extends Area2D

signal clicked(position)

func _ready() -> void:
	input_pickable = true
	input_event.connect(_on_input)

func _on_input(_viewport, event: InputEvent, _shape) -> void:
	if event is InputEventMouseButton and event.pressed:
		emit_signal("clicked", event.position)
