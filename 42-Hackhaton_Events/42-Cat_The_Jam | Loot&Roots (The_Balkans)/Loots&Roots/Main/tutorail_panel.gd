extends Area2D

func _ready() -> void:
	body_entered.connect(_on_body_entered)
	body_exited.connect(_on_body_exited)
	get_node("/root/Loot&Roots/tavuk/TutorailPanel/VBoxContainer").visible = false

func _on_body_entered(body: Node) -> void:
	if body is CharacterBody2D:
		get_node("/root/Loot&Roots/tavuk/TutorailPanel/VBoxContainer").visible = true

func _on_body_exited(body: Node) -> void:
	if body is CharacterBody2D:
		get_node("/root/Loot&Roots/tavuk/TutorailPanel/VBoxContainer").visible = false
