extends Node2D
##
## Kuyu — Milestone 1 ile açılır (Arazi 1).
##
## Kural: Haftada 42 saat log time → 1 kova su kazanılır (login'de hesaplanır).
## Kullanım: Tıkla → tüm tarlalar anında max aşamaya gelir.
##

signal bucket_used(remaining: int)


func _ready() -> void:
	input_pickable = true if has_method("input_pickable") else false
	# Eğer Area2D ise
	if self is Area2D:
		input_event.connect(_on_input_event)


func _on_input_event(_viewport, event: InputEvent, _shape_idx: int) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		use_bucket()


func use_bucket() -> void:
	if PlayerData.milestone < 1:
		print("[Kuyu] Henüz açılmadı (Milestone 1 gerekli).")
		return
	if PlayerData.water_buckets <= 0:
		print("[Kuyu] Kova yok! Bu hafta 42 saat log time biriktir.")
		return

	# FarmManager'a bağlan
	var farm_manager := _find_farm_manager()
	if farm_manager == null:
		push_warning("[Kuyu] FarmManager bulunamadı!")
		return

	farm_manager.water_all_crops()
	emit_signal("bucket_used", PlayerData.water_buckets)
	print("[Kuyu] Kova kullanıldı. Kalan: %d" % PlayerData.water_buckets)


func _find_farm_manager() -> Node:
	# Sahne ağacında FarmManager'ı ara
	var root := get_tree().root
	return _search_for_node(root, "farm_manager")


func _search_for_node(node: Node, script_name: String) -> Node:
	if node.get_script() != null:
		var path: String = node.get_script().resource_path
		if path.get_file().get_basename() == script_name:
			return node
	for child in node.get_children():
		var result := _search_for_node(child, script_name)
		if result != null:
			return result
	return null
