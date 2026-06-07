extends Control
##
## Depo envanter paneli — çiftlik teması, sıcak toprak renkleri.
##

@export var item_icons: Dictionary = {
	"havuc": preload("res://src/tarla/havuc/havuc_icon.png"),
	"bugday": preload("res://src/tarla/buğday/bugday_icon.png"),
	"lahana": preload("res://src/tarla/lahana/lahana_icon.png"),
}

const ORAK_ICON := "res://assets/orak_icon.png"

@onready var vbox: VBoxContainer = $VBoxContainer


func _ready() -> void:
	visible = false
	z_index = 100          # Her şeyin üstünde görünsün
	z_as_relative = false  # Absolute z-index kullan
	_add_background()
	Inventory.inventory_changed.connect(_on_inventory_changed)
	_refresh_display()


func _add_background() -> void:
	## VBoxContainer'ın arkasına toprak renkli düz arka plan ekle

	# Tam arka plan — toprak bej
	var bg := ColorRect.new()
	bg.color = Color("#e8d5a3")   # sıcak buğday sarısı
	bg.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	# VBoxContainer sol tarafa doğru büyüyor (-0.95 scale). Daha küçük bir dikdörtgen:
	bg.offset_left   = -110
	bg.offset_right  =  80
	bg.offset_top    = -120
	bg.offset_bottom =  150
	bg.z_index = -1
	add_child(bg)
	move_child(bg, 0)   # en arkaya al

	# İnce kahverengi kenarlık şeridi (üst)
	var top_border := ColorRect.new()
	top_border.color = Color("#7a4e1e")
	top_border.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	top_border.offset_left   = -110
	top_border.offset_right  =  80
	top_border.offset_top    = -120
	top_border.offset_bottom = -116
	top_border.z_index = 0
	add_child(top_border)

	# Alt kenarlık
	var bot_border := ColorRect.new()
	bot_border.color = Color("#7a4e1e")
	bot_border.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	bot_border.offset_left   = -110
	bot_border.offset_right  =  80
	bot_border.offset_top    =  146
	bot_border.offset_bottom =  150
	bot_border.z_index = 0
	add_child(bot_border)


func _on_inventory_changed(_item_name: String, _amount: int) -> void:
	_refresh_display()


func _refresh_display() -> void:
	for child in vbox.get_children():
		child.queue_free()

	# ── Başlık satırı: orak ikonu + "Envanter" yazısı ──
	var title_row := HBoxContainer.new()
	title_row.alignment = BoxContainer.ALIGNMENT_CENTER
	title_row.add_theme_constant_override("separation", 6)
	vbox.add_child(title_row)

	# Orak ikonu (import hatasını önlemek için Image üzerinden direkt yüklüyoruz)
	var orak_img := Image.new()
	if orak_img.load("res://assets/orak_icon.png") == OK:
		var orak := TextureRect.new()
		orak.texture = ImageTexture.create_from_image(orak_img)
		orak.custom_minimum_size = Vector2(20, 20)
		orak.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
		orak.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
		title_row.add_child(orak)

	var title := Label.new()
	title.text = "Envanter"
	title.add_theme_font_size_override("font_size", 13)
	title.add_theme_color_override("font_color", Color("#4a2408"))
	title_row.add_child(title)

	# Buğday ikonu
	if "bugday" in item_icons:
		var bugday_ic := TextureRect.new()
		bugday_ic.texture = item_icons["bugday"]
		bugday_ic.custom_minimum_size = Vector2(20, 20)
		bugday_ic.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
		bugday_ic.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
		title_row.add_child(bugday_ic)

	# ── Ayırıcı çizgi ──
	var sep := ColorRect.new()
	sep.color = Color("#a0784a")
	sep.custom_minimum_size = Vector2(150, 1)
	vbox.add_child(sep)

	# ── İçerik ──
	if Inventory.items.is_empty():
		var empty_lbl := Label.new()
		empty_lbl.text = "Henüz ürün yok."
		empty_lbl.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
		empty_lbl.add_theme_font_size_override("font_size", 11)
		empty_lbl.add_theme_color_override("font_color", Color("#7a5535"))
		vbox.add_child(empty_lbl)
		return

	for item in Inventory.items:
		var amount: int = Inventory.items[item]

		var hbox := HBoxContainer.new()
		hbox.custom_minimum_size = Vector2(150, 30)
		hbox.add_theme_constant_override("separation", 8)

		if item in item_icons:
			var icon := TextureRect.new()
			icon.custom_minimum_size = Vector2(24, 24)
			icon.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
			icon.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
			icon.texture = item_icons[item]
			hbox.add_child(icon)

		var label := Label.new()
		label.text = "%s: %d" % [item, amount]
		label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
		label.add_theme_font_size_override("font_size", 12)
		label.add_theme_color_override("font_color", Color("#3b2008"))
		hbox.add_child(label)

		vbox.add_child(hbox)


func toggle() -> void:
	visible = !visible
