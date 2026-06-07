extends Node

var user_data: Dictionary = {}
var intra_login: String = ""
var intra_level: float = 0.0
var milestone: int = 0

const DEBUG_SKIP_LOGIN: bool = false
const DEBUG_LOG_HOURS: float = 6.0

var log_time_hours: float = DEBUG_LOG_HOURS if DEBUG_SKIP_LOGIN else 0.0
var weekly_log_hours: float = 42.0 if DEBUG_SKIP_LOGIN else 0.0
var days_until_blackhole: int = -1

var seeds: Dictionary = {"bugday": 4, "lahana": 0, "havuc": 0}
var water_buckets: int = 0
var loot_roots_coin: int = 0
var last_eval_count: int = 0

signal data_initialized()

func initialize(p_user_data: Dictionary, p_logtime_data: Dictionary) -> void:
	user_data = p_user_data
	intra_login = p_user_data.get("login", "")

	var cursus_users: Array = p_user_data.get("cursus_users", [])
	intra_level = 0.0
	for cu in cursus_users:
		var lvl: float = float(cu.get("level", 0.0))
		var c_name: String = cu.get("cursus", {}).get("name", "")
		if c_name == "42cursus":
			intra_level = lvl
			break
		if lvl > intra_level:
			intra_level = lvl

	_calculate_milestone()
	_parse_logtime(p_logtime_data)
	_calculate_seed_bonus()
	_calculate_water_buckets()
	_calculate_blackhole(p_user_data)

	emit_signal("data_initialized")
	print("[PlayerData] Initialized — login=%s level=%.2f milestone=%d log_time=%.1fh blackhole=%d gün" % [
		intra_login, intra_level, milestone, log_time_hours, days_until_blackhole
	])


func _calculate_blackhole(p_user_data: Dictionary) -> void:
	var blackhole_str: String = p_user_data.get("blackholed_at", "")
	if blackhole_str == "" or blackhole_str == "null":
		days_until_blackhole = -1
		return
	var blackhole_date = Time.get_datetime_dict_from_datetime_string(blackhole_str, false)
	var blackhole_unix = Time.get_unix_time_from_datetime_dict(blackhole_date)
	var now_unix = Time.get_unix_time_from_system()
	days_until_blackhole = int((blackhole_unix - now_unix) / 86400)


func _calculate_milestone() -> void:
	var projects_users: Array = user_data.get("projects_users", [])
	var validated: int = 0
	for pu in projects_users:
		if pu.get("validated?", false):
			validated += 1
	if validated >= 25:
		milestone = 3
	elif validated >= 10:
		milestone = 2
	elif validated >= 3:
		milestone = 1
	else:
		milestone = 0


func _parse_logtime(logtime_data: Dictionary) -> void:
	var total_seconds: float = 0.0
	var weekly_seconds: float = 0.0
	var current_week_key := _get_current_week_key()
	for week_key in logtime_data.keys():
		var secs: float = float(logtime_data[week_key])
		total_seconds += secs
		if week_key == current_week_key:
			weekly_seconds = secs
	log_time_hours = total_seconds / 3600.0
	weekly_log_hours = weekly_seconds / 3600.0


func _get_current_week_key() -> String:
	var d := Time.get_datetime_dict_from_system()
	var year: int = d["year"]
	var month: int = d["month"]
	var day: int = d["day"]
	var jan1_weekday := _weekday_of_jan1(year)
	var day_of_year := _day_of_year(year, month, day)
	var week_number: int = int(float(day_of_year + jan1_weekday - 1) / 7.0) + 1
	return "%d-W%02d" % [year, week_number]


func _weekday_of_jan1(year: int) -> int:
	var d := Time.get_datetime_dict_from_unix_time(
		Time.get_unix_time_from_datetime_dict({"year": year, "month": 1, "day": 1, "hour": 0, "minute": 0, "second": 0})
	)
	return d.get("weekday", 0)


func _day_of_year(year: int, month: int, day: int) -> int:
	var days_in_month := [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
	if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
		days_in_month[2] = 29
	var total := day
	for m in range(1, month):
		total += days_in_month[m]
	return total


func _calculate_seed_bonus() -> void:
	var projects_users: Array = user_data.get("projects_users", [])
	var current_eval_count: int = 0
	for pu in projects_users:
		if pu.get("final_mark", null) != null:
			current_eval_count += 1
	last_eval_count = current_eval_count
	# Tohum başlangıcı: buğday için proje sayısına göre (max 4), diğerleri sabit 4
	var bugday_bonus: int = clamp(current_eval_count, 0, 4)
	if seeds["bugday"] < bugday_bonus:
		seeds["bugday"] = bugday_bonus
	if milestone >= 1 and seeds["lahana"] < 4:
		seeds["lahana"] = 4
	if milestone >= 2 and seeds["havuc"] < 4:
		seeds["havuc"] = 4


func _add_seeds_for_diff(amount: int) -> void:
	var unlocked_crops := []
	for crop in ["bugday", "lahana", "havuc"]:
		if is_crop_unlocked(crop):
			unlocked_crops.append(crop)
	if unlocked_crops.is_empty():
		seeds["bugday"] += amount
		return
	var min_crop: String = unlocked_crops[0]
	for crop in unlocked_crops:
		if seeds.get(crop, 0) < seeds.get(min_crop, 0):
			min_crop = crop
	seeds[min_crop] += amount


func _calculate_water_buckets() -> void:
	if milestone < 1:
		return
	var earned: int = int(weekly_log_hours / 42.0)
	water_buckets = min(3, water_buckets + earned)


func get_growth_stage_bonus() -> int:
	return clamp(int(log_time_hours / 2.0), 0, 3)


func get_unlocked_land_count() -> int:
	return milestone + 1


func is_crop_unlocked(crop: String) -> bool:
	match crop:
		"bugday":  return milestone >= 0
		"lahana":  return milestone >= 1
		"havuc":   return milestone >= 2
		_:         return false


func use_seed(crop_name: String) -> bool:
	if seeds.get(crop_name, 0) > 0:
		seeds[crop_name] -= 1
		return true
	return false


func add_lrc(amount: int) -> void:
	loot_roots_coin += amount
	print("[PlayerData] LRC +%d → toplam %d" % [amount, loot_roots_coin])
