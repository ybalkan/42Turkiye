extends Area2D
##
## Lahana bitkisi. Log time tabanlı büyüme.
## Başlangıç aşaması PlayerData.get_growth_stage_bonus() ile belirlenir.
##

@export var crop_type: String = "lahana"
@export var growth_time: float = 4.0  # her aşama kaç saniye

@onready var animated_sprite: AnimatedSprite2D = $AnimatedSprite2D

const MAX_STAGE = 3  # 0,1,2,3 → 4 aşama

var current_stage: int = 0
var is_growing: bool = false
var growth_timer: float = 0.0


func _ready() -> void:
	input_pickable = true
	input_event.connect(_on_input_event)
	start_growing()


func start_growing() -> void:
	var bonus: int = 0
	if Engine.has_singleton("PlayerData") or has_node("/root/PlayerData"):
		bonus = PlayerData.get_growth_stage_bonus()
	current_stage = clamp(bonus, 0, MAX_STAGE)
	is_growing = current_stage < MAX_STAGE
	growth_timer = 0.0
	_update_animation()


func force_max_stage() -> void:
	current_stage = MAX_STAGE
	is_growing = false
	growth_timer = 0.0
	_update_animation()


func _process(delta: float) -> void:
	if not is_growing:
		return

	growth_timer += delta
	if growth_timer >= growth_time:
		growth_timer = 0.0
		_advance_stage()


func _advance_stage() -> void:
	if current_stage < MAX_STAGE:
		current_stage += 1
		_update_animation()
	else:
		is_growing = false


func _update_animation() -> void:
	var anim_name = crop_type + "_" + str(current_stage)
	if animated_sprite.sprite_frames.has_animation(anim_name):
		animated_sprite.play(anim_name)
	else:
		print("[lahana] BULUNAMADI: ", anim_name)


func _on_input_event(_viewport, event: InputEvent, _shape_idx: int) -> void:
	if event is InputEventMouseButton and event.pressed:
		if current_stage == MAX_STAGE:
			_harvest()


func _harvest() -> void:
	Inventory.add_item(crop_type, 1)
	start_growing()
	print("Hasat edildi: ", crop_type)
