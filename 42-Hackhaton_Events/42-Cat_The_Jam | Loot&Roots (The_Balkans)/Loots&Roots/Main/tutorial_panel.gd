extends Area2D
##
## TutorailPanel — Pano üzerine gelinince tutorial içeriğini gösterir.
## Depo (envanter) ile aynı hover mantığını kullanır.
##

var _panel: Control  # VBoxContainer

func _ready() -> void:
	input_pickable = true
	_panel = get_node_or_null("VBoxContainer")
	if _panel:
		_panel.visible = false

	mouse_entered.connect(_on_mouse_entered)
	mouse_exited.connect(_on_mouse_exited)


func _on_mouse_entered() -> void:
	if _panel:
		_panel.visible = true


func _on_mouse_exited() -> void:
	if _panel:
		_panel.visible = false
