*This project has been created as part of the 42 curriculum by ybalkan, iuslu*

## Description
**Push Swap**, veri setlerini sınırlı bir dizi işlem ve iki yığın (A ve B) kullanarak mümkün olan en az hamleyle sıralamayı amaçlayan bir algoritma projesidir. Proje, karmaşıklık yönetimi ve algoritma optimizasyonu üzerine odaklanır.

Bu implementasyonda, yüksek performans ve minimum işlem sayısı hedefleyen optimize edilmiş bir yapı kullanılmıştır. Proje, modüler bir mimariye sahip olup (parsing, ops, algo, utils) geniş ölçekli sayı dizilerini etkili bir şekilde sıralayabilmektedir. Ayrıca performans analizi için `--bench` bayrağı içermektedir.

## Instructions
Projenin derlenmesi ve çalıştırılması için aşağıdaki adımları takip edebilirsiniz:

### Derleme
Proje dizininde `Makefile` dosyasını kullanarak derleme yapabilirsiniz:
```bash
make
```

### Kullanım
Programı bir sayı dizisi ile çalıştırın:
```bash
./push_swap 3 2 5 1 4
```

Hız testi ve işlem sayısını görmek için `--bench` bayrağını kullanabilirsiniz:
```bash
./push_swap --bench 500
```

### Temizlik
Nesne dosyalarını ve ikili dosyayı temizlemek için:
```bash
make clean
make fclean
```

## Resources
Bu projenin geliştirilme sürecinde aşağıdaki kaynaklardan yararlanılmıştır:
- **42 Subject**: Proje gereksinimleri ve kısıtlamaları.
- **Algoritma Teknikleri**: Yığın tabanlı sıralama algoritmaları ve optimizasyon stratejileri üzerine makaleler.

### AI Kullanımı
Bu projede Yapay Zeka (Antigravity), aşağıdaki görevlerde yardımcı bir araç olarak kullanılmıştır:
- **Kod Refaktörü**: Kodun modüler hale getirilmesi ve 42 Norm kurallarına (Norminette) uygunluğunun sağlanması.
- **Hata Ayıklama**: Derleme hatalarının çözülmesi ve uç durumların (edge cases) tespiti.
- **Dokümantasyon**: Mevcut README dosyasının ve teknik açıklamaların yapılandırılması.
- **Performans Analizi**: Yazılan algoritmaların verimlilik kontrolleri ve optimizasyon önerileri.

---

## Algorithms and Thresholds (Algoritmalar ve Kriterler)

Proje yöneticisi, farklı girdi düğüm listelerinin karmaşıklığına en uygun sıralama yaklaşımına (Simple, Medium, Complex) **Adaptive** modu kullanarak karar verir. Bu mekanizmada iki ana faktör dikkate alınır: **Dizi Uzunluğu (Size)** ve **Karmaşa Oranı (Disorder)**.
Disorder hesaplatması $O(n^2)$ çift karşılaştırması üzerinden oran alınarak ölçülür.

### Strateji Sınırları ve İzahı
- **Simple $O(n^2)$**:
  - `(size <= 5)` olduğunda veya veri setindeki % karmaşıklık `(mistakes < total_pairs / 5)` oranında yani `%20'den (disorder < 0.2)` düşük olduğunda devreye girer. Bubble sort / Insertion Sort benzeri yapılar kısa veya çok az hatalı birleştirilmiş yığınlarda işlem hacmini minimalize eder.
- **Medium $O(n\sqrt{n})$**:
  - Eğer disorder `%20 ≤ disorder < %50` aralığındaysa orta halli bloklamalar olan K-Sort parçalama tekniklerinden faydalanır. (Aksiyon sınırları kısıtlamasındaki esneklik yüzünden proje `Engine` adı altında en kompleks motorla `Adaptive` bloklarını paylaşıyor.)
- **Complex $O(n \log n)$**:
  - Hata/Karmaşıklık oranı veri tabanının boyutları üzerinde `%50'nin` (disorder $\ge 0.5$) üzerine çıktığında büyük çaplı Quick/Radix türevleriyle (burada `Engine`) en hızlı işlem sınırlarına varılır.

---

## Group Contributions (Grup Katkıları)

Bu proje iki öğrencinin yoğun katkısı ve ortak çalışmasıyla tasarlanmıştır:
- **`ybalkan`**: Argüman ayrıştırma (parsing), kütüphane fonksiyonları entegrasyonu, `Makefile` otomasyonu ve yardımcı `utils/` dosyalarının yazımı/yönetimi süreçlerinden sorumludur.
- **`iuslu`**: Çekirdek sıralama mekanizması dizaynı (algoritma), operasyon komutlarının uygulanması ve operasyon/performans benchmark entegrasyonları dahil kalan tüm sistem sorumluluklarını üstlenmiştir.

> Her iki öğrenci de savunma (peer-review defense) sırasında tam randımanlı bulunacak ve kodun herhangi bir parçasını savunabilecek düzeyde hakimiyete sahiptir.
