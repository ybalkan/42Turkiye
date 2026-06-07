extends Node
##
## GameState — Aktif arazi ve arazi geçiş yönetimi.
##
## Kullanım: GameState.active_land → şu an hangi arazi görünüyor.
## Arazi geçişi: GameState.change_land(n)
##

var active_land: int = 0

signal land_changed(new_land: int)


func change_land(index: int) -> void:
	var max_land := PlayerData.get_unlocked_land_count() - 1
	index = clamp(index, 0, max_land)
	if index == active_land:
		return
	active_land = index
	emit_signal("land_changed", active_land)
	print("[GameState] Aktif arazi → %d" % active_land)


func next_land() -> void:
	change_land(active_land + 1)


func prev_land() -> void:
	change_land(active_land - 1)


func is_land_unlocked(index: int) -> bool:
	return index < PlayerData.get_unlocked_land_count()
