extends Area2D
##
## Depo (kırmızı ahır) — tıklanınca envanter panelini açar/kapar.
##
## Bağlantı yolu: Binalar/Depo/Control (control.gd → toggle())
##

func _ready() -> void:
	input_pickable = true
	input_event.connect(_on_input_event)


func _on_input_event(_viewport, event: InputEvent, _shape_idx) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		_toggle_inventory()


func _toggle_inventory() -> void:
	# Depo'nun kendi Control child'ı üzerindeki control.gd toggle()'ını çağır
	var control := get_node_or_null("Control")
	if control and control.has_method("toggle"):
		control.toggle()
		return

	# Fallback: sahnedeki %Control unique node arama
	var root := get_tree().root
	var found := _find_by_script_name(root, "control")
	if found and found.has_method("toggle"):
		found.toggle()
	else:
		push_warning("[Depo] control.gd bulunamadı!")


func _find_by_script_name(node: Node, script_name: String) -> Node:
	if node.get_script() != null:
		var path: String = node.get_script().resource_path
		if path.get_file().get_basename() == script_name:
			return node
	for child in node.get_children():
		var result := _find_by_script_name(child, script_name)
		if result != null:
			return result
	return null
