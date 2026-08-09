# Python_Module_08 — Matrix Environment

> **Python 3.13+ · Virtual Environments · Dependency Management · Environment Variables**

Sanal ortamlar, bağımlılık yönetimi ve environment variable'lar üzerine kurulu bir proje.  
Her egzersiz bir öncekinin üzerine inşa edilir.

---

## 📂 Adım Adım Ne Yaptım? (Yeni Başlayanlar İçin Rehber)

### **ex0 / Sanal Ortam Kontrolü (`construct.py`)**
* **Ne Öğrendim?** Python'da **virtual environment (sanal ortam)** kavramı ve neden gerekli olduğu.
* **Adım Adım:** Program çalıştırıldığında `VIRTUAL_ENV` ortam değişkenini kontrol ediyor. Eğer sanal ortam aktifse "Welcome to the construct" mesajı çıkıyor, kurulu paketlerin yükleneceği dizin gösteriliyor. Aktif değilse uyarı vererek nasıl sanal ortam kurulacağı adım adım açıklanıyor.

### **ex1 / Bağımlılık Yönetimi (`loading.py`)**
* **Ne Öğrendim?** Üçüncü parti kütüphaneleri kontrol etmek, `pyproject.toml` ve `requirements.txt` ile bağımlılıkları tanımlamak.
* **Adım Adım:** `pandas`, `numpy`, `matplotlib` kütüphanelerinin yüklü olup olmadığı `importlib.util.find_spec` ile kontrol ediliyor. Eksik paket varsa kurulum komutu gösteriliyor. Hepsi mevcutsa verilerle analiz yapılıp görsel olarak `matrix_analysis.png` dosyasına kaydediliyor.

### **ex2 / Environment Variables (`oracle.py`)**
* **Ne Öğrendim?** Hassas bilgileri (API anahtarı, veri tabanı URL'i vb.) kodun içine yazmak yerine `.env` dosyasında saklamak ve `python-dotenv` ile okumak.
* **Adım Adım:** `.env.example` şablonundan `.env` dosyası oluşturuluyor. `load_dotenv()` ile değişkenler yükleniyor. `MATRIX_MODE`, `API_KEY`, `DATABASE_URL` gibi değerler okunup doğrulama ve güvenlik kontrolünden geçiriliyor. API anahtarı eksikse program hata vererek duruyor.

---

## Proje Yapısı

```
py08/
├── ex0/
│   └── construct.py        ← Sanal ortam kontrol scripti
│
├── ex1/
│   ├── loading.py          ← Bağımlılık kontrolü + analiz
│   ├── pyproject.toml      ← Proje & bağımlılık tanımları (Poetry)
│   └── requirements.txt    ← pip için bağımlılık listesi
│
└── ex2/
    ├── oracle.py           ← Environment variable okuma & doğrulama
    ├── .env.example        ← Değişken şablonu (versiyon kontrolüne girer)
    ├── .gitignore          ← .env dosyasını gizler
    └── requirements.txt    ← python-dotenv bağımlılığı
```

---

## Çalıştırma

```bash
# ex0 — Sanal ortam kontrolü
python3 construct.py

# ex1 — Bağımlılık kontrolü & analiz
pip install -r requirements.txt
# veya Poetry ile:
poetry install
python3 loading.py

# ex2 — Environment variables
cp .env.example .env     # .env dosyasını oluştur ve doldur
pip install -r requirements.txt
python3 oracle.py
```

---

## Egzersizler

### EX0 — Virtual Environment · `construct.py`

Programın sanal ortam içinde mi yoksa global ortamda mı çalıştığını tespit eder.

| Durum | Mesaj | Açıklama |
|---|---|---|
| ✅ Sanal ortam aktif | `Welcome to the construct` | İzole ortam, güvenli paket kurulumu |
| ❌ Global ortam | `You're still plugged in` | Sistem genelini etkileyebilir, uyarı verilir |

```bash
# Sanal ortam oluşturma ve aktif etme
python -m venv matrix_env
source matrix_env/bin/activate   # Unix/macOS
matrix_env\Scripts\activate      # Windows
```

---

### EX1 — Dependency Management · `loading.py`

Gerekli kütüphanelerin (`pandas`, `numpy`, `matplotlib`) yüklü olup olmadığını kontrol eder. Hepsi mevcutsa 1000 rastgele veri noktası üretir, rolling mean hesaplar ve `matrix_analysis.png` olarak kaydeder.

| Paket | Görev |
|---|---|
| `numpy` | Sayısal veri üretimi |
| `pandas` | Veri çerçevesi + rolling mean |
| `matplotlib` | Grafik oluşturma & kaydetme |

```
check_deps()   →  [OK] pandas / numpy / matplotlib
get_versions() →  versiyon bilgisi
run_analysis() →  matrix_analysis.png
```

---

### EX2 — Environment Variables · `oracle.py`

Hassas konfigürasyon verilerini `.env` dosyasından okur, doğrular ve güvenlik kontrolü yapar.

| Değişken | Varsayılan | Açıklama |
|---|---|---|
| `MATRIX_MODE` | `development` | `development` veya `production` |
| `DATABASE_URL` | `sqlite:///matrix_local.db` | Veri tabanı bağlantı adresi |
| `API_KEY` | *(boş)* | Zorunlu — eksikse program durur |
| `LOG_LEVEL` | `DEBUG` | Loglama seviyesi |
| `ZION_ENDPOINT` | `http://zion.local:8080` | Ağ uç noktası |

> ⚠️ `.env` dosyası asla versiyonlama sistemine (Git) eklenmez. Şablonu `.env.example` olarak paylaşırsın.

---

## Temel Kavramlar

* **`os.environ.get(key)`**: Ortam değişkenini okur; bulunamazsa `None` döner.
* **`importlib.util.find_spec(pkg)`**: Bir paketin yüklü olup olmadığını import etmeden kontrol eder.
* **`load_dotenv()`**: `.env` dosyasındaki değişkenleri `os.environ`'a yükler.
* **`pyproject.toml`**: Modern Python projelerinde bağımlılıkları ve proje meta verilerini tanımlamak için standart dosya formatı.
* **`requirements.txt`**: `pip install -r` ile hızlı kurulum için kullanılan klasik bağımlılık listesi.
* **`getattr(mod, "__version__", "unknown")`**: Bir modülün versiyon bilgisini güvenli şekilde okur.

---

## Doğrulama

```bash
python3 -m flake8 ex0/ ex1/ ex2/
python3 -m mypy   ex0/ ex1/ ex2/ --strict
```
