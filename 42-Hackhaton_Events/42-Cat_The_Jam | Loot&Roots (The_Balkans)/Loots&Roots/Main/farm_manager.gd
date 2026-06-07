extends Node2D
##
## FarmManager — Tarla slotlarını, tohum ekimini ve su kovası mekaniklerini yönetir.
##

const CROPS = {
	"havuc": preload("res://src/tarla/havuc/havuc.tscn"),
	"bugday": preload("res://src/tarla/buğday/bugday.tscn"),
	"lahana": preload("res://src/tarla/lahana/lahana.tscn"),
}

# Bitki adı → Türkçe görüntü adı
const CROP_LABELS = {
	"bugday": "Buğday",
	"lahana": "Lahana",
	"havuc": "Havuç",
}

var selected_slot: int = -1
var slot_occupied: Array = []
var slot_crops: Array = []   # Her slottaki bitki düğümü (null = boş)
var crop_menu: PopupMenu
var _locked_items: Array = []  # Kilidi açık olmayan menü itemları


func _ready() -> void:
	for i in $FarmArea/Slots.get_children().size():
		slot_occupied.append(false)
		slot_crops.append(null)

	crop_menu = PopupMenu.new()
	add_child(crop_menu)

	var theme = Theme.new()
	theme.default_font_size = 20
	crop_menu.theme = theme
	crop_menu.min_size = Vector2(200, 0)

	crop_menu.id_pressed.connect(_on_crop_selected)

	var slots = $FarmArea/Slots.get_children()
	for i in slots.size():
		slots[i].input_event.connect(_on_slot_clicked.bind(i))


func _build_crop_menu() -> void:
	crop_menu.clear()
	_locked_items.clear()
	var crops_ordered := ["bugday", "lahana", "havuc"]
	for id in crops_ordered.size():
		var crop_name: String = crops_ordered[id]
		var is_unlocked: bool = PlayerData.is_crop_unlocked(crop_name)
		var seed_count: int = PlayerData.seeds.get(crop_name, 0)
		var label: String = CROP_LABELS.get(crop_name, crop_name)

		if is_unlocked:
			crop_menu.add_item("%s  [%d tohum]" % [label, seed_count], id)
			if seed_count <= 0:
				# Tohum yok → disable
				var idx := crop_menu.get_item_index(id)
				crop_menu.set_item_disabled(idx, true)
		else:
			crop_menu.add_item("🔒 %s  [Milestone %d]" % [label, _required_milestone(crop_name)], id)
			var idx := crop_menu.get_item_index(id)
			crop_menu.set_item_disabled(idx, true)
			_locked_items.append(id)


func _required_milestone(crop_name: String) -> int:
	match crop_name:
		"bugday": return 0
		"lahana": return 1
		"havuc":  return 2
		_:        return 99


func _on_slot_clicked(_viewport, event: InputEvent, _shape, slot_index: int) -> void:
	if event is InputEventMouseButton and event.pressed:
		if event.button_index == MOUSE_BUTTON_LEFT:
			if not slot_occupied[slot_index]:
				selected_slot = slot_index
				_build_crop_menu()
				crop_menu.popup()
				crop_menu.position = Vector2i(event.position)


func _on_crop_selected(id: int) -> void:
	if selected_slot == -1:
		return
	if id in _locked_items:
		selected_slot = -1
		return

	var crop_name: String = (["bugday", "lahana", "havuc"] as Array[String])[id]

	# Tohum kontrolü
	if not PlayerData.use_seed(crop_name):
		print("[FarmManager] Yeterli %s tohumu yok!" % crop_name)
		selected_slot = -1
		return

	_spawn_crop(crop_name, selected_slot)
	selected_slot = -1


func _spawn_crop(crop_name: String, slot_index: int) -> void:
	var slots = $FarmArea/Slots.get_children()
	var crop = CROPS[crop_name].instantiate()
	add_child(crop)
	crop.global_position = slots[slot_index].global_position
	slot_occupied[slot_index] = true
	slot_crops[slot_index] = crop
	print("[FarmManager] Ekildi: %s slot %d" % [crop_name, slot_index])


func water_all_crops() -> void:
	## Su kovası: tüm aktif bitkiler anında max aşamaya gelir
	if PlayerData.water_buckets <= 0:
		print("[FarmManager] Su kovası yok!")
		return
	PlayerData.water_buckets -= 1
	for crop in slot_crops:
		if crop != null and is_instance_valid(crop):
			if crop.has_method("force_max_stage"):
				crop.force_max_stage()
	print("[FarmManager] Tüm bitkiler sulandı! Kalan kova: %d" % PlayerData.water_buckets)


func free_slot(slot_index: int) -> void:
	## Hasat sonrası slot'u serbest bırak (bitkiler bunu çağırabilir)
	slot_occupied[slot_index] = false
	slot_crops[slot_index] = null
