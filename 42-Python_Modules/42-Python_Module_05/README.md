# Selamlar! 👋 Code Nexus'a Hoş Geldiniz

Bu projeyi Python'da Nesne Yönelimli Programlama (OOP) tarafında derinleşmek için hazırladım.
Polimorfizm, Soyut Sınıflar ve Duck Typing kavramlarını gerçek bir veri işleme senaryosunda **adım adım** kodlayarak inceledim.

---

## 🚀 Proje Adımları

---

### Exercise 0 — Soyut Sınıf ve Metod Ezme

Sistemin temelini oluşturan `DataProcessor` soyut sınıfı burada kurulur.
`NumericProcessor`, `TextProcessor` ve `LogProcessor` bu şablondan türer.
Her biri kendi veri tipini tanır, doğrular ve işler — ama hepsi aynı arayüzü kullanır.

![Exercise 0 Şema](ex0_sema.png)

**Kaynak kod:** `ex0/data_processor.py`
**Yorumlu versiyon:** `anlatim/ex0/data_processor_yorumlu.py`
**Anlatım dosyaları:** `anlatim/ex0/`

```bash
python3 ex0/data_processor.py
```

---

### Exercise 1 — Polimorfik Yönlendirme (DataStream)

Karmaşık ve karışık bir veri akışı geldiğinde `DataStream` devreye girer.
Gelen her veriyi kayıtlı işlemcilere tek tek sorar: "Bu senin malın mı?"
Sahip çıkan işlemci veriyi alır. Kimse sahip çıkmazsa hata basar.
Yeni işlemci eklemek için mevcut koda dokunmak gerekmez.

![Exercise 1 Şema](ex1_sema.png)

**Kaynak kod:** `ex1/data_stream.py`
**Yorumlu versiyon:** `anlatim/ex1/data_stream_yorumlu.py`
**Anlatım dosyaları:** `anlatim/ex1/`

```bash
python3 ex1/data_stream.py
```

---

### Exercise 2 — Duck Typing ve Plugin Sistemi (DataPipeline)

İşlenen veriler artık dışarı çıkacak. Ama nasıl? Hangi formatta?
`output_pipeline()` ile işlenmiş veriler bir plugin'e aktarılır.
Plugin'in tek şartı `process_output` metoduna sahip olmak — miras almak zorunda değil.
`CSVExportPlugin`, `JSONExportPlugin`... Yarın başkası da eklenebilir, sisteme dokunulmaz.

![Exercise 2 Şema](ex2_sema.png)

**Kaynak kod:** `ex2/data_pipeline.py`
**Yorumlu versiyon:** `anlatim/ex2/data_pipeline_yorumlu.py`
**Anlatım dosyaları:** `anlatim/ex2/`

```bash
python3 ex2/data_pipeline.py
```

---

## 📂 Klasör Yapısı

```text
py05/
├── ex0/
│   └── data_processor.py
├── ex1/
│   └── data_stream.py
├── ex2/
│   └── data_pipeline.py
├── anlatim/
│   ├── genel.md
│   ├── metafor.md              <- Hikayeli anlatım + genel şema
│   ├── ex0/
│   │   ├── data_processor_yorumlu.py
│   │   ├── genel_amac.md
│   │   ├── anlatim.md          <- Ex0 şeması burada
│   │   ├── kod_yorum.md
│   │   └── sema.png
│   ├── ex1/
│   │   ├── data_stream_yorumlu.py
│   │   ├── genel_amac.md
│   │   ├── anlatim.md          <- Ex1 şeması burada
│   │   ├── kod_yorum.md
│   │   └── sema.png
│   └── ex2/
│       ├── data_pipeline_yorumlu.py
│       ├── genel_amac.md
│       ├── anlatim.md          <- Ex2 şeması burada
│       ├── kod_yorum.md
│       └── sema.png
└── README.md
```

---

Okuduğunuz için teşekkürler! Umarım OOP mantığını oturtmak isteyenler için faydalı bir kaynak olur. Keyifli kodlamalar! ☕️
