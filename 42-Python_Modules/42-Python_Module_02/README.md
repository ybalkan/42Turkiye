# Python_Module_02 - Hata Yakalama Sanatı (Exceptions) 🚨

Selam! Yazılımda her şey yolunda gitmez. Kullanıcı harf yerine sayı girer, internet kopar, dosya bulunamaz... İşte programın aniden kırmızı yazılar fırlatıp patlamasını (crash) engellediğimiz ve kontrolü ele aldığımız yer burası. Bu modülde hatalara kafa tutmayı öğrendim.

## 🎯 Bu Modülde Asıl Öğrenmemiz Gerekenler

Bu modülü bitirdiğinizde şunlara tam anlamıyla hakim olmalısınız:
1.  **Try-Except Blokları:** Hata üretebilecek riskli kodları koruma altına almak.
2.  **Özel Hata Yakalama:** Tüm hataları körü körüne yakalamak yerine (`except Exception:` kullanmak çok tehlikelidir), sadece beklediğiniz belirli hataları (`ValueError`, `TypeError` gibi) yakalamak.
3.  **Kendi Hatanı Fırlatma (`raise`):** Program teknik olarak çökmemiş olsa bile, iş mantığına aykırı bir durum olduğunda (örn: şifrenin çok kısa olması) kendi kontrolümüzle hata fırlatmak.
4.  **Custom Exceptions:** Python'un yerleşik hatalarının yetersiz kaldığı büyük projelerde, kendi hata sınıflarımızı (Class) yaratmak.
5.  **Temizlik Aşaması (`finally`):** Kod hata versin veya vermesin, çalışmasını kesinlikle garanti altına aldığımız bloklar oluşturmak.

---

## 🧠 Teknik ve Metaforik Bakış

*   **Teknik Olarak:** Bir Exception fırlatıldığında, Python "Call Stack" (çağrı yığını) boyunca geriye doğru bu hatayı yakalayacak bir `except` bloğu arar. Eğer en üste kadar bulamazsa program `Traceback` fırlatır ve kapanır. Exception yakalamak biraz performans maliyetine sahiptir, bu yüzden sadece istisnai durumlar için kullanılmalıdır, normal akış kontrolü (`if-else` yerine) için kullanılmamalıdır.
*   **Metaforik Olarak:** Bir sirkte akrobat (Kod) ipin üstünde yürüyor. Aşağıda bir güvenlik ağı (Try-Except) var. Akrobat düşerse (Hata/Exception), ağ onu yakalar ve şovun iptal olmasını (Crash) engeller, akrobat gösteriye kaldığı yerden devam edebilir. `Finally` ise, akrobat düşse de düşmese de şov sonunda o ipin oradan toplanmasıdır.

---

## 📂 Adım Adım Ne Yaptım? (Yeni Başlayanlar İçin Rehber)

Eğer hatalarla yeni başa çıkıyorsan, şu adımları izlemelisin:

### **ex0 / Güvenlik Ağı Germek (`try-except`)**
*   **Ne Öğrendim?** Programın çökmesini önlemek.
*   **Adım Adım:** Kırılgan olan (mesela matematiksel bir bölme işlemi) kodları `try:` bloğunun içine yaz. Hemen altına `except:` yazarak hata durumunda ne ekrana basılacağını veya ne önlem alınacağını belirle. Program artık kırmızı bir hata mesajı kusup kapanmaz.

### **ex1 / Kasten Hata Çıkarmak (`raise`)**
*   **Ne Öğrendim?** Kurallara uymayan duruma anında itiraz etmek.
*   **Adım Adım:** Diyelim ki bir sisteme yaş girilecek. Kullanıcı "-5" girdi. Python bunu teknik olarak bir hata görmez çünkü -5 bir tam sayıdır. Ama gerçek hayatta hata! Koduna `if yas < 0:` yazıp altına `raise ValueError("Yaş negatif olamaz!")` yazarak kontrolü sen sağla.

### **ex2 / Her Hataya Ayrı Muamele**
*   **Ne Öğrendim?** Hatanın tipini bilmek ve ona göre davranmak.
*   **Adım Adım:** Sadece `except:` yazıp geçme. `except ValueError:` yazarsan sayı dönüştürme hatalarını yakalarsın. Altına bir tane de `except ZeroDivisionError:` eklersen, sıfıra bölme hatasını yakalarsın. Hangi hata geldiyse ilgili bloğa girer!

### **ex3 / Kendi Hata Türünü Yaratmak (Custom Exceptions)**
*   **Ne Öğrendim?** Projeye özel isimlendirilmiş hatalar.
*   **Adım Adım:** Python'daki `Exception` sınıfından miras alarak boş bir sınıf oluştur. Mesela `class UserBannedError(Exception): pass`. Artık engellenmiş bir kullanıcı sisteme girmeye çalıştığında bu kendi özel isimlendirdiğin hatayı fırlatabilirsin. Kodu okuyan kişi anında ne olduğunu anlar.

### **ex4 / Her Şeye Rağmen Çalışacak Kod (`finally`)**
*   **Ne Öğrendim?** Arkamı temizlemek.
*   **Adım Adım:** `try-except` bloğunun en sonuna `finally:` ekle. Kod başarıyla bitse de çalışır, hata verip `except`'e düşse de çalışır. Özellikle açık kalan veritabanı bağlantılarını veya dosyaları kapatmak için mükemmel bir yerdir.
