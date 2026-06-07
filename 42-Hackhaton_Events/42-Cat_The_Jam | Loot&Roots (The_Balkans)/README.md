# Loot&Roots (42 Cat The Jam)

## Oyun Özeti
Loot&Roots, 42 Game Jam (Cat The Jam) etkinliği kapsamında geliştirilmiş bir oyundur. Oyuna giriş yapabilmek ve oynayabilmek için 42 Intra API sistemi üzerinden doğrulama (OAuth) yapılması gerekmektedir. 

## Nasıl Çalıştırılır?

Oyunu bilgisayarınızda sorunsuz bir şekilde çalıştırmak ve oynamaya başlamak için aşağıdaki adımları sırasıyla uygulayın:

### 1. 42 Intra API Oluşturma
- [42 Intra Uygulamaları (Applications)](https://profile.intra.42.fr/oauth/applications) adresine gidin.
- **New Application** butonuna tıklayarak yeni bir uygulama oluşturun.
- Uygulamanın yönlendirme (redirect) URI'sini `http://localhost:8060/tmp_js_export.html` olarak belirleyin.
- Uygulama başarıyla oluşturulduktan sonra size verilen **UID** ve **SECRET** kimlik bilgilerini kopyalayın.

### 2. Konfigürasyon Dosyasının Ayarlanması
- Projenin içerisinde bulunan `yeni/` klasörüne gidin.
- Orada bulunan `secrets.cfg.example` dosyasının adını `secrets.cfg` olarak değiştirin (veya bu dosyanın kopyasını oluşturup adını `secrets.cfg` yapın).
- Dosyayı bir metin editörüyle açın ve 42 Intra üzerinden aldığınız UID ve SECRET bilgilerini ilgili tırnak içlerine yapıştırın:
  ```ini
  [api42]
  uid="ALDIĞINIZ_UID_BURAYA"
  secret="ALDIĞINIZ_SECRET_BURAYA"
  redirect_uri="http://localhost:8060/tmp_js_export.html"
  ```

### 3. Oyunu Başlatma
- Godot Engine'i (sürüm 4.x) açın.
- Projenin `Loot&Roots/` klasöründe yer alan `project.godot` dosyasını seçerek projeyi içe aktarın (import).
- Export Template'i kurduğunuzdan emin olun. (Project -> Export -> Add -> HTML5 -> Export Template...) (f5 ile godot içerisinde direkt, sağ üst köşeden export ettiğiniz web üzerinden çalıştırabilirsiniz.) 
- Editör üzerinden projeyi çalıştırın. 
- Karşınıza çıkacak olan **Login** ekranı aracılığıyla 42 Intra hesabınız ile giriş yapın.
- Giriş başarılı olduktan sonra oynamaya başlayabilirsiniz! İyi eğlenceler!
