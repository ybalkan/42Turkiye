# Python_Module_04 - Kadim Parşömenler (Dosya İşlemleri) 📜

Selam! Programlarımız çalıştığı sürece verileri RAM'de tutar, program kapanınca da her şey silinir gider. Peki oyunu kaydetmek, log tutmak veya veriyi diskte saklamak istersek ne yapacağız? İşte bu modülde geçici belleğin ötesine geçip, "Kadim Parşömenler" temasıyla kalıcı dosyalar okumayı ve disk üzerine yazı yazmayı (File I/O) öğrendim.

## 🎯 Bu Modülde Asıl Öğrenmemiz Gerekenler

Bu modülü bitirdiğinizde şunlara tam hakim olmalısınız:
1.  **Açma Modları (File Modes):** Bir dosyayı hangi niyetle açtığınızı Python'a anlatmak. `r` (read/okuma), `w` (write/yazma), `a` (append/ekleme) modlarının farkları.
2.  **Güvenli Erişim (Context Manager):** `with open(...) as file:` bloğu kullanarak dosya kapatmayı unutma derdinden kurtulmak ve memory leak (bellek sızıntısı) riskini sıfırlamak.
3.  **Satır Satır Okuma:** Gigabaytlarca büyüklükteki bir dosyayı tek seferde RAM'e yüklemek yerine (ki bu bilgisayarı dondurur), `.readline()` veya `for line in file:` ile satır satır güvenle okumak.
4.  **İmleç Yönetimi (Cursor):** Dosya içinde okuma/yazma imlecinin nerede olduğunu bulmak (`tell()`) ve imleci istediğimiz yere ışınlamak (`seek()`).

---

## 🧠 Teknik ve Metaforik Bakış

*   **Teknik Olarak:** Python, işletim sistemi üzerinden donanımla (Harddisk/SSD) haberleşir. Dosyayı `open()` ile açtığınızda işletim sistemi bu dosyaya bir kilit (lock) veya dosya tanımlayıcı (file descriptor) atar. Eğer `close()` demezseniz, program kapanana kadar o dosya meşgul görünür, başka programlar erişemeyebilir. Bu yüzden I/O (Girdi/Çıktı) işlemleri her zaman risklidir ve try-except ile veya `with` bloğuyla korunmalıdır.
*   **Metaforik Olarak:** Diskteki bir dosya, cam bir fanus içindeki eski bir kitaptır. `open()` demek, fanusun kilidini açmaktır. Eğer kitabı okuduktan sonra fanusu kilitlemezsen (`close()` demezsen), kitabın sayfaları havalanıp zarar görebilir. `with open` yapısı ise, sen odadan çıkar çıkmaz fanusu otomatik kilitleyen sihirli bir mekanizmadır.

---

## 📂 Adım Adım Ne Yaptım? (Yeni Başlayanlar İçin Rehber)

Dosya işlemleri konusunda sıfırsan, bu adımlar rehberin olacak:

### **ex0 / Kadim Metin (Dosya Okuma - `r`)**
*   **Ne Öğrendim?** Var olan bir dosyadan veriyi çekmek.
*   **Adım Adım:** `with open("gizli_metin.txt", "r") as dosya:` yaz. Ardından içerideki veriyi almak için `icerik = dosya.read()` komutunu kullan ve `print(icerik)` ile ekrana bas.

### **ex1 / Arşiv Oluşturma (Dosya Yazma - `w` ve `a`)**
*   **Ne Öğrendim?** Sıfırdan dosya yaratmak veya üzerine ekleme yapmak.
*   **Adım Adım:** `w` modu tehlikelidir; dosya varsa içindekini tamamen siler ve sıfırdan yazar. `with open("yeni_arsiv.txt", "w")` diyerek dosyayı aç ve `.write("Merhaba Dünya")` de. Eğer önceki silinmesin, sadece sonuna eklensin istiyorsan `a` (append) moduyla aç.

### **ex2 / Akış Yönetimi (`seek` ve `tell`)**
*   **Ne Öğrendim?** Dosya içinde gezinmek.
*   **Adım Adım:** Dosyayı okurken `dosya.tell()` dersen sana kaçıncı baytta/karakterde olduğunu söyler. Eğer tekrar başa dönüp okumak istersen dosyayı kapatıp açmana gerek yok; `dosya.seek(0)` dersen imleci sıfırıncı noktaya geri alırsın.

### **ex3 / Kasa Güvenliği (Kapsamlı Pratik)**
*   **Ne Öğrendim?** `with` yapısının gücü.
*   **Adım Adım:** Burada artık tüm `try-except` yeteneklerimle dosya işlemlerini birleştirdim. "Ya dosya yoksa?" (`FileNotFoundError`), "Ya okuma iznim yoksa?" (`PermissionError`) gibi soruların cevabını koda döküp kırılmaz bir kasa sistemi yazdım.
