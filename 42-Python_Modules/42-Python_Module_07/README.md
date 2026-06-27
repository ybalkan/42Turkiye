# DataDeck — Abstract Card Architecture

> **Python 3.10+ · flake8 · mypy --strict**

Creature tabanlı bir kart oyunu altyapısı. Üç tasarım desenini (Abstract Factory, Capability/Mixin, Strategy) katmanlı biçimde uygular.

---

## 📂 Adım Adım Ne Yaptım? (Yeni Başlayanlar İçin Rehber)

Eğer Design Patterns dünyasına ilk adımını atıyorsan, bu süreci şöyle incelemelisin:

### **ex0 / Abstract Factory (`battle.py`)**
*   **Ne Öğrendim?** Nesne üretimini standartlaştırmak.
*   **Adım Adım:** Flameling isimli yaratığı elimle oluşturmadım. Bir `FlameFactory` yazdım. Bu fabrika bana ateş elementli baz yaratıklar veya gelişmiş (`Pyrodon`) yaratıklar verebiliyor. `AquaFactory` de aynı komutlarla su yaratıkları veriyor. Hangi fabrikayı kullandığımı umursamadan kod yazabildim (Polimorfizm).

### **ex1 / Capabilities / Mixin (`capacitor.py`)**
*   **Ne Öğrendim?** Eklenti (Plugin) mantığı ile yetenek kazandırmak.
*   **Adım Adım:** Yaratıklara yeni bir sınıf türetmeden "Heal" (İyileştirme) ve "Transform" (Dönüşüm) özellikleri ekledim. `Shiftling` yaratığı normalde sadece vururken, Transform yeteneği sayesinde `attack() → transform() → attack() → revert()` döngüsüne sahip oldu. Özellikler yaratıktan bağımsız yaşıyor!

### **ex2 / Strategy Pattern (`tournament.py`)**
*   **Ne Öğrendim?** Algoritmayı dışarıdan yönetmek.
*   **Adım Adım:** Karakterin saldırı mantığını içine yazmadım. Dışarıda `NormalStrategy`, `AggressiveStrategy`, `DefensiveStrategy` isimli beyinler tasarladım. Karakter savaşa girerken ona bir beyin atadım. Karakter sadece `execute()` dedi, gerisini o an kafasındaki beyin halletti.

---

## 🎨 Proje Görselleri ve Yapısı

**Proje Diyagramları:**
<img width="3388" height="1372" alt="Ekran Görüntüsü - 2026-06-23 12-25-36" src="https://github.com/user-attachments/assets/715d9935-77df-49fd-b948-6caabeeec43d" />
<img width="3494" height="1371" alt="Ekran Görüntüsü - 2026-06-23 14-05-47" src="https://github.com/user-attachments/assets/57c14873-265b-4d8c-bb27-281876047232" />
<img width="949" height="368" alt="Ekran Görüntüsü - 2026-06-23 14-26-30" src="https://github.com/user-attachments/assets/7aef9560-2b9b-4ae6-a49e-b9b7b8b67ace" />





---

## Proje Yapısı

```
py07/
├── ex0/                    ← Abstract Factory
│   ├── creature.py         Tüm yaratık sınıfları
│   ├── factory.py          Fabrika sınıfları
│   └── __init__.py         Dışarıya sadece fabrikalar açık
│
├── ex1/                    ← Capabilities (Mixin)
│   ├── capability.py       HealCapability, TransformCapability
│   ├── creature.py         Yetenekli yaratıklar
│   ├── factory.py          Yetenekli fabrikalar
│   └── __init__.py
│
├── ex2/                    ← Strategy Pattern
│   ├── strategy.py         Normal / Aggressive / Defensive strateji
│   └── __init__.py
│
├── battle.py               python3 battle.py      → ex0 testi
├── capacitor.py            python3 capacitor.py   → ex1 testi
├── tournament.py           python3 tournament.py  → ex2 testi
│
├── anlatim/                Türkçe dokümantasyon
│   ├── ana_amac.md         Her exercise'ın kısa amacı
│   ├── genel_bakis.md      Dosya akışları ve metaforlu açıklamalar
│   ├── ex0_anlatim.md      EX0 detaylı anlatım
│   ├── ex1_anlatim.md      EX1 detaylı anlatım
│   ├── ex2_anlatim.md      EX2 detaylı anlatım
│   └── yorum.md            Satır satır yorum açıklamaları
│
└── .gitignore
```

---

## Çalıştırma

```bash
python3 battle.py       # EX0 — Abstract Factory
python3 capacitor.py    # EX1 — Capabilities
python3 tournament.py   # EX2 — Strategy + Turnuva
```

---

## Exercises

### EX0 — Abstract Factory · `battle.py`

Yaratıkları doğrudan sen üretmiyorsun, **fabrikaya sipariş veriyorsun.**

| Aile | Temel | Gelişmiş |
|---|---|---|
| 🔥 Ateş | Flameling | Pyrodon |
| 💧 Su | Aquabub | Torragon |

```
FlameFactory → create_base()    → Flameling
             → create_evolved() → Pyrodon
AquaFactory  → create_base()    → Aquabub
             → create_evolved() → Torragon
```

> Aynı `test_factory()` fonksiyonu her iki fabrika için değişmeden çalışır — **polimorfizm**.

---

### EX1 — Capabilities · `capacitor.py`

Ex0'ın üzerine yaratıklara **aksesuar** (yetenek) takılır. Yetenekler `Creature`'dan bağımsızdır.

| Yetenek | Yaratıklar | Metotlar |
|---|---|---|
| 🌿 Heal | Sproutling, Bloomelle | `attack()` + `heal()` |
| 🔀 Transform | Shiftling, Morphagon | `attack()` → `transform()` → `attack()` → `revert()` |

```
Shiftling.transform()  →  transformed = True
Shiftling.attack()     →  "boosted strike!"   ← aynı metot, farklı çıktı
Shiftling.revert()     →  transformed = False
```

---

### EX2 — Strategy Pattern · `tournament.py`

Ex0 + Ex1'in üzerine **strateji sistemi** ve **turnuva** eklenir.

| Strateji | Uyumlu Yaratık | Eylem |
|---|---|---|
| NormalStrategy | Hepsi | `attack()` |
| AggressiveStrategy | TransformCapability | `transform()` → `attack()` → `revert()` |
| DefensiveStrategy | HealCapability | `attack()` → `heal()` |

```
Uyumsuz kombinasyon → ValueError → turnuva durur
3 rakip             → 3 maç (her çift bir kez)
```

---

## Kural Zinciri

```
ex0  ──►  Creature + Factory sistemi kurulur
  │
  ▼
ex1  ──►  ex0'ı alır, Capability + Mixin eklenir
  │
  ▼
ex2  ──►  ex0 + ex1'i alır, Strategy + Tournament çalışır
```

---

## Doğrulama

```bash
python3 -m flake8 ex0/ ex1/ ex2/ battle.py capacitor.py tournament.py
python3 -m mypy   ex0/ ex1/ ex2/ battle.py capacitor.py tournament.py --strict
```

---
<img width="949" height="368" alt="Ekran Görüntüsü - 2026-06-23 14-26-53" src="https://github.com/user-attachments/assets/ee48b452-31b5-410c-8385-e664b5f82e0f" />

