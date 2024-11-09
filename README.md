# Spy-Fi - Wi-Fi Repeater + Jammer Detector

![Meme](https://i.imgflip.com/1ihzfe.jpg)
*When your ESP8266 catches Wi-Fi jammers in the act.*

## Overview
**Wi-Fi Repeater + Jammer Detector** is an ESP8266-based project that acts as both a Wi-Fi repeater and a basic jammer detection tool. It extends Wi-Fi range by creating a secondary network and provides alerts if it detects deauthentication attacks, a common method in Wi-Fi jamming.

---

## Disclaimer
**This project is intended for educational and ethical use only.** Monitoring Wi-Fi networks and detecting jamming signals may be subject to legal regulations in certain jurisdictions. Use responsibly and with appropriate permissions. The authors are not responsible for any misuse of this code or any legal consequences arising from its unauthorized use.

---

## Features
- **Wi-Fi Repeater**: Expands your Wi-Fi network range.
- **Jammer Detection**: Detects deauthentication packets, a signal used in Wi-Fi jamming attacks.
- **Visual LED Alert**: LED notification for detected jamming activity.
- **Email Alerts**: Optional email notifications when a jamming attempt is detected.
- **Web Interface**: Provides real-time jammer detection data and network information.

---

## Installation

### Requirements
- **ESP8266** (e.g., NodeMCU)
- **Arduino IDE**
- **LED** (optional, for visual alert)
- **Wi-Fi credentials** for both primary and repeater networks
- **SMTP Account** (optional for email alerts)

### Steps

1. **Set Up Arduino IDE**:
   - In Arduino IDE, go to **File > Preferences**.
   - Add the URL `http://arduino.esp8266.com/stable/package_esp8266com_index.json` under **Additional Board Manager URLs**.
   - Go to **Tools > Board > Board Manager**, search for **ESP8266**, and install it.

2. **Wiring**:
   - Connect an LED to GPIO pin **D4** with a resistor (220 ohms recommended).
   - Connect the LED anode (longer leg) to **D4** and the cathode to **GND**.

3. **Upload the Code**:
   - Update `primarySSID`, `primaryPassword`, `repeaterSSID`, and `repeaterPassword` in the code with your Wi-Fi details.
   - Configure `sendEmailAlert()` in the code with your SMTP server details if you want email alerts.
   - Select **ESP8266 board** and **COM port** in **Tools**, then upload the code to your ESP8266.

4. **Access the Web Interface**:
   - Connect a device to the ESP8266’s repeater network.
   - Enter the ESP8266’s IP address (usually `192.168.4.1`) in a browser to access the web interface.

---

## How to Use
1. **Repeater Function**: Connect devices to the ESP8266’s repeater network (`Repeater_SSID`) to extend Wi-Fi range.
2. **Jammer Detection Alerts**:
   - The LED will flash if the ESP8266 detects a potential jamming attack.
   - Optional email notifications can be set up to alert you in real time.
3. **Web Interface**: Open the ESP8266's IP address in a browser to monitor the status of detected jamming attacks and connection information.

---

## Advantages
- Extends Wi-Fi coverage in low-signal areas.
- Provides basic alerting for Wi-Fi deauthentication-based jamming.
- Simple to set up and monitor through a web interface.

## Disadvantages
- Only detects deauthentication attacks, a specific jamming type.
- Provides alerts but cannot actively block attacks.
- SMTP setup for email notifications may require additional configuration.

---

## License
This project is open-source and available under the MIT License. Please refer to the license file for more details.

