extends Node
##
## 42 API OAuth2 (Authorization Code Flow) singleton.
##
## Akis:
##   1) start_login() -> tarayicida intra.42.fr/oauth/authorize acilir
##   2) localhost:PORT/callback dinlenir, code yakalanir
##   3) code -> token endpoint, access_token alinir
##   4) access_token ile /v2/me cagrilir
##   5) /v2/users/{login}/locations_stats cagrilir (log time)
##   6) all_data_ready(user_data, logtime_data) yayinlanir
##

signal status_changed(message: String)
signal all_data_ready(user_data: Dictionary, logtime_data: Dictionary)
signal login_failed(error: String)

# Geriye dönük uyumluluk için (main.gd gibi eski kodlar hâlâ bağlıysa)
signal login_success(user_data: Dictionary)

const AUTH_URL := "https://api.intra.42.fr/oauth/authorize"
const TOKEN_URL := "https://api.intra.42.fr/oauth/token"
const ME_URL := "https://api.intra.42.fr/v2/me"
const LOGTIME_URL := "https://api.intra.42.fr/v2/users/%s/locations_stats"

var _uid: String = ""
var _secret: String = ""
var _redirect_uri: String = "http://localhost:8060/tmp_js_export.html"
var _redirect_port: int = 8060

var _state_token: String = ""
var access_token: String = ""

var _tcp_server_v4: TCPServer = null
var _tcp_server_v6: TCPServer = null
var _pending_peers: Array = []  # [{peer: StreamPeerTCP, buffer: String}, ...]

var _http_token: HTTPRequest
var _http_me: HTTPRequest
var _http_logtime: HTTPRequest

var _user_data: Dictionary = {}


func _ready() -> void:
	set_process(false)
	_load_secrets()

	_http_token = HTTPRequest.new()
	add_child(_http_token)
	_http_token.request_completed.connect(_on_token_response)

	_http_me = HTTPRequest.new()
	add_child(_http_me)
	_http_me.request_completed.connect(_on_me_response)

	_http_logtime = HTTPRequest.new()
	add_child(_http_logtime)
	_http_logtime.request_completed.connect(_on_logtime_response)

	if OS.has_feature("web"):
		_check_web_callback()


func _load_secrets() -> void:
	var cfg := ConfigFile.new()
	var err := cfg.load("res://secrets.cfg")
	if err != OK:
		push_warning("secrets.cfg yuklenemedi (err=%d). secrets.cfg.example'i kopyalayip doldur." % err)
		return
	_uid = cfg.get_value("api42", "uid", "")
	_secret = cfg.get_value("api42", "secret", "")
	_redirect_uri = cfg.get_value("api42", "redirect_uri", _redirect_uri)
	
	if not OS.has_feature("web"):
		var splits := _redirect_uri.split(":")
		if splits.size() > 2:
			var port_part := splits[2]
			_redirect_port = int(port_part.split("/")[0])
		else:
			_redirect_port = 8765


func start_login() -> void:
	if _uid == "" or _secret == "":
		emit_signal("login_failed", "secrets.cfg eksik (UID/SECRET bos).")
		return

	_state_token = _generate_state()

	var params := {
		"client_id": _uid,
		"redirect_uri": _redirect_uri,
		"response_type": "code",
		"scope": "public",
		"state": _state_token,
	}
	var query := ""
	for k in params.keys():
		if query != "":
			query += "&"
		query += String(k).uri_encode() + "=" + String(params[k]).uri_encode()
	var full_url := AUTH_URL + "?" + query

	if OS.has_feature("web"):
		_save_web_state(_state_token)
		emit_signal("status_changed", "Tarayicida 42'ye yonlendiriliyor...")
		JavaScriptBridge.eval("window.location.href = '%s';" % full_url)
		return

	if _tcp_server_v4 != null or _tcp_server_v6 != null:
		emit_signal("login_failed", "Zaten bir giris islemi devam ediyor.")
		return

	_tcp_server_v4 = TCPServer.new()
	var err_v4 := _tcp_server_v4.listen(_redirect_port, "127.0.0.1")
	if err_v4 != OK:
		_tcp_server_v4 = null
		
	_tcp_server_v6 = TCPServer.new()
	var err_v6 := _tcp_server_v6.listen(_redirect_port, "::1")
	if err_v6 != OK:
		_tcp_server_v6 = null

	if _tcp_server_v4 == null and _tcp_server_v6 == null:
		emit_signal("login_failed", "Port %d dinlenemedi (zaten kullanimda olabilir)." % _redirect_port)
		return

	emit_signal("status_changed", "Tarayicida 42'ye giris yap...")
	OS.shell_open(full_url)
	set_process(true)


func cancel_login() -> void:
	_stop_server()
	emit_signal("status_changed", "Giris iptal edildi.")


func _generate_state() -> String:
	var chars := "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	var s := ""
	for i in range(32):
		s += chars[randi() % chars.length()]
	return s


func _process(_delta: float) -> void:
	if _tcp_server_v4 == null and _tcp_server_v6 == null:
		return

	if _tcp_server_v4 != null:
		while _tcp_server_v4.is_connection_available():
			var peer := _tcp_server_v4.take_connection()
			_pending_peers.append({"peer": peer, "buffer": ""})

	if _tcp_server_v6 != null:
		while _tcp_server_v6.is_connection_available():
			var peer := _tcp_server_v6.take_connection()
			_pending_peers.append({"peer": peer, "buffer": ""})

	var i := 0
	while i < _pending_peers.size():
		if _tcp_server_v4 == null and _tcp_server_v6 == null:
			return  # _stop_server cagrildi
		var entry: Dictionary = _pending_peers[i]
		var peer: StreamPeerTCP = entry.peer
		peer.poll()
		var should_remove := false
		if peer.get_status() != StreamPeerTCP.STATUS_CONNECTED:
			should_remove = true
		else:
			var available := peer.get_available_bytes()
			if available > 0:
				entry.buffer += peer.get_utf8_string(available)
			if "\r\n\r\n" in entry.buffer:
				_handle_http_request(peer, entry.buffer)
				should_remove = true
		if should_remove:
			if _tcp_server_v4 == null and _tcp_server_v6 == null:
				return
			_pending_peers.remove_at(i)
		else:
			i += 1


func _handle_http_request(peer: StreamPeerTCP, raw: String) -> void:
	var first_line := raw.split("\r\n")[0]
	var parts := first_line.split(" ")
	if parts.size() < 2:
		_send_response(peer, 400, _html_page("Bad request"))
		return
	var path := parts[1]
	if not path.begins_with("/callback"):
		_send_response(peer, 404, _html_page("Not found"))
		return

	var qmark := path.find("?")
	if qmark == -1:
		_send_response(peer, 400, _html_page("Callback parametresiz geldi."))
		emit_signal("login_failed", "Callback'te query parametresi yok.")
		_stop_server()
		return

	var query := path.substr(qmark + 1)
	var params := {}
	for pair in query.split("&"):
		var kv := pair.split("=", true, 1)
		if kv.size() == 2:
			params[kv[0].uri_decode()] = kv[1].uri_decode()

	if "error" in params:
		var err_msg: String = params.get("error_description", params["error"])
		_send_response(peer, 200, _html_page("Giris reddedildi: " + err_msg))
		emit_signal("login_failed", "42 reddetti: " + err_msg)
		_stop_server()
		return

	if not "code" in params or not "state" in params:
		_send_response(peer, 400, _html_page("Eksik code veya state."))
		emit_signal("login_failed", "Callback'te code veya state eksik.")
		_stop_server()
		return

	if params["state"] != _state_token:
		_send_response(peer, 400, _html_page("State uyumsuz (CSRF korumasi)."))
		emit_signal("login_failed", "State uyumsuz - olasi CSRF.")
		_stop_server()
		return

	_send_response(peer, 200, _html_page("Giris basarili! Bu sekmeyi kapatabilirsin."))
	_stop_server()

	emit_signal("status_changed", "Token aliniyor...")
	_exchange_code_for_token(params["code"])


func _send_response(peer: StreamPeerTCP, status: int, body: String) -> void:
	var status_text := "OK" if status == 200 else "ERROR"
	var body_bytes := body.to_utf8_buffer()
	var response := "HTTP/1.1 %d %s\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %d\r\nConnection: close\r\n\r\n" % [status, status_text, body_bytes.size()]
	peer.put_data(response.to_utf8_buffer())
	peer.put_data(body_bytes)
	peer.disconnect_from_host()


func _html_page(message: String) -> String:
	return "<!doctype html><html><head><meta charset='utf-8'><title>42 Auth</title><style>body{font-family:sans-serif;background:#111;color:#eee;display:flex;align-items:center;justify-content:center;height:100vh;margin:0}div{text-align:center;padding:2em 3em;border:1px solid #00babc;border-radius:8px}h1{color:#00babc;margin:0 0 .5em}</style></head><body><div><h1>42-gamejam</h1><p>" + message + "</p></div></body></html>"


func _stop_server() -> void:
	if _tcp_server_v4 != null:
		_tcp_server_v4.stop()
		_tcp_server_v4 = null
	if _tcp_server_v6 != null:
		_tcp_server_v6.stop()
		_tcp_server_v6 = null
	for entry in _pending_peers:
		var peer: StreamPeerTCP = entry.peer
		if peer.get_status() == StreamPeerTCP.STATUS_CONNECTED:
			peer.disconnect_from_host()
	_pending_peers.clear()
	set_process(false)


func _exchange_code_for_token(code: String) -> void:
	var body := {
		"grant_type": "authorization_code",
		"client_id": _uid,
		"client_secret": _secret,
		"code": code,
		"redirect_uri": _redirect_uri,
	}
	var body_str := ""
	for k in body.keys():
		if body_str != "":
			body_str += "&"
		body_str += String(k).uri_encode() + "=" + String(body[k]).uri_encode()
	var headers := ["Content-Type: application/x-www-form-urlencoded"]
	var err := _http_token.request(TOKEN_URL, headers, HTTPClient.METHOD_POST, body_str)
	if err != OK:
		emit_signal("login_failed", "Token request baslatilamadi (err=%d)." % err)


func _on_token_response(_result: int, response_code: int, _headers: PackedStringArray, body: PackedByteArray) -> void:
	var text := body.get_string_from_utf8()
	if response_code != 200:
		emit_signal("login_failed", "Token endpoint %d dondu: %s" % [response_code, text])
		return
	var json: Variant = JSON.parse_string(text)
	if json == null or typeof(json) != TYPE_DICTIONARY or not "access_token" in json:
		emit_signal("login_failed", "Token cevabi gecersiz: " + text)
		return
	access_token = json["access_token"]
	emit_signal("status_changed", "Kullanici bilgisi cekiliyor...")
	_fetch_me()


func _fetch_me() -> void:
	var headers := ["Authorization: Bearer " + access_token]
	var err := _http_me.request(ME_URL, headers, HTTPClient.METHOD_GET)
	if err != OK:
		emit_signal("login_failed", "/v2/me request baslatilamadi (err=%d)." % err)


func _on_me_response(_result: int, response_code: int, _headers: PackedStringArray, body: PackedByteArray) -> void:
	var text := body.get_string_from_utf8()
	if response_code != 200:
		emit_signal("login_failed", "/v2/me %d dondu: %s" % [response_code, text])
		return
	var json: Variant = JSON.parse_string(text)
	if json == null or typeof(json) != TYPE_DICTIONARY:
		emit_signal("login_failed", "/v2/me cevabi parse edilemedi.")
		return
	_user_data = json
	# Geriye dönük uyumluluk sinyali
	emit_signal("login_success", _user_data)
	# Log time çek
	var login: String = _user_data.get("login", "")
	if login == "":
		emit_signal("login_failed", "Login adi bos — log time cekilemiyor.")
		return
	emit_signal("status_changed", "Log time verisi cekiliyor...")
	_fetch_logtime(login)


# ─────────────────────────────────────────────────────────────
# Log Time — /v2/users/{login}/locations_stats
# Yanıt: { "2024-W01": 3600, ... }  (saniye cinsinden)
# ─────────────────────────────────────────────────────────────
func _fetch_logtime(login: String) -> void:
	var url := LOGTIME_URL % login
	var headers := ["Authorization: Bearer " + access_token]
	var err := _http_logtime.request(url, headers, HTTPClient.METHOD_GET)
	if err != OK:
		# Log time çekilemese de devam et (boş veriyle)
		push_warning("[OAuth42] Log time request baslatilamadi (err=%d). Bos devam." % err)
		emit_signal("all_data_ready", _user_data, {})


func _on_logtime_response(_result: int, response_code: int, _headers: PackedStringArray, body: PackedByteArray) -> void:
	var text := body.get_string_from_utf8()
	if response_code != 200:
		push_warning("[OAuth42] Log time %d dondu. Bos veriyle devam." % response_code)
		emit_signal("all_data_ready", _user_data, {})
		return
	var json: Variant = JSON.parse_string(text)
	if json == null or typeof(json) != TYPE_DICTIONARY:
		push_warning("[OAuth42] Log time parse edilemedi. Bos veriyle devam.")
		emit_signal("all_data_ready", _user_data, {})
		return
	emit_signal("status_changed", "Veriler hazir!")
	emit_signal("all_data_ready", _user_data, json)

# ─────────────────────────────────────────────────────────────
# Web Auth Helpers
# ─────────────────────────────────────────────────────────────
func _save_web_state(state: String) -> void:
	var cfg := ConfigFile.new()
	cfg.set_value("oauth", "state", state)
	cfg.save("user://oauth_state.cfg")


func _load_web_state() -> String:
	var cfg := ConfigFile.new()
	if cfg.load("user://oauth_state.cfg") == OK:
		return cfg.get_value("oauth", "state", "")
	return ""


func _check_web_callback() -> void:
	var query_raw = JavaScriptBridge.eval("window.location.search;")
	if typeof(query_raw) != TYPE_STRING:
		return
	var query: String = query_raw
	
	if query.length() > 1 and query.begins_with("?"):
		query = query.substr(1)
		var params := {}
		for pair in query.split("&"):
			var kv := pair.split("=", true, 1)
			if kv.size() == 2:
				params[kv[0].uri_decode()] = kv[1].uri_decode()
		
		if "error" in params:
			var err_msg: String = params.get("error_description", params.get("error", "Bilinmeyen hata"))
			emit_signal("login_failed", "42 reddetti: " + err_msg)
			return
			
		if "code" in params and "state" in params:
			var saved_state := _load_web_state()
			if params["state"] != saved_state:
				emit_signal("login_failed", "State uyumsuz - olasi CSRF.")
				return
				
			emit_signal("status_changed", "Token aliniyor...")
			JavaScriptBridge.eval("window.history.replaceState({}, document.title, window.location.pathname);")
			_exchange_code_for_token(params["code"])
