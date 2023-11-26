# esp32-s3
Bu kod, ESP32 cihazının başlangıcında LittleFS dosya sistemi kullanarak ssid.txt ve password.txt dosyalarını okur. Eğer bu dosyalar mevcutsa, içlerindeki SSID ve şifre bilgilerini alır ve WiFi'ye bağlanmayı dener. Eğer bağlantı başarılı olursa, "LittleFS ile bağlandı" mesajını seri monitöre yazdırır.

Eğer bağlantı başarısız olursa veya dosyalar mevcut değilse, WiFiManager kütüphanesini kullanarak bir erişim noktası (AP) oluşturur ve kullanıcıdan yeni SSID ve şifre bilgilerini alır. Bu bilgileri aldıktan sonra, WiFi'ye bağlanmayı dener ve başarılı olursa "WiFi Manager ile bağlandı" mesajını seri monitöre yazdırır. Bağlantı bilgilerini ssid.txt ve password.txt dosyalarına kaydeder.

Bu şekilde, ESP32 cihazınızı başlattığınızda, LittleFS dosya sistemi kullanılarak ağ bilgilerini okur ve WiFi'ye bağlanmayı dener. Eğer ağ bilgileri mevcut değilse veya bağlantı başarısız olursa, WiFiManager kullanarak yeni ağ bilgilerini alır ve bağlanmayı dener.
