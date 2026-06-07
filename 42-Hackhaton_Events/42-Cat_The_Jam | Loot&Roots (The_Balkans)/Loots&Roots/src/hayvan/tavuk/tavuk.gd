extends Node2D
##
## Tavuk — Milestone 1 ile açılır.
## Besleme: Buğday  →  Ürün: Yumurta  →  Değer: 5 LRC
##

const FEED_ITEM: String = "bugday"
const PRODUCT_ITEM: String = "yumurta"
const PRODUCT_PRICE: int = 5
const FEED_LOG_HOURS: float = 24.0  # Her 24 saatlik log time → 1 ürün

var is_hungry: bool = true
var has_product: bool = false

signal product_ready(animal_name: String)


func _ready() -> void:
	_check_product_from_logtime()


func _check_product_from_logtime() -> void:
	## Log time 24+ saat → yumurta hazır
	if PlayerData.log_time_hours >= FEED_LOG_HOURS and not is_hungry:
		has_product = true
		emit_signal("product_ready", "tavuk")


func feed(item_name: String) -> bool:
	if item_name != FEED_ITEM:
		print("[Tavuk] Yanlış besin: %s (gereken: %s)" % [item_name, FEED_ITEM])
		return false
	if not Inventory.remove_item(item_name, 1):
		print("[Tavuk] Envanterde %s yok." % item_name)
		return false
	is_hungry = false
	print("[Tavuk] Beslendi!")
	# 24 saatlik log time kontrolü
	_check_product_from_logtime()
	return true


func collect_product() -> String:
	if not has_product:
		print("[Tavuk] Henüz ürün yok.")
		return ""
	has_product = false
	is_hungry = true
	Inventory.add_item(PRODUCT_ITEM, 1)
	print("[Tavuk] %s toplandı!" % PRODUCT_ITEM)
	return PRODUCT_ITEM


func sell_product() -> int:
	if Inventory.remove_item(PRODUCT_ITEM, 1):
		PlayerData.add_lrc(PRODUCT_PRICE)
		print("[Tavuk] %s satıldı: %d LRC" % [PRODUCT_ITEM, PRODUCT_PRICE])
		return PRODUCT_PRICE
	return 0
