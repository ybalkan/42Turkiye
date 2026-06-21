# Python İçe Aktarma (Import) Sırları - Öğrenim Rehberi

Bu projenin temel amacı şudur: **Python'da farklı dosya ve klasörler birbirleriyle nasıl iletişim kurar? Kodlarımızı nasıl yönetiriz?** 

Projenin mantığına inmeden önce, projede çok sık geçen terimleri bilmen konuyu çok daha rahat anlamanı sağlayacaktır:

## 📚 Terimler Sözlüğü (İlk Kez Duyanlar İçin)
* **Module (Modül):** İçerisinde Python kodları (fonksiyonlar, değişkenler vb.) barındıran, bildiğimiz sıradan bir `.py` uzantılı dosyadır (Örn: `elements.py`).
* **Package (Paket):** İçerisinde birden fazla modül (dosya) barındıran ve Python'un burayı bir kütüphane olarak algılaması için içine mutlaka `__init__.py` dosyası konulmuş klasördür.
* **Import (İçe Aktarma):** Başka bir dosyada veya klasörde yazılmış olan kodları (fonksiyonları) bulunduğumuz dosyada kullanabilmek için içeri çağırma işlemidir.
* **Alias (Takma İsim):** Çok uzun dosya yollarını, kodun içinde kullanırken `as` kelimesi ile kısaltmaktır. (Örn: `import pandas as pd`)
* **Absolute Import (Mutlak İçe Aktarma):** Bir dosyayı çağırırken en dıştaki ana klasörden başlayarak adresi tam ve eksiksiz olarak yazmaktır.
* **Relative Import (Göreceli İçe Aktarma):** Bir dosyayı çağırırken "noktalar" (`.` veya `..`) kullanarak, tam adres vermek yerine "bir üst klasöre çık" gibi yön tarif etmektir.
* **Circular Dependency (Dairesel Bağımlılık):** İki kod dosyasının (A ve B) sonsuz bir döngüde birbirini beklemesi/çağırması ve programın içinden çıkamayıp patlaması (`ImportError`) durumudur.

---

## 1. Paketler (Packages) ve `__init__.py` Dosyası
**Konu:** Yan yana duran veya klasör içindeki kod dosyaları birbirini nasıl görür?

* **Olay Nedir?** Python, içerisinde kod dosyaları olan her klasörü otomatik olarak bir "kod kütüphanesi" (paket) olarak kabul etmez. Python'un o klasörü tanıyıp içindeki dosyalara dışarıdan izin vermesi için o klasörün içine boş da olsa bir `__init__.py` dosyası koymalıyız.
* **Gizlilik Kontrolü:** `__init__.py` sadece klasörü tanıtmakla kalmaz, vitrin görevi de görür. Bu projede, toprak elementini (`create_earth`) `__init__.py` içerisine **koymadık**. Böylece dışarıdan biri `alchemy.create_earth` diye toprak elementini çağırmaya çalıştığında `AttributeError` (hata) aldı. 
* **Öğrendiğimiz şey:** Hangi kodları dış dünyaya açıp, hangi kodları projemizin içinde gizli tutacağımızı `__init__.py` kullanarak yönetebiliriz.

---

## 2. Takma İsimler / Alias Mantığı
**Konu:** Çok uzun dosya uzantılarını kod yazarken nasıl pratikleştiririz?

* **Olay Nedir?** Bazen bir fonksiyonu çağırmak çok uzun sürer: `alchemy.potions.healing_potion`. 
* **Çözüm:** `__init__.py` dosyasına girip ona bir takma ad atayabiliriz (`from .potions import healing_potion as heal` şeklinde).
* **Öğrendiğimiz şey:** Takma isim (Alias) sayesinde kodun geri kalanında uzun adresler yerine sadece `alchemy.heal` yazarak büyük bir kolaylık ve okunabilirlik sağlarız.

---

## 3. Absolute (Mutlak) vs Relative (Göreceli) Import
**Konu:** Başka bir dosyayı çağırırken (import ederken) adresi nasıl vermeliyiz? İki yöntemin farkı nedir?

Projede `recipes.py` dosyasını oluştururken bilerek bu iki farklı yöntemi de kullandık:

**A) Absolute (Mutlak) Import**
* **Nasıl yazılır?** `from alchemy.potions import strength_potion`
* **Mantığı:** Adresi Türkiye'den, şehirden, sokaktan başlayarak tam ve eksiksiz vermektir.
* **Avantajı:** Kodu okuyan kişi dosyanın tam olarak nereden geldiğini şıp diye anlar.
* **Dezavantajı:** Eğer en dıştaki `alchemy` klasörünün adını yarın `magic` diye değiştirirsek, adres bozulduğu için bütün kodlar tek tek patlar ve hepsini elinle düzeltmen gerekir.

**B) Relative (Göreceli) Import**
* **Nasıl yazılır?** `from ..elements import create_air`
* **Mantığı:** Yön tarifi vermek gibidir. Baştaki iki nokta `..` demek: **"Şu an bulunduğum klasörden bir üst klasöre çık, oradaki elements dosyasına gir"** demektir. (Tek nokta `.` olsaydı "bulunduğum klasördeki" anlamına gelirdi).
* **Avantajı:** Ana klasörün adı `alchemy` iken `magic` olsa bile kod bozulmaz. Çünkü adrese değil, yön tarifine (yukarı çık/aşağı in) bakar.
* **Dezavantajı:** Eğer kodu alıp klasörün içinde başka derinlikte bir yere taşırsan, yön tarifi ("bir üst klasöre çık") bozulacağı için kod çalışmaz.

---

## 4. Dairesel Bağımlılık (Circular Dependency)
**Konu:** Dosyalar karşılıklı olarak birbirini çağırdığında kopan felaket ve çözümü.

* **Olay Nedir?** Diyelim ki **A** dosyası çalışmak için **B**'ye, **B** dosyası da çalışmak için **A**'ya muhtaç.
* **Kara Büyü (Patlayan Kod):** Eğer import işlemlerini (sayfayı içeri aktarmayı) dosyaların **en tepesine** yazarsanız, kod ilk okunduğunda A dosyası B'yi ister, B dosyasına gider o da A'yı ister. Sistem kimin kime muhtaç olduğunu çözemeyip kilitlenir ve `ImportError` fırlatıp çöker. 
* **Işık Büyüsü (Çözen Kod):** Bu döngüden kurtulmanın yolu, `import` işlemini sayfanın en üstüne **yazmamaktır**. İçe aktarma kodunu, direkt olarak o fonksiyona ihtiyaç duyduğumuz satırın içine (yani kendi `def` blokumuzun içine) yazarız. Buna **lokal import** denir. Kod ilk okunurken import işlemi es geçilir, böylece dosyalar birbirini kitlemez. Sadece ve sadece o fonsiyon çalıştırıldığında o anlık dosya import edilir.

> **Özetle:** Dosyaların ilk satırlarında birbirlerini sonsuz bir Import döngüsüne sokmasına Dairesel Bağımlılık denir ve import işlemlerini fonksiyon içerisine (aşağılara) alarak bu sorundan kaçınılır.
