# Mastering Python's Import Mysteries 🧪

Hoş geldiniz! (Welcome to the Alchemist's Laboratory!) 

Bu proje, Python programlamaya yeni başlayanlar için **Import (İçe Aktarma)** mantığını eğlenceli bir "Simya" temasıyla öğretmeyi amaçlayan bir çalışmadır. 

## 🌟 Proje Ne Hakkında?
Kod yazarken her şeyi tek bir dosyaya yazamayız. Kodlarımızı düzenli tutmak için farklı dosyalara ve klasörlere böleriz. Ancak bu dosyaların birbiriyle konuşabilmesi, birbirindeki güçleri (fonksiyonları) kullanabilmesi gerekir. İşte bu projede, elementler (Ateş, Su, Toprak, Hava) üreterek ve bunlardan iksirler yaparak Python'daki dosya iletişimini (import mekanizmasını) adım adım öğreniyoruz.

## 📁 Proje Yapısı ve Öğrettikleri

Proje 4 ana bölümden (Part) oluşur:

### Part 1: The Alembic (Temel Import ve Paketler)
- **Öğrenilenler:** Yan yana duran dosyalar birbirini nasıl tanır? Bir klasörü Python paketi yapmak için neden `__init__.py` dosyasına ihtiyacımız var? `__init__.py` dosyası ile neleri gizleyip neleri dışarıya açabileceğimizi nasıl kontrol ederiz?
- **Nasıl Çalıştırılır:** `python3 ft_alembic_0.py` (0'dan 5'e kadar test edebilirsiniz.)

### Part 2: Distillation (Alias - Takma İsimler)
- **Öğrenilenler:** Uzun dosya yollarını nasıl kısaltırız? Dışarıdan çağırdığımız bir özelliğe (fonksiyona) paket üzerinden nasıl daha kısa bir takma isim (Alias) veririz? (Örn: `alchemy.potions.healing_potion` yerine sadece `alchemy.heal` yazmak)
- **Nasıl Çalıştırılır:** `python3 ft_distillation_0.py` ve `python3 ft_distillation_1.py`

### Part 3: The Great Transmutation (Absolute vs Relative Imports)
- **Öğrenilenler:** Başka bir dosyanın yerini tarif ederken tam adresini (Absolute) vermek ile, "benim bulunduğum yerin bir üst klasöründe" (Relative) demek arasındaki fark nedir? Hangisi hangi durumlarda daha güvenlidir?
- **Nasıl Çalıştırılır:** `python3 ft_transmutation_0.py` (0, 1 ve 2. testler mevcuttur.)

### Part 4: Avoid the Explosion (Dairesel Bağımlılık - Circular Import)
- **Öğrenilenler:** A dosyası B'yi, B dosyası da A'yı aynı anda çağırırsa ne olur? (Cevap: Kod kilitlenir ve çöker!). Bu kısır döngüden (Circular Dependency) import kodunu dosyanın en üstüne değil de, kodun akışı içinde sadece gerektiği an (fonksiyonun içine) yazarak nasıl kurtuluruz?
- **Nasıl Çalıştırılır:** 
  - `python3 ft_kaboom_0.py` (Sorunsuz çalışan Işık Büyüsü)
  - `python3 ft_kaboom_1.py` (Bilerek patlatılan Kara Büyü)

## 🚀 Nasıl Başlarım?
Proje klasörünü bilgisayarınıza indirdikten sonra terminali (veya komut satırını) açın, bu klasörün içine girin ve test dosyalarını teker teker çalıştırın. Örneğin:

```bash
python3 ft_alembic_0.py
```

Her test dosyasının ekrana bastığı mesajı inceleyin. Ardından o test dosyasının (`ft_alembic_0.py`) kodlarını açarak hangi import yönteminin kullanıldığını gözlemleyin. Dosyaların birbirini nasıl çağırdığını anlamak, gelecekte yazacağınız büyük kod mimarilerinin temelini atacaktır.

Eğlenceli kodlamalar! 🐍✨
