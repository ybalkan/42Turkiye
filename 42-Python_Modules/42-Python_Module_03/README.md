# Python_Module_03 - Veri Macerası (Veri İşleme ve Formatlama) ⚔️

Selam! Veriler bize her zaman mükemmel temizlikte gelmez. Bu modülde bir RPG (Rol Yapma Oyunu) teması üzerinden, karmaşık ve kirli metin/veri yığınlarını nasıl parçalayacağımı, dönüştüreceğimi ve anlamlı hale getireceğimi öğrendim. Ham veriyi adeta altına çeviren bir simyacı/maceracı oldum!

## 🎯 Bu Modülde Asıl Öğrenmemiz Gerekenler

Bu modülü bitirdiğinizde şunları çok rahat yapıyor olmalısınız:
1.  **String (Metin) Manipülasyonları:** Gelen devasa bir metni boşluklardan, virgüllerden veya özel karakterlerden ayırıp (`.split()`) listelere bölmek veya listeleri tekrar birleştirmek (`.join()`).
2.  **String Formatlama (`f-string`):** Değişkenleri uzun uzun artı (`+`) işaretleriyle birleştirmek yerine, metinlerin içine süslü parantezlerle dinamik bir şekilde gömmek.
3.  **İleri Seviye Döngüler ve Koşullar:** Liste içinde liste (matrix) dolaşmak, verileri filtreden geçirmek.
4.  **Algoritmik Veri Dönüşümleri:** Girdi (input) ne kadar farklı formatta gelirse gelsin, istediğimiz çıktı (output) formatına kod yazarak çevirebilmek.

---

## 🧠 Teknik ve Metaforik Bakış

*   **Teknik Olarak:** Stringler Python'da değiştirilemez (immutable) dizilerdir. Bir string üzerinde `.replace()` veya `.upper()` gibi bir işlem yaptığınızda orijinal metin değişmez, bellekte yeni bir metin objesi yaratılır. Veri işlerken hafıza yönetimini ve metotların zincirleme (chaining) kullanımını bilmek kodun hem kısa hem hızlı çalışmasını sağlar.
*   **Metaforik Olarak:** Size ormandan toplanmış dallı, çamurlu, taşlı karışık bir sepet elma geliyor (Ham Veri). Sizin göreviniz bu elmaları yıkamak (temizlemek/formatlamak), çürükleri ayıklamak (filtrelemek) ve fırınlayıp mükemmel bir elmalı turta (İşlenmiş Veri / Analiz Sonucu) olarak sunmaktır.

---

## 📂 Adım Adım Ne Yaptım? (Yeni Başlayanlar İçin Rehber)

Eğer veri işlemeye yeni giriyorsan, RPG karakteri yaratır gibi şu adımları takip etmelisin:

### **ex0 / Görev Başlangıcı (Komut Ayıklama)**
*   **Ne Öğrendim?** Girdi temizliği.
*   **Adım Adım:** Kullanıcıdan "  saldır ejderha  " gibi başında sonunda boşluk olan düzensiz komutlar geldiğini varsay. `.strip()` kullanarak bu gereksiz boşlukları tıraşlamayı ve temiz bir komut elde etmeyi öğrendim.

### **ex1 / Skor Analitiği (Döngülerle Veri Çekme)**
*   **Ne Öğrendim?** Listelerin içinden matematiksel anlam çıkarmak.
*   **Adım Adım:** Bir sayı listesi üzerinde `for` döngüsü ile dolaşarak, Python'un hazır `max()`, `min()` metodlarını kullanmadan kendi mantığımla en yüksek veya en düşük skoru hesaplayan algoritmalar yazdım.

### **ex2 / Koordinat Sistemi (Matematiksel Güncellemeler)**
*   **Ne Öğrendim?** Birden fazla değişkeni aynı anda kontrol etmek.
*   **Adım Adım:** Karakterin bir x ve y konumu var. Gelen yön komutlarına (Kuzey, Güney) göre bu x, y değerlerini koşul bloklarıyla (`if-elif`) doğru şekilde artırıp azalttım.

### **ex3 / Başarı Takibi (f-string ile Formatlama)**
*   **Ne Öğrendim?** Ekrana güzel ve okunaklı yazılar basmak.
*   **Adım Adım:** `print("Tebrikler " + oyuncu_adi + ", seviyen " + str(seviye))` gibi çirkin bir kod yerine, `print(f"Tebrikler {oyuncu_adi}, seviyen {seviye}!")` diyerek kodun içine değişkenleri muazzam bir şekilde yerleştirmeyi kavradım.

### **ex4 / Envanter Sistemi (Sözlük Manipülasyonu)**
*   **Ne Öğrendim?** Dinamik veritabanı mantığı.
*   **Adım Adım:** Bir sözlükte (envanterde) o eşya var mı diye kontrol edip (`if item in inventory:`), varsa sayısını artırma, yoksa sözlüğe yeni bir kayıt olarak ekleme yeteneği kazandım.

### **ex5 & ex6 / Veri Akışı ve Simyacı (Split, Join, Replace)**
*   **Ne Öğrendim?** Gerçek veri analisti gibi çalışmak!
*   **Adım Adım:** `100,Kılıç,Hasarlı|200,Kalkan,Yeni` gibi tamamen anlamsız görünen düz bir metni aldım. Önce `|` işaretinden `.split('|')` ile böldüm. Sonra döngüye sokup her birini `,` işaretinden böldüm. Elime harika düzenli bir Liste geldi. String metodlarını zincirleme kullanarak imkansız görünen verileri çözdüm.
