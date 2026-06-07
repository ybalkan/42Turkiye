*This project has been created as part of the 42 curriculum by ybalkan.*

# Born2beRoot

## Description
Born2beRoot projesinin amacı, bir Linux sanal makinesi kurarak sistem yönetimi ve güvenlik konularında temel bilgi ve beceriler kazanmaktır. Bu proje kapsamında, Debian veya Rocky Linux tabanlı bir sistem kurulup, belirli güvenlik kuralları uygulanır ve servisler yapılandırılır.

This project was implemented using **Debian** as the operating system due to its stability, simplicity, and strong community support. Key design decisions included using LVM for flexible disk management, enforcing strict password and sudo policies, restricting SSH access, and configuring a firewall.

Proje kapsamında ayrıca aşağıdaki konular ele alınmıştır:
- Biz Debian Kurulumu YAptık
- Kullanıcı ve grup yönetimi
- Disk bölümlendirme (LVM)
- SSH yapılandırması
- Firewall kurulumu
- Sistem izleme (monitoring script)

Aşağıda Debian ve Rocky Linux karşılaştırması ile birlikte güvenlik araçları ve sanallaştırma çözümleri detaylı olarak verilmiştir.

---

## Instructions

### Kurulum
1. VirtualBox üzerinden bir sanal makine oluştur.
2. Debian ISO indir ve minimal kurulum yap (GUI olmadan).
3. Diskleri LVM kullanarak bölümlendir.

### Yapılandırma
- SSH servisini kur ve portunu `4242` olarak değiştir
- Root login'i devre dışı bırak
- Yeni kullanıcı oluştur ve `sudo` grubuna ekle
- Güçlü parola politikası uygula
- UFW firewall aktif et
- Cron ile monitoring script çalıştır

###Resources
- Brute force için Resources kısmına kullanıcı adı ve şifre wordlistleri eklenir.

--- AI KULLANIMI
- Sadece PHP kurulumunda yaşanan sorunda yararlanıldı.

### Çalıştırma
```bash
sudo systemctl status ssh
sudo ufw status
