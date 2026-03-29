# 🔌 Hardware Setup Guide  
## ESP32-CAM Headlight Glare Detection System (Vision-Based)

This guide explains how to connect all hardware components required for the ESP32-CAM based glare detection system.

---

## 🧰 Components Used
- ESP32-CAM (AI Thinker Module)
- FTDI Programmer / USB-to-Serial Module
- LED (optional)
- Buzzer (optional)
- Breadboard
- Jumper Wires

---

## ⚙️ Overview
This system uses the ESP32-CAM module to capture images and detect headlight glare using brightness intensity analysis.

Unlike LDR-based systems, no external light sensor is required.  
All detection is done using the camera.

---

## 🔌 Circuit Connections

### 1. ESP32-CAM Programming Connections

FTDI Programmer → ESP32-CAM  
5V → 5V  
GND → GND  
TX → U0R  
RX → U0T  
GND → GPIO0 (ONLY during upload)

Steps:
- Connect FTDI to ESP32-CAM as shown above  
- Connect GPIO0 to GND to enter flashing mode  
- Upload code  
- After upload:
  - Remove GPIO0 from GND  
  - Press RESET button  

---

### 2. LED Connection (Optional Alert)

GPIO 4 → LED → GND  

Steps:
- Connect GPIO 4 → LED anode (+)  
- Connect LED cathode (–) → GND  

Note: GPIO 4 is also connected to onboard flash LED.

---

### 3. Buzzer Connection (Optional)

GPIO 12 → Buzzer → GND  

Steps:
- Connect GPIO 12 → Buzzer (+)  
- Connect Buzzer (–) → GND  

---

## 🧠 Pin Summary

Component → ESP32-CAM Pin  
Camera → Built-in  
LED → GPIO 4  
Buzzer → GPIO 12  
Flash Mode → GPIO 0  

---

## ⚠️ Important Notes

- ESP32-CAM must be powered with 5V, not 3.3V  
- GPIO0 → GND is ONLY for uploading code  
- Remove GPIO0 connection before normal operation  
- Ensure all GND connections are common  
- Avoid using pins used by the camera internally  

---

## 🧪 Testing Steps

1. Connect ESP32-CAM via FTDI  
2. Upload the code  
3. Remove GPIO0 from GND  
4. Press RESET  
5. Open Serial Monitor (115200 baud)  

Test:
- Dark environment → No glare detected  
- Shine flashlight → Glare detected  
- LED/Buzzer should activate  

---

## 💡 Tips for Better Performance

- Mount camera facing road direction  
- Avoid direct sunlight into camera  
- Use low-light/night conditions for testing  
- Keep camera stable  

---

## 🚀 Optional Enhancements

- Add relay module for automatic headlight dimming  
- Add WiFi streaming for live monitoring  
- Improve detection using object tracking  
- Build enclosure for real-world deployment  

---

## 🛠️ Troubleshooting

Camera not working?
- Check power supply (use stable 5V)

Upload failed?
- Ensure GPIO0 is connected to GND

No output?
- Check Serial Monitor
- Verify threshold values in code

LED not working?
- Check polarity and GPIO pin

Random detection?
- Adjust brightness threshold in code

---

## 📌 Conclusion
Once connected correctly, the ESP32-CAM will continuously capture frames and detect headlight glare using image processing in real time.