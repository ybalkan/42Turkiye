extends Node
##
## Envanter singleton'ı. Tüm item'ları tutar.
## Hayvan ürünleri (yumur 	ta, sut, yun) de burada yönetilir.
##

# { "havuc": 5, "bugday": 2, "yumurta": 1, ... }
var items: Dictionary = {}

# LRC satış fiyatları
const SELL_PRICES: Dictionary = {
	"yumurta": 5,
	"sut": 8,
	"yun": 10,
}

signal inventory_changed(item_name: String, new_amount: int)
signal item_sold(item_name: String, amount: int, lrc_earned: int)


func add_item(item_name: String, amount: int = 1) -> void:
	if item_name in items:
		items[item_name] += amount
	else:
		items[item_name] = amount

	emit_signal("inventory_changed", item_name, items[item_name])
	print("[Inventory] +%d %s (toplam: %d)" % [amount, item_name, items[item_name]])


func get_amount(item_name: String) -> int:
	return items.get(item_name, 0)


func remove_item(item_name: String, amount: int = 1) -> bool:
	if get_amount(item_name) >= amount:
		items[item_name] -= amount
		emit_signal("inventory_changed", item_name, items[item_name])
		return true
	return false


func sell_item(item_name: String, count: int = 1) -> int:
	## Hayvan ürünlerini sat, LRC kazan.
	## Dönüş: kazanılan LRC miktarı (başarısızsa 0)
	if not item_name in SELL_PRICES:
		print("[Inventory] %s satılamaz (fiyat listesinde yok)." % item_name)
		return 0
	if not remove_item(item_name, count):
		print("[Inventory] Yeterli %s yok (istenen: %d, mevcut: %d)." % [item_name, count, get_amount(item_name)])
		return 0
	var lrc_earned: int = SELL_PRICES[item_name] * count
	PlayerData.add_lrc(lrc_earned)
	emit_signal("item_sold", item_name, count, lrc_earned)
	print("[Inventory] Satıldı: %dx%s → %d LRC" % [count, item_name, lrc_earned])
	return lrc_earned


func get_sellable_items() -> Dictionary:
	## Satılabilir itemların mevcut miktarını döndürür
	var result := {}
	for item_name in SELL_PRICES.keys():
		var amount := get_amount(item_name)
		if amount > 0:
			result[item_name] = amount
	return result
