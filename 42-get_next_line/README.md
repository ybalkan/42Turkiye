*This project has been created as part of the 42 curriculum by ybalkan.*

# Get Next Line (GNL)

## 📌 Description (Açıklama)
**Get Next Line**, 42 okulunun temel projelerinden biridir. Bu projenin temel amacı, bir Dosya Tanımlayıcısından (File Descriptor - FD) her çağrılışında dosyanın sonuna (EOF) gelene kadar yalnızca bir satır (newline `\n` karakterine veya dosya sonuna kadar) okuyan ve o satırı döndüren bir fonksiyon yazmaktır.

Proje, C programlama dilindeki **Statik Değişkenleri (Static Variables)**, bellek ayırmayı (memory allocation) ve dosya işlemlerini (file manipulation) derinlemesine kavramayı hedefler. Sadece standart dosyalardan değil, aynı zamanda standart girişten (stdin) ve diğer çeşitli I/O akışlarından da veri okuyabilme kapasitesine sahiptir.

**Hedefler:**
- Statik değişkenlerin arka planındaki davranışı, ömrü (lifetime) ve kullanım alanlarını öğrenmek.
- `read()`, `malloc()`, ve `free()` fonksiyonlarını kullanarak bellek yönetimini (memory management) sağlamak ve "Memory Leak" (bellek sızıntısı) sorunlarının önüne geçmek.
- Norminette standartlarına uygun (Norm V3) temiz, modüler ve güvenli C kodu yazmak.

---

## 🚀 Instructions (Talimatlar)
Bu bölüm, projenin derlenmesi, projeye veya test ortamınıza entegre edilmesi ve yürütülmesi için gereken adımları içerir.

### Gereksinimler
- GCC veya Clang derleyicisi.
- Unix tabanlı bir işletim sistemi (Linux, macOS vb.).
- 42 Norminette kurallarına uygun bir ortam.

### Kullanım ve Derleme
Proje genellikle doğrudan bir çalıştırılabilir (executable) dosya veya kendi başına bir kütüphane üretmez. Bunun yerine fonksiyonlarınızı kendi projenize veya test senaryonuza dahil edebileceğiniz C kaynak dosyaları (mandatory/bonus) şeklinde derlersiniz. (Daha sonra `libft` içerisine kütüphane fonksiyonu olarak entegre edilebilir.)

Bir C dosyasında (örneğin `main.c`) fonksiyonu kullanmak için başlık dosyasını projenize dahil etmelisiniz:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

**Zorunlu (Mandatory) bölümü kendi betiğinizle derlemek için:**
(Derleme sırasında `-D` bayrağı ile bir `BUFFER_SIZE` makrosu değeri belirlemelisiniz.)
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 mandatory/get_next_line.c mandatory/get_next_line_utils.c main.c -o gnl_test
./gnl_test
```

**Bonus kısmını derlemek için (Çoklu FD Desteği):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus_test
./gnl_bonus_test
```

**🌟 Önemli Not (Teslimata Dair):** Moulinette ve `Makefile` projeyi ana dizinde beklediği için projeyi gönderirken/savunurken `get_next_line.c` gibi dosyaların doğrudan kök dizinde (`gnl_son/`) bulunduğundan emin olun.
Ayrıca fonksiyonlarınızın derlenmesi sırasında `-D BUFFER_SIZE=1`, `-D BUFFER_SIZE=9999` ve `-D BUFFER_SIZE=10000000` gibi devasa ya da çok ufak boyutlarla tutarlı çalışıp çalışmadığını Valgrind ile kontrol etmek test aşamasının standart bir parçasıdır.

---

## 🧠 Seçilen Algoritma ve Açıklaması (Algorithm & Justification)
`get_next_line` fonksiyonunun temel problemi, `read()` fonksiyonunun belirlenen kısıtla (`BUFFER_SIZE`) dosyadan belirli sayıda bayt çekmesi, ancak aynı anda yeni satırların (`\n`) nerede başlayıp nerede biteceğini bilememesidir. Bu nedenle, okuduğunuz fakat döndüreceğiniz satırdan arta kalan kısmı "kalanlar" olarak bir hafızada (**Static Variable**) tutmanız hayati bir gerekliliktir.

### Neden Bu Yaklaşımı Seçtik ve Nasıl Çalışıyor?
Projenin temel mantığı üç adımlı bir yaklaşım ile işler:

1. **`read_and_stash` (Dosyadan Okuma ve Biriktirme):** 
   Dosyada okunacak karakter varsa ve önceki okunanlardan elimizde kalan statik değişkende (stash) hala bir `\n` (yeni satır) karakteri bulamadıysak, `read()` yardımıyla buffer doldurulur. Okunan her yeni buffer, önceki okumadan kalan stringle birleştirilir (`ft_strjoin` veya dengiyle stringin sonuna eklenir). `\n` bulunduğunda veya EOF'ye (okuma bitişine, `read == 0`) gelindiğinde bu döngü durur.
   **Gerekçesi:** Read döngüsünü string manipülasyonundan izole edip yalnızca yeterli veriyi garantiye almak projenin esnekliğini maksimuma çıkarır.

2. **`extract_line` (Tam Satırı Çekme):**
   Statik değişke elimizdeki verinin tamamına sahip olduğunda (içinde yeni satır barındıran veya tamamlanmış metin), statik değişken baştan sona tek tek taranır. İlk `\n` karakterini gördüğümüz yere kadar (ve `\n` karakterini de dahil edecek şekilde) olan kısım tamamen kopyalanır ve yeni bir bellek (`malloc`) ayırılarak o adrese aktarılır.
   **Gerekçesi:** Buffer ve stash stringi tek parça halinde tutulur, bu işlemle sadece bize yarayan, kullanıcıya teslim edilecek saf kısmı temiz bir şekilde koparıp alırız.

3. **`clean_stash` (Kalanı / Artığı Güncelleme):**
   Kullanıcıya verilen satır sonrası geriye kalan bütün metin, bir sonraki `get_next_line()` çağrısı için elde tutulmalıdır. O yüzden statik pointer'daki satırdan hemen sonrasına denk gelen yer yakalanır, geri kalanı hafıza yenilenerek aynı statik değişkene aktarılır ve asıl hafızadaki o tek satırlık bölüm eski statik bellekten yok edilerek `free` işlemine sokulur.

**Algoritmanın Gücü:** Bu optimize edilmiş bölümlü mekanizma, modülerliği ciddi şekilde artırır. Çok devasa `BUFFER_SIZE` değerleri verilse dahi sadece `\n` arandığı için bellek gereksiz döngülerle ihlal edilmez (Time Limit Exceeded sorunlarının önüne geçilir).

### Bonus Algoritması (Çoklu Dosya Okuma)
Bonus gereksinimi "Tek bir static değişken kullanarak aynı anda birbirinden tamamen bağımsız dosya tanımlayıcılarından (fd) kalınan yer kaybedilmeden okuma yapılmasıdır." 
Bunu sağlamak için 2 boyutlu/dizi pointer formatında maksimum dosya sayısı sınırı kadar (`OPEN_MAX` veya standart Linux spesifikasyonlarına göre `4096` / `1024`) statik bir liste yarattık: `static char *stash[4096];`
Bunun bize katkısı şudur: 
- `get_next_line(3)` çağrıldığında `stash[3]` devreye girer ve fd 3'ün artık stringi orada bekler.
- `get_next_line(4)` veya `get_next_line(5)` çağrıldığında herbiri kendi dizi indexi üzerinden işlem yapar. Bu yaklaşım son derece basit fakat bir o kadar da kesin çalışan güçlü bir O(1) erişim tekniğidir. Hiçbir bellek çakışması veya veri karışması yaşanmaz.

---

## 📚 Resources (Kaynaklar ve AI Kullanımı)

### Kullanılan Referanslar
Projeyi yazarken ve test ederken C standart kütüphaneleri ve temel dökümantasyonlar dikkate alınmıştır:
- [C Programming - Static Variables (GeeksforGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/)
- Unix sistem kılavuzları (Man pages): `man 2 read`, `man 3 malloc`, `man 3 free`, `man ulimit`.
- "File Descriptors kavramı ve limitleri" üzerine geliştirici forumlarındaki akademik tartışmalar.
- 42 School Norminette V3 Kuralları ve Github üzerindeki Open-Source Test scriptleri (örneğin: `francinette`, `gnlTester`).

### Yapay Zeka (AI) Kullanımı
Müfredat değerlendirmelerinin gereklilikleri doğrultusunda, proje sürecinde Yapay Zeka (LLM / AI) asistanları (örneğin Google Gemini Agent) spesifik bazı alanlarda aktif olarak kullanılmış ve bunlardan nasıl faydalanıldığı aşağıda şeffaf şekilde listelenmiştir:
1. **Norminette (Kod Standartları) Uyumu:** Fonksiyonları daha modüler, `25 satır sınırına` uyan ve `değişken sayısı (5 limitini)` koruyan küçük yardımcı (utility) fonksiyonlara ayırma sürecinde stratejik öneriler ve yeniden düzenlemeler için (Refactoring desteği).
2. **Kapsamlı Test ve Sorun Giderme (İşlem Geçmişi İzleri):** Kullanıcının işlem geçmişindeki kayıtlara dayanarak, `ybalkan` isimli tester aracının oluşturulması, Time Limit Timeout hataları için bash optimizasyonları ve bellek yönetimi / Valgrind entegrasyonu (Memory Leaks taramaları) süreçlerinde, test ortamını otomatikleştiren karmaşık make/bash dosyalarının onarımında.
3. **Dokümantasyon (README Süreci):** Projenin gereksinimlerini en iyi şekilde anlatmayı ve akıcı bir Türkçe kaynak sunmayı sağlayan bu `README.md` dosyasının, belirlenen kurallara (`Chapter V` ve `Chapter VII`) kusursuzca uyum sağlayacak profesyonel formatta hazırlanması ve Türkçe diline oturtulması için AI sisteminin doğal dil işleme kapasitesi kullanılmıştır. 

---

## 🧪 Submission and Peer-Evaluation (Değerlendirme Notları)
Chapter VII değerlendirme talimatları ışığında; test süreçlerimiz sırasında şunlara ekstra dikkat edilmiştir:
- **`BUFFER_SIZE` Çeşitliliği:** Valgrind üzerinden bellek testleri (leak, invalid read) yoğun olarak test edilirken tampon boyutu özellikle uç degerlerde çalıştırıldı (`1`, `2`, `10`, `9999`, `10000000`). Tüm bu boyutlarda proje çökmeye mahal bırakmadan, stabil olarak EOF olana kadar tam sonucu vermiştir. Hedef boyut `42` dışında her türlü limit denendi.
- **Standart Olmayan Dosyalar:** File descriptor'un sadece sıradan dosyalar (`txt`, `md`) olmadığı, aynı zamanda standard input (`stdin = 0`), klasörler yönlendirilerek I/O buffer testleri de başarıyla kurgulandı ve savunma süreci test edildi. Dosyaya yazma/okuma hakkı (permissions) olmadığındaki tepkiler işlendi.
- **Anlık Değişiklikler (Refactor):** Değerlendirme sırasında istenebilecek ufak bir bellek yapısı değişimi (Örneğin: statik pointer yapısında değişken değişikliği) durumunda rahat müdahale için kod oldukça esnek modüllerle yapılandırıldı. Savunma esnasındaki talebe göre kısa sürede kolayca manevra yapılabilmesi amaçlandı.
- Projenizin hatasız devam ettiğinden ve onaylandığından emin olduktan sonra `get_next_line()` fonksiyonunu (veya utils fonksiyonlarını) `libft` (Kütüphane) projenize özgürce dahil edebilirsiniz.

*Tüm zorluklara rağmen projedeki emeğiniz için tebrikler. Değerlendirmede (Evaluation) ve Defense sırasında başarılar!*
