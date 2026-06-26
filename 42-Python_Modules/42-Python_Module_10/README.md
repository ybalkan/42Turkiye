# FuncMage Projesi

Selam, bu proje Python'da "fonksiyonel programlama" mantığını oturtmak için hazırladığım 5 aşamalı bir çalışma. Klasik döngüler (`for`, `while`) ve upuzun fonksiyonlar yazmak yerine, daha az kodla daha akıllı işler (fonksiyonları birbirine paslamak, sarmalamak, tek satırda çözmek vb.) yapmaya odaklandım. Akılda kalıcı olsun diye de kodların tamamı büyücülük ve sihir teması (mage/spells vb.) üzerinden ilerliyor.

Aşağıda aşama aşama neler yaptığımı, hangi mantıkla hangi kodları yazdığımı detaylıca anlattım.



<img width="2049" height="1581" alt="Ekran Görüntüsü - 2026-06-26 01-45-43" src="https://github.com/user-attachments/assets/e72d2457-0da2-48ec-ae02-5ef59a2ffb98" />

---

## Adım Adım Neler Yaptım?

### 1. Adım: Lambda & Built-ins (`ex0/lambda_spells.py`)
İlk adımda uzun fonksiyon tanımlamalarından kurtulup isimsiz ve tek satırlık `lambda` fonksiyonlarını kullandım. Bunu Python'un gömülü fonksiyonlarıyla (`map`, `filter`, `sorted`) harmanladım:
- **`artifact_sorter`**: Elimdeki sihirli eşya (artifact) sözlüklerinden oluşan listeyi, sadece "power" değerlerine bakarak sıraladım. `sorted` içine `key=lambda...` vererek bunu tek satırda hallettim.
- **`power_filter`**: Tapınağa girmeye çalışan büyücüleri filtrelemek için `filter` fonksiyonunu kullandım. Sadece gücü belirli bir değerin üstünde olanları (yine lambda ile) geçirdim.
- **`spell_transformer`**: Listede duran büyü isimlerinin başına ve sonuna yıldız (`*`) eklemek için `map` fonksiyonunu kullandım. Bütün listeyi döngüye sokmadan tek hamlede dönüştürdüm.
- **`mage_stats`**: Listedeki büyücülerin istatistiklerini (min, max, average) çıkarmak için Python'un `min`, `max`, `sum`, `len` ve `round` fonksiyonlarını bir arada kullandım.

### 2. Adım: Higher-Order Functions (`ex1/higher_magic.py`)
Burada fonksiyonları birer veri tipi gibi (First-Class Citizen) kullanarak birbirlerine pasladım. Yani bir fonksiyon parametre olarak başka bir fonksiyon aldı veya geriye yepyeni bir fonksiyon döndürdü:
- **`spell_combiner`**: İki farklı büyüyü (iki ayrı fonksiyonu) parametre olarak alıp, ikisini de sırayla çalıştıran ve sonuçlarını birleştiren (tuple) bir yapı kurdum.
- **`power_amplifier`**: Bir fonksiyonun gücünü dışarıdan aldığı bir çarpan (multiplier) ile artıran ve geriye yükseltilmiş yepyeni bir fonksiyon döndüren bir güçlendirici yazdım.
- **`conditional_caster`**: Büyünün sadece belirli bir şart sağlandığında çalışmasını, aksi takdirde enerjiyi boşa harcamadan "fizzled" (patladı/söndü) döndürmesini sağlayan bir şartlayıcı (condition) fonksiyon ayarladım.
- **`spell_sequence`**: Bir sürü büyüyü liste halinde alıp, tek bir tetiklemeyle hepsini sırayla çalıştıran ve sonuçları liste olarak dönen bir seri atış mekanizması tasarladım.

### 3. Adım: Closure & Scope (`ex2/scope_mysteries.py`)
Bir fonksiyonun içinde başka bir fonksiyon tanımlayarak, içteki fonksiyonun dışarıdaki anlık durumu "hatırlamasını" (closure) sağladım. `global` kullanmak yasaktı, bu yüzden durumu korumak için `nonlocal` anahtar kelimesini kullandım:
- **`mage_counter`**: Her çağrıldığında 1 artan ama sayıyı globalde tutmayan, kendi izole hafızasında tutan bir sayaç yaptım. Birden fazla sayaç üretilirse birbirlerini etkilemiyorlar.
- **`spell_accumulator`**: Atılan büyülerin güçlerini toplayarak üstüne ekleyen (birikimli toplam) bir kara delik gibi çalışan kümülatif toplayıcı kurdum.
- **`enchantment_factory`**: Girdiğim formülü (örn: "Alevli") hatırlayıp, sonradan verilen her eşyayı bu formülle isimlendiren ("Alevli Kılıç", "Alevli Kalkan") bir seri üretim fabrikası ürettim.
- **`memory_vault`**: Sadece kendi içindeki `store` (kaydet) ve `recall` (çağır) alt fonksiyonlarıyla erişilebilen kırılmaz bir "hafıza kasası" oluşturdum. Dışarıdan bu sözlüğe doğrudan erişim yok.

### 4. Adım: Functools Kütüphanesi (`ex3/functools_artifacts.py`)
Daha karmaşık işlemleri daha kısa çözmek için Python'un standart kütüphanesinden `functools` ve `operator` modüllerine geçtim:
- **`spell_reducer`**: `functools.reduce` kullanarak bir listeyi baştan sona işleyip kümülatif olarak tek bir sayıya/değere indirgedim.
- **`partial_enchanter`**: Sürekli aynı argümanları alan büyüler için `functools.partial` kullandım. Parametrelerin bir kısmını önceden sabitleyip, eksik kısımları sonradan alan pratik "yarım parşömenler" elde ettim.
- **`memoized_fibonacci`**: Fibonacci gibi çok tekrarlı işlemlerde aynı hesabı tekrar yapmamak için fonksiyonun tepesine `@lru_cache` ekleyip hesaplamayı önbelleğe aldım.
- **`spell_dispatcher`**: Kendisine gönderilen verinin tipine (sayı mı, metin mi, liste mi?) bakarak farklı bir tepki vermesini sağlayan şekil değiştiren kapılar için `singledispatch` yapısını kullandım.

### 5. Adım: Decorators (`ex4/decorator_mastery.py`)
Son aşamada sarmalayıcı (decorator) mantığıyla orijinal fonksiyona hiç dokunmadan ona ek yetenekler kazandırdım. Kimliğini kaybetmemesi için hep `functools.wraps` kullandım:
- **`spell_timer`**: Çalıştırılan herhangi bir fonksiyonun ne kadar sürede tamamlandığını ölçen ve ekrana yazdıran bir zamanlayıcı zırhı yazdım.
- **`power_validator`**: Büyü atılmadan önce araya girip, büyücünün gücünün yetip yetmediğini kontrol eden bir gümrük muhafızı ekledim. Gücü yetmiyorsa asıl fonksiyonu hiç çalıştırmıyor.
- **`retry_spell`**: İçerideki fonksiyon `Exception` verirse işlemi sonlandırmak yerine 3 kez üst üste tekrar denemesini sağlayan inatçı bir yardımcı asistan ayarladım.
- **`MageGuild Sınıfı`**: Bütün bu öğrendiklerimi birleştiren bir sınıf (Class) yazdım. Üstüne bir de örnek (instance) oluşturmadan sadece sınıf adı üzerinden doğrudan çağrılabilen bir `@staticmethod` (`validate_mage_name`) tanımladım.

---

## Geliştirme Kuralları ve Notlarım

Projeyi geliştirirken sıkı sıkıya uyduğum bazı disiplin kuralları:
- **Yorumsuz Temiz Kod:** Kodların içinde `docstring` veya açıklama satırı (comment) bilerek bırakmadım. Kod bloklarının isimlendirmeleriyle ve yapısıyla kendini ifade etmesini istedim.
- **Tip Belirteçleri (Type Hinting):** Giren ve çıkan tüm verilerin tipini net olarak belirttim (`Callable`, `int`, `list`, `str` vb.). Kodun anlaşılabilirliği bu sayede arttı.
- **Sadece Standart Kütüphane:** Dışarıdan (`pip` üzerinden) hiçbir eklenti kurmadım, her şeyi saf Python standartlarıyla hazırladım. 
- **Güvenli Kod:** `eval` veya `exec` gibi ne çalıştıracağı belli olmayan riskli kodlardan uzak durdum.
- **Okunabilirlik (PEP-8):** Kodları yazarken hiçbir satırın 79 karakteri (flake8 kuralları) aşmamasına özen gösterdim.

## Nasıl Çalıştırılır?

Projenin içinde hiçbir harici bağımlılık yoktur (requirements.txt vb. gerekmiyor). İncelemek istediğiniz ilgili adımı doğrudan terminal üzerinden şu şekilde çalıştırabilirsiniz:

```bash
python3 ex0/lambda_spells.py
```
*(Diğer aşamalar da aynı formatta kendi yollarında sorunsuzca çalışacaktır.)*
