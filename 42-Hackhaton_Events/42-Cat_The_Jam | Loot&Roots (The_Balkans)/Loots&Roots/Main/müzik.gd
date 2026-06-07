extends Node

@export var music: AudioStream

func _ready() -> void:
	var player = AudioStreamPlayer.new()
	add_child(player)
	player.stream = music
	player.volume_db = 0.0  # sesi ayarla -10, -20 gibi kısabilirsin
	player.play()
	player.finished.connect(func(): player.play())  # bitince tekrar başlat
