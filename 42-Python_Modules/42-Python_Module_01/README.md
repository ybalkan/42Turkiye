# Python_Module_01 - Gizemli Bahçe (Veri Yapıları) 🌿

Selam! Verilerin dağınık halde durması bir kabustur. Bu modülde verileri düzenli tutmamızı sağlayan Veri Yapılarını (Data Structures) bir "Botanik Bahçesi" teması üzerinden öğrendim. Hangi veriyi ne zaman ve nerede kullanmam gerektiğini kavradığım yer tam da burası.

## 🎯 Bu Modülde Asıl Öğrenmemiz Gerekenler

Bu modülü bitirdiğinizde şu sorulara net cevap verebiliyor olmalısınız:
1.  **List (Liste):** Sıralı ve değiştirilebilir (mutable) verileri nasıl depolarım? Liste metodları (`append`, `pop`, `insert`) nasıl çalışır?
2.  **Dictionary (Sözlük):** Verileri "Anahtar-Değer" (Key-Value) ikilisi olarak birbirine nasıl bağlarım?
3.  **Tuple (Demet):** Değiştirilemez (immutable) ve sabit verileri dış müdahaleden nasıl korurum? Neden listelere göre daha az bellek harcar?
4.  **Set (Küme):** İçinde tekrar eden (duplicate) hiçbir eleman barındırmayan eşsiz bir yapıyı nasıl kurarım?
5.  **Nested Structures:** Bir listenin içine sözlük, sözlüğün içine tuple koyarak karmaşık veritabanı benzeri yapıları nasıl modellerim?

---

## 🧠 Teknik ve Metaforik Bakış

*   **Teknik Olarak:** Her veri yapısının bellekte (RAM) tutulma şekli ve algoritmik zaman karmaşıklığı (Time Complexity - Big O Notation) farklıdır. Listelerde bir eleman aramak $O(N)$ zaman alırken, Dictionary veya Set içinde eleman aramak $O(1)$ yani anında gerçekleşir. Veriye göre yapı seçmek performansın sırrıdır.
*   **Metaforik Olarak:** 
    *   **List**, bir alışveriş listesidir. Ekleyip çıkarabilir, sırasını değiştirebilirsiniz.
    *   **Tuple**, bir kitabın sayfalarıdır. Yazıldıktan sonra yırtamaz veya değiştiremezsiniz, hep sabittir.
    *   **Dictionary**, gerçek bir sözlüktür. "Elma" (Anahtar/Key) kelimesini ararsın ve karşılığındaki "Kırmızı bir meyve" (Değer/Value) açıklamasına direkt ulaşırsın.
    *   **Set**, bir gece kulübünün VIP davetli listesidir. Aynı kişi iki kere listeye yazılamaz. Sadece eşsiz (benzersiz) isimler vardır.

---

## 📂 Adım Adım Ne Yaptım? (Yeni Başlayanlar İçin Rehber)

Eğer veri yapılarını yeni öğreniyorsan, adımlarını şöyle atmalısın:

### **ex0 / Listelerle Tanışma**
*   **Ne Öğrendim?** Bahçedeki bitkileri sıraya dizmek.
*   **Adım Adım:** Köşeli parantez `[]` kullanarak bir liste oluştur. İçine elemanlar ekle. Unutma, listeler sıfırıncı indeks (0) ile başlar. Yani 1. elemana ulaşmak için `liste[0]` yazmalısın.

### **ex1 / Sözlükler (Dictionaries)**
*   **Ne Öğrendim?** Bitkilerin özelliklerini birbirine bağlamak.
*   **Adım Adım:** Süslü parantez `{}` kullan. `{"Bitki Adı": "Gül", "Su İhtiyacı": "Az"}` şeklinde yaz. Artık `sozluk["Bitki Adı"]` dediğinde sana doğrudan "Gül" cevabını verecek. Listeler gibi indeks numarası aramak zorunda değilsin!

### **ex2 / Veri Manipülasyonu**
*   **Ne Öğrendim?** Var olan veriyi değiştirmek.
*   **Adım Adım:** Listeye `.append()` ile yeni bitki ekle, `.remove()` ile çıkar. Sözlüğün bir değerini doğrudan `sozluk["Su İhtiyacı"] = "Çok"` diyerek güncelle.

### **ex3 / İç İçe Veri Yapıları (Nested)**
*   **Ne Öğrendim?** Büyük sistemler kurmak.
*   **Adım Adım:** Tek bir listeye sığamayacak veriler için sözlüklerin değer kısmına listeler ekle. `{"Sera_1": ["Gül", "Lale"], "Sera_2": ["Papatya"]}` gibi. JSON veri formatının temeli tam olarak budur!

### **ex4 / Demetler (Tuples)**
*   **Ne Öğrendim?** Değiştirilemez (Immutable) sabitler oluşturmak.
*   **Adım Adım:** Normal parantez `()` kullan. `koordinatlar = (45.5, 30.2)` yaz. Alt satırda bunu değiştirmeye çalışırsan Python hata verir. Bu, güvenlik gerektiren sabit veriler için mükemmeldir.

### **ex5 / Kümeler (Sets)**
*   **Ne Öğrendim?** Tekrar eden elemanlardan kurtulmak.
*   **Adım Adım:** Uzun bir listede aynı bitkiden 10 tane varsa, bu listeyi `set(liste)` diyerek kümeye çevir. Python anında kopyaları siler ve sana eşsiz (unique) elemanları bırakır. Matematikteki küme birleşimleri (`union`) gibi işlemler de yapılabilir.
