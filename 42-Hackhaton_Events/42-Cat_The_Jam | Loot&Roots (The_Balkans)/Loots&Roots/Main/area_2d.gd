extends Area2D

var label: Label

func _ready() -> void:
	input_pickable = true
	input_event.connect(_on_input_event)
	label = get_node_or_null("Label")
	if label == null:
		# Fallback: absolute yolu dene
		label = get_node_or_null("/root/Loot&Roots/Binalar/Area2D/Label")
	if label:
		label.visible = false

func _on_input_event(_viewport, event: InputEvent, _shape) -> void:
	if label == null:
		return
	if event is InputEventMouseButton and event.pressed:
		label.visible = !label.visible
		label.text = (
			"👤  %s\n" +
			"⭐  Level: %.2f\n" +
			"🏆  Milestone: %d\n" +
			"⏱  Haftalık Log: %.1f saat\n" +
			"📅  Toplam Log: %.1f saat"
		) % [
			PlayerData.intra_login,
			PlayerData.intra_level,
			PlayerData.milestone,
			PlayerData.weekly_log_hours,
			PlayerData.log_time_hours
		]
