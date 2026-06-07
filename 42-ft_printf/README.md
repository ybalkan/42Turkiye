*This project has been created as part of the 42 curriculum by ybalkan.*

## Description
Bu proje, standart C kütüphanesindeki `printf` fonksiyonunu **sıfırdan yeniden oluşturma** ve çalışma mantığını anlama amacıyla geliştirilmiştir.
Proje, `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, ve `%%` format belirteçlerini **tam uyumlulukla** destekler.

**Temel Hedef:** Değişken sayıda argüman alan (variadic) fonksiyonları yönetmek ve bellek/performans optimizasyonu yapmaktır.

## Instructions (Talimatlar)

### 1. Compilation (Derleme)
Projeyi derlemek ve `libftprintf.a` kütüphanesini oluşturmak için:
```bash
make
```

### 2. Execution (Kullanım)
Kütüphaneyi kendi kodunuzda kullanmak için `ft_ft_printf.h` dosyasını include edin ve derlerken kütüphaneyi bağlayın:
```c
#include "ft_ft_printf.h"

int main()
{
    ft_printf("Merhaba %s!\n", "Dunya");
    return (0);
}
```
Derleme komutu:
```bash
gcc main.c libftprintf.a -o my_code && ./my_code
```

### 3. Cleaning (Temizleme)
*   **make clean:** Sadece `.o` (obje) dosyalarını siler.
*   **make fclean:** `.o` dosyalarıyla birlikte `libftprintf.a` kütüphanesini de siler.
*   **make re:** Projeyi temizler ve baştan derler.

---

## Detailed Algorithm & Development Steps (Adım Adım Geliştirme Süreci)

Bu proje rastgele kodlanmamış, her adımı belirli bir mantık ve mimari karar ile atılmıştır. İşte adım adım süreç:

### Adım 1: Mimari Kararı - `va_list` Yönetimi 
İlk olarak, değişken sayıda argümanı (`...`) nasıl yöneteceğimize karar verdik.
*   **Sorun:** `va_list` yapısı bazı mimarilerde (örn: Apple Silicon M1/M2) referans gibi davranmayabilir. Fonksiyona değer olarak (copy) gönderilirse, ana fonksiyondaki liste ilerlemez.
*   **Çözüm:** Tüm yardımcı fonksiyonlara `va_list`'in kendisini değil, **adresini (pointer)** göndermeye karar verdim (`va_list *args`).
*   **Sonuç:** Bu sayede argüman listesi her zaman doğru şekilde ilerler ve `Segmentation Fault` riski ortadan kalkar.

### Adım 2: Ana Döngü ve Dispatcher (Yönlendirici) 🚦
Fonksiyon karmaşasını önlemek için "Yönetici ve İşçiler" modeli uygulandı.
1.  **Parser (Yönetici):** Ana `ft_printf` fonksiyonu sadece format stringini (`fmt`) tarar.
2.  **Dispatcher:** `%` işareti görüldüğünde, `ft_eval_format` fonksiyonu devreye girer.
3.  **İşçiler:** `c`, `s`, `d` gibi tiplere göre ilgili `conv_*` fonksiyonu çağrılır.
*   **Not:** Switch-Case yapısı simüle edilerek kodun okunabilirliği artırıldı.

### Adım 3: Sayı Dönüşümleri - Iterative Yaklaşım 
Sayıları (`%d`, `%i`, `%u`, `%x`) ekrana basmak için kullanılan `putnbr` mantığı optimize edildi.
*   **Eski Yöntem:** Recursive (Özyinelemeli) fonksiyonlar. (Dezavantajı: Stack Overflow riski).
*   **Yeni Yöntem:** **Iterative (Döngüsel)** ve **Buffer** kullanımı.
    *   Sayıyı önce bir `char` dizisine (buffer) tersten doldurdum.
    *   Sonra diziyi doğru sırada ekrana bastım.
*   **Not:** Bu yöntem hem daha güvenli hem de daha hızlıdır.

### Adım 4: Bellek Yönetimi (No Malloc) 
Hız ve güvenilirlik için dinamik bellek tahsisi (`malloc`) **kullanılmamıştır**.
*   Tüm işlemler Stack üzerinde ve statik bufferlar ile yapılmıştır.
*   Bu sayede `Memory Leak` (Bellek Sızıntısı) riski **sıfıra indirilmiştir**.

---

## Resources & AI Usage (Kaynaklar ve AI Kullanımı)

### Resources (Kaynaklar)
*   **`man 3 printf`**: Orijinal fonksiyonun davranışı ve dönüş değerleri incelendi.
*   **`man 3 stdarg`**: Variadic makroların (`va_start`, `va_list`) kullanımı öğrenildi.
*   **ABI Documentation**: Farklı işlemci mimarilerinde (x86 vs ARM) fonksiyon çağırma konvansiyonları araştırıldı.

### AI Usage Description (Yapay Zeka Kullanımı)
Bu projede Yapay Zeka, bir "Pair Programmer" (Eş Yazılımcı) gibi kullanılmıştır:

1.  **Debugging (Hata Ayıklama):**
    *   **Görev:** Apple Silicon mimarisinde `va_list` kaynaklı Segfault hatasının tespiti.
    *   **AI Katkısı:** `va_list`'in pointer olarak gönderilmesi gerektiği çözümünü önerdi ve uyguladık.

2.  **Test Case Generation (Test Senaryoları):**
    *   **Görev:** Kodun kırılma noktalarını (Edge Cases) test etmek.
    *   **AI Katkısı:** `INT_MIN`, `NULL` String, `NULL` Pointer gibi uç durumlar için kapsamlı bir `test_main.c` dosyası oluşturuldu.

3.  **Refactoring (Kod Düzenleme):**
    *   **Görev:** Kodun daha okunabilir ve modüler hale getirilmesi.
    *   **AI Katkısı:** `ft_eval_format` fonksiyonunun yapılandırılması ve `header` dosyasının düzenlenmesinde şablon sağlandı.

**Not:** Kodun tüm mantıksal akışı ve algoritma kararları (Iterative vs Recursive) tarafımdan belirlenmiş ve yapay zeka desteğiyle optimize edilmiştir.

---

## 🌾 Çiftlik Metaforu (Code Analogy)

Kodun anlaşılabilirliği için özel bir metafor geliştirildi. Her dosya bir çiftlik çalışanını temsil eder:

*   **[src/ft_printf.c](src/ft_printf.c)** -> **Çiftlik Sahibi (Ağa)** 👨‍🌾
    *   Siparişleri alır ve yönetir. Tarlaya (detaylara) girmez.
*   **[src/ft_printf_utils.c](src/ft_printf_utils.c)** -> **Kahya (Baş Yardımcı)** 📜
    *   Hangi ürün için hangi işçinin çağrılacağını bilir. Görev dağılım listesini (`table`) tutar.
*   **[src/pf_*.c](src/)** -> **Uzman Çiftçiler** 👩‍🌾
    *   `pf_char.c`: **Tohumcu** (Tek karakter eker).
    *   `pf_string.c`: **Balya Yapan** (Uzun metinleri toplar).
    *   `pf_int.c`: **Sayman** (Hesap kitap yapar).
    *   `pf_hex.c`: **Yabancı Tüccar** (Farklı dilde/tabanda hesaplar).
*   **[utils/ft_itoa_base.c](utils/ft_itoa_base.c)** -> **Değirmen** ⚙️
    *   Ürünleri (sayıları) işleyip son hale (yazıya) getiren makine.
*   **[utils/write_helpers.c](utils/write_helpers.c)** -> **Nakliye Ekibi** 🚚
    *   Ürünleri pazara (ekrana) taşıyan kamyoncular.

---

## 🛠 Yapılan Düzeltmeler ve Notlar (Techniques & Fixes)

Normal geliştirme sürecine ek olarak şu iyileştirmeler yapılmıştır:

1.  **Format Belirteci (Specifier) İsimlendirmesi:**
    *   Karışıklığı önlemek için tüm dönüşüm dosyaları `pf_` (printf) önekiyle yeniden adlandırıldı (`src/pf_char.c`, `src/pf_int.c` vb.).
    *   Header dosyası `ft_ft_printf.h` yerine daha sade olan `ft_printf.h` olarak güncellendi.

2.  **Tanımsız Karakter Yönetimi (%k Gibi):**
    *   Standart `printf` davranışı analiz edildi. Şu anki versiyon tanımsız karakterleri güvenlik amacıyla yutmaktadır (ignore). İstenirse orijinal davranış (olduğu gibi basma) kolayca eklenebilir.

3.  **Performans Odaklı Yardımcı Fonksiyon:**
    *   `ft_itoa` (Integer to ASCII) yerine `ft_putnbr_base` kullanıldı. Bu sayede bellek tahsisi (`malloc`) yapmadan sayılar doğrudan ekrana basılıyor, bu da performansı artırıyor.