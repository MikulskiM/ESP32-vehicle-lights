# Projekt symulacji systemu oświetlenia pojazdu z ESP32

## Opis Projektu

Symulacja systemu oświetlenia i sterowania dla modelu pojazdu, zrealizowany w oparciu o mikrokontrolery **ESP32** i system operacyjny czasu rzeczywistego **FreeRTOS**. Projekt dzieli się na trzy niezależne moduły komunikujące się ze sobą. Celem projektu jest stworzenie elastycznej architektury, która pozwoli na łatwe przełączanie między różnymi metodami komunikacji (prototypowo Wi-Fi, docelowo Ethernet po kablu).

## Architektura Systemu

System składa się z trzech głównych modułów (nodów) opartych na ESP32:

1.  **Master Controller (Sterownik Główny):**
    * **Funkcja:** Mózg systemu. Odbiera sygnały wejściowe od użytkownika, przetwarza je i wysyła komendy do modułów świateł.
    * **Wejścia:** 4 przyciski do sterowania ruchem (przód, tył, prawo, lewo), przełączniki do świateł (dzienne/mijania, drogowe, kierunkowskazy).
    * **Wyjścia:** Wyświetlacz OLED do informowania o statusie świateł, kierunkowskazach i błędach systemu.

2.  **Front Lights (Światła Przednie):**
    * **Funkcja:** Moduł odpowiedzialny za sterowanie oświetleniem przednim pojazdu.
    * **Funkcjonalność:** Włączanie/wyłączanie świateł dziennych, świateł mijania, świateł drogowych oraz lewego i prawego kierunkowskazu.

3.  **Rear Lights / Rear Cam (Światła Tylne / Kamera Cofania):**
    * **Funkcja:** Moduł odpowiedzialny za sterowanie oświetleniem tylnym pojazdu i przesyłanie sygnału z kamery cofania kiedy auto jedzie do tyłu.
    * **Funkcjonalność:** Włączanie/wyłączanie świateł hamowania, świateł cofania oraz lewego i prawego kierunkowskazu, przesyłanie danych z kamery cofania.

## Technologia i Narzędzia

* **Mikrokontrolery:** ESP32-WROOM-32 (38-pinowe i 30-pinowe).
* **System operacyjny:** FreeRTOS.
* **Środowisko programistyczne:** PlatformIO (w VS Code).
* **Framework:** ESP-IDF (Espressif IoT Development Framework).
* **Komunikacja:**
    * Docelowo: **Ethernet** za pomocą modułu LAN8720.
    * Tymczasowo: **Wi-Fi** dla uproszczenia fazy testowej.
* **Abstrakcja:** Wykorzystanie wzorca projektowego **Hardware Abstraction Layer (HAL)** poprzez jedną klasę komunikacyjną z dwiema implementacjami (Wi-Fi i Ethernet).

## Struktura Repozytorium

Repozytorium jest podzielone na trzy główne podfoldery, z których każdy zawiera niezależny projekt PlatformIO dla danego modułu ESP32.

* `ESP32-master-controller/` - Projekt dla sterownika głównego z wyświetlaczem.
* `ESP32-front-lights/` - Projekt dla modułu świateł przednich.
* `ESP32-rear-lights-camera/` - Projekt dla modułu świateł tylnych i kamery cofania.

Dodatkowe katalogi:
* `common/` - (Opcjonalnie) folder na pliki i klasy współdzielone między projektami np. komunikacja, logi itp.

## Uruchamianie Projektu

1.  Zainstaluj **PlatformIO** w VS Code.
2.  Sklonuj repozytorium: `git clone [link do repozytorium]`
3.  Otwórz wybrany podprojekt (np. `ESP32-master-controller/`) w VS Code.
4.  W pliku `platformio.ini` zdefiniuj, którego środowiska kompilacji chcesz użyć (np. `esp32_devkitc_38` (38-pin) lub `esp32_devkitc_v1` (30-pin)).
5.  Użyj komendy PlatformIO do wgrania oprogramowania:
    ```bash
    pio run --target upload
    ```
6.  Aby monitorować logi z urządzenia:
    ```bash
    pio device monitor
    ```

OK, rozumiem. Chcesz, żeby lista była prosta, a punkty ułożone w dokładnej kolejności, w jakiej będziesz je realizował, tak aby było to przejrzyste.

Oto uproszczona, chronologiczna lista, gotowa do wklejenia w pliku `README.md`.

---

## Lista Kontrolna Projektu (Checklist)

* [ ] Stworzenie trzech projektów PlatformIO z podstawowymi zadaniami FreeRTOS.
* [ ] Implementacja uniwersalnej klasy komunikacyjnej (Wi-Fi).
* [ ] Proste taski, które migają diodą i wysyłają logi na terminal.
* [ ] Implementacja komunikacji między modułami ESP32 przez Wi-Fi.
* [ ] Stworzenie schematu elektronicznego głównego sterownika i jego wykonanie (przyciski jazdy, przyciski kierunkowskazu, przycisk światła).
* [ ] Implementacja sterownika głównego i przesyłanie sygnałów do świateł.
* [ ] Implementacja wyświetlania statusu na ekranie OLED (błędy, kierunkowskazy, światła).
* [ ] Stworzenie schematów i wykonanie modułów świateł.
* [ ] Implementacja sterowników świateł (Front & Rear).
* [ ] Przejście z komunikacji Wi-Fi na Ethernet (LAN8720).
* [ ] Rozszerzenie modułu tylnego o kamerę cofania.
* [ ] Rozszerzenie modułu tylnego o czujnik odległości.
* [ ] Implementacja wyświetlania danych z kamerki/czujnika na OLED w sterowniku.

---
