extends Node2D
##
## İnek — Milestone 2 ile açılır.
## Besleme: Lahana  →  Ürün: Süt  →  Değer: 8 LRC
##

const FEED_ITEM: String = "lahana"
const PRODUCT_ITEM: String = "sut"
const PRODUCT_PRICE: int = 8
const FEED_LOG_HOURS: float = 24.0

var is_hungry: bool = true
var has_product: bool = false

signal product_ready(animal_name: String)


func _ready() -> void:
	_check_product_from_logtime()


func _check_product_from_logtime() -> void:
	if PlayerData.log_time_hours >= FEED_LOG_HOURS and not is_hungry:
		has_product = true
		emit_signal("product_ready", "inek")


func feed(item_name: String) -> bool:
	if item_name != FEED_ITEM:
		print("[İnek] Yanlış besin: %s (gereken: %s)" % [item_name, FEED_ITEM])
		return false
	if not Inventory.remove_item(item_name, 1):
		print("[İnek] Envanterde %s yok." % item_name)
		return false
	is_hungry = false
	print("[İnek] Beslendi!")
	_check_product_from_logtime()
	return true


func collect_product() -> String:
	if not has_product:
		print("[İnek] Henüz ürün yok.")
		return ""
	has_product = false
	is_hungry = true
	Inventory.add_item(PRODUCT_ITEM, 1)
	print("[İnek] %s toplandı!" % PRODUCT_ITEM)
	return PRODUCT_ITEM


func sell_product() -> int:
	if Inventory.remove_item(PRODUCT_ITEM, 1):
		PlayerData.add_lrc(PRODUCT_PRICE)
		print("[İnek] %s satıldı: %d LRC" % [PRODUCT_ITEM, PRODUCT_PRICE])
		return PRODUCT_PRICE
	return 0
