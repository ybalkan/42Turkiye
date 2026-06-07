extends Camera2D

@export var zoom_speed: float = 0.1
@export var zoom_min: float = 0.3
@export var zoom_max: float = 5.0
@export var drag_speed: float = 1.0
@export var intro_duration: float = 5.0

var dragging: bool = false
var drag_start: Vector2
var canvas_modulate: CanvasModulate
var intro_timer: float = 0.0
var intro_done: bool = false

func _ready() -> void:
	canvas_modulate = CanvasModulate.new()
	canvas_modulate.color = Color(0, 0, 0, 1)
	add_child(canvas_modulate)

func _process(delta: float) -> void:
	if not intro_done:
		intro_timer += delta
		var t = clamp(intro_timer / intro_duration, 0.0, 1.0)
		canvas_modulate.color = Color(t, t, t, 1)
		if t >= 1.0:
			intro_done = true

func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_WHEEL_UP:
			zoom = clamp(
				zoom + Vector2(zoom_speed, zoom_speed),
				Vector2(zoom_min, zoom_min),
				Vector2(zoom_max, zoom_max)
			)
		elif event.button_index == MOUSE_BUTTON_WHEEL_DOWN:
			zoom = clamp(
				zoom - Vector2(zoom_speed, zoom_speed),
				Vector2(zoom_min, zoom_min),
				Vector2(zoom_max, zoom_max)
			)
		if event.button_index == MOUSE_BUTTON_MIDDLE:
			dragging = event.pressed
			drag_start = event.position
	if event is InputEventMouseMotion and dragging:
		var drag_delta = (event.position - drag_start) / zoom
		position -= drag_delta * drag_speed
		drag_start = event.position
