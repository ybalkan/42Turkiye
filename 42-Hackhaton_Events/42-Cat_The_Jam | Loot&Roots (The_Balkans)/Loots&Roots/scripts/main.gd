extends Control
##
## Loot & Roots — Ana login ekranı (Görselli).
## Arka plan: Login.png
## Görseldeki LOGIN yazısının üzerine gizli bir buton ekleyerek tıklanabilir yaptık.
## all_data_ready → PlayerData doldurulur → oyun sahnesi açılır.
##

const MAIN_SCENE := "res://Main/node_2d.tscn"
const BG_PATH    := "res://Login.png"

# UI düğümleri
var _login_btn:     Button
var _status_lbl:    Label
var _overlay:       ColorRect
var _user_panel:    PanelContainer
var _avatar_rect:   TextureRect
var _info_lbl:      Label
var _spinner_lbl:   Label

var _avatar_http:   HTTPRequest
var _is_loading:    bool  = false
var _spinner_t:     float = 0.0


func _ready() -> void:
	_build_ui()
	OAuth42.status_changed.connect(_on_status_changed)
	OAuth42.all_data_ready.connect(_on_all_data_ready)
	OAuth42.login_failed.connect(_on_login_failed)


func _process(delta: float) -> void:
	if not _is_loading:
		return
	_spinner_t += delta * 3.0
	var frames := ["◐", "◓", "◑", "◒"]
	_spinner_lbl.text = frames[int(_spinner_t) % frames.size()]


# ─────────────────────────────────────────────────────────────
# UI İNŞASI
# ─────────────────────────────────────────────────────────────
func _build_ui() -> void:
	# ── Tam ekran arka plan resmi ──
	var bg := TextureRect.new()
	bg.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	bg.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	bg.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_COVERED
	if ResourceLoader.exists(BG_PATH):
		bg.texture = load(BG_PATH)
	add_child(bg)

	# ── GİZLİ BUTON: Görseldeki LOGIN yazısının üstüne gelir ──
	_login_btn = Button.new()
	_login_btn.set_anchor_and_offset(SIDE_LEFT,   0.5, -160.0)
	_login_btn.set_anchor_and_offset(SIDE_RIGHT,  0.5,  160.0)
	_login_btn.set_anchor_and_offset(SIDE_TOP,    1.0, -140.0)
	_login_btn.set_anchor_and_offset(SIDE_BOTTOM, 1.0,  -40.0)
	# flat = true sayesinde butonun kendi arka planı/grafikleri görünmez!
	_login_btn.flat = true
	# Fareyle üzerine gelince (hover) imleci el işaretine dönüştürür.
	_login_btn.mouse_default_cursor_shape = Control.CURSOR_POINTING_HAND
	_login_btn.pressed.connect(_on_login_pressed)
	add_child(_login_btn)

	# ── Yükleme overlay'i (login süresince hafif karartır) ──
	_overlay = ColorRect.new()
	_overlay.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	_overlay.color = Color(0, 0, 0, 0.6)
	_overlay.visible = false
	add_child(_overlay)

	# ── Spinner (yükleme animasyonu) ──
	_spinner_lbl = Label.new()
	_spinner_lbl.text = "◐"
	_spinner_lbl.set_anchor_and_offset(SIDE_LEFT,   0.5, -24.0)
	_spinner_lbl.set_anchor_and_offset(SIDE_RIGHT,  0.5,  24.0)
	_spinner_lbl.set_anchor_and_offset(SIDE_TOP,    0.5, -30.0)
	_spinner_lbl.set_anchor_and_offset(SIDE_BOTTOM, 0.5,  30.0)
	_spinner_lbl.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_spinner_lbl.add_theme_font_size_override("font_size", 48)
	_spinner_lbl.add_theme_color_override("font_color", Color("#f5c842"))
	_spinner_lbl.visible = false
	add_child(_spinner_lbl)

	# ── Status mesajı ──
	_status_lbl = Label.new()
	_status_lbl.text = ""
	_status_lbl.set_anchor_and_offset(SIDE_LEFT,   0.0,  20.0)
	_status_lbl.set_anchor_and_offset(SIDE_RIGHT,  1.0, -20.0)
	_status_lbl.set_anchor_and_offset(SIDE_TOP,    0.5,  40.0)
	_status_lbl.set_anchor_and_offset(SIDE_BOTTOM, 0.5,  80.0)
	_status_lbl.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	_status_lbl.add_theme_font_size_override("font_size", 16)
	_status_lbl.add_theme_color_override("font_color", Color("#f5e0a0"))
	add_child(_status_lbl)

	# ── Login başarı paneli (avatar + bilgi) ──
	_user_panel = PanelContainer.new()
	_user_panel.set_anchors_and_offsets_preset(Control.PRESET_CENTER)
	_user_panel.grow_horizontal = Control.GROW_DIRECTION_BOTH
	_user_panel.grow_vertical = Control.GROW_DIRECTION_BOTH
	_user_panel.visible = false

	var panel_style := StyleBoxFlat.new()
	panel_style.bg_color = Color(0.1, 0.05, 0.0, 0.9)
	panel_style.border_color = Color("#c48a2f")
	panel_style.set_border_width_all(2)
	panel_style.set_corner_radius_all(12)
	panel_style.set_content_margin_all(16)
	_user_panel.add_theme_stylebox_override("panel", panel_style)
	add_child(_user_panel)

	var hbox := HBoxContainer.new()
	hbox.add_theme_constant_override("separation", 16)
	_user_panel.add_child(hbox)

	_avatar_rect = TextureRect.new()
	_avatar_rect.custom_minimum_size = Vector2(80, 80)
	_avatar_rect.expand_mode = TextureRect.EXPAND_FIT_WIDTH_PROPORTIONAL
	_avatar_rect.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
	hbox.add_child(_avatar_rect)

	_info_lbl = Label.new()
	_info_lbl.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	_info_lbl.add_theme_font_size_override("font_size", 14)
	_info_lbl.add_theme_color_override("font_color", Color("#fff8e0"))
	hbox.add_child(_info_lbl)

	# Avatar HTTP
	_avatar_http = HTTPRequest.new()
	add_child(_avatar_http)
	_avatar_http.request_completed.connect(_on_avatar_downloaded)


# ─────────────────────────────────────────────────────────────
# Sinyal işleyicileri
# ─────────────────────────────────────────────────────────────
func _on_login_pressed() -> void:
	_login_btn.disabled = true
	_status_lbl.text   = "Tarayıcıda 42'ye bağlanılıyor..."
	_overlay.visible   = true
	_spinner_lbl.visible = true
	_is_loading = true
	OAuth42.start_login()


func _on_status_changed(message: String) -> void:
	_status_lbl.text = message


func _on_login_failed(error: String) -> void:
	_login_btn.disabled  = false
	_overlay.visible     = false
	_spinner_lbl.visible = false
	_is_loading = false
	_status_lbl.text = "⚠  " + error
	push_error("[OAuth42] " + error)


func _on_all_data_ready(user_data: Dictionary, logtime_data: Dictionary) -> void:
	PlayerData.initialize(user_data, logtime_data)

	_login_btn.disabled  = false
	_spinner_lbl.visible = false
	_is_loading = false

	# Kullanıcı bilgisi paneli
	var login_name:   String = user_data.get("login", "?")
	var display_name: String = user_data.get("displayname", "?")
	var level:        float  = PlayerData.intra_level
	var milestone:    int    = PlayerData.milestone
	var total_log:    float  = PlayerData.log_time_hours
	var weekly_log:   float  = PlayerData.weekly_log_hours

	_info_lbl.text = (
		"👤  %s  (%s)\n" +
		"⭐  Level: %.2f\n" +
		"🏆  Milestone: %d\n" +
		"⏱  Haftalık Log: %.1f saat\n" +
		"📅  Toplam Log: %.1f saat"
	) % [login_name, display_name, level, milestone, weekly_log, total_log]

	_status_lbl.text = "✅  Hoşgeldin, %s!  Çiftliğin hazır..." % login_name
	_user_panel.visible = true

	# Avatar indir
	var image_info: Dictionary = user_data.get("image", {})
	var versions:   Dictionary = image_info.get("versions", {})
	var avatar_url: String     = versions.get("medium", image_info.get("link", ""))
	if avatar_url != "":
		_avatar_http.request(avatar_url)
	else:
		await get_tree().create_timer(2.5).timeout
		_go_to_game()


func _on_avatar_downloaded(_result: int, response_code: int, _headers: PackedStringArray, body: PackedByteArray) -> void:
	if response_code == 200 and body.size() > 8:
		var img := Image.new()
		var err := FAILED
		
		if body[0] == 255 and body[1] == 216:
			err = img.load_jpg_from_buffer(body)
		elif body[0] == 137 and body[1] == 80 and body[2] == 78 and body[3] == 71:
			err = img.load_png_from_buffer(body)
		elif body[0] == 82 and body[1] == 73 and body[2] == 70 and body[3] == 70:
			err = img.load_webp_from_buffer(body)
			
		if err == OK:
			_avatar_rect.texture = ImageTexture.create_from_image(img)

	await get_tree().create_timer(2.5).timeout
	_go_to_game()


func _go_to_game() -> void:
	_overlay.color = Color(0, 0, 0, 0.0)
	var tween := create_tween()
	tween.tween_property(_overlay, "color", Color(0, 0, 0, 1.0), 0.8)
	tween.tween_callback(func(): get_tree().change_scene_to_file(MAIN_SCENE))
	_overlay.visible = true
