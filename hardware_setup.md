# 🔌 Hardware Setup Guide  
## ESP32 Headlight Glare Detection System

This guide explains how to connect all hardware components required for the project.

---

## 🧰 Components Used
- ESP32 Development Board  
- LDR (Light Dependent Resistor)  
- 10kΩ Resistor  
- LED  
- 220Ω Resistor (for LED safety)  
- Buzzer  
- Breadboard  
- Jumper Wires  

---

## ⚙️ Overview
The system works using an **LDR-based voltage divider** to measure light intensity.  
The ESP32 reads this value and triggers outputs (LED + buzzer) when glare is detected.

---

## 🔌 Circuit Connections

### 1. LDR Connection (Voltage Divider)

```
3.3V ---- LDR ----+---- GPIO 34 (ESP32)
                  |
               10kΩ
                  |
                 GND
```

### Steps:
- Connect one leg of LDR → **3.3V**  
- Connect other leg of LDR → **GPIO 34**  
- Connect **10kΩ resistor** between GPIO 34 → **GND**

---

### 2. LED Connection

```
GPIO 2 ---- 220Ω ---- LED ---- GND
```

### Steps:
- Connect **GPIO 2 → 220Ω resistor → LED anode (+)**  
- Connect LED cathode (–) → **GND**

---

### 3. Buzzer Connection

```
GPIO 4 ---- Buzzer ---- GND
```

### Steps:
- Connect **GPIO 4 → Buzzer (+)**  
- Connect Buzzer (–) → **GND**

---

## 🧠 Pin Summary

| Component | ESP32 Pin |
|----------|----------|
| LDR Output | GPIO 34 |
| LED        | GPIO 2  |
| Buzzer     | GPIO 4  |

---

## ⚠️ Important Notes

- GPIO 34 is **input-only** (perfect for LDR)
- Always use a **resistor with LED** to avoid damage
- Ensure all **GND connections are common**
- Use **3.3V (NOT 5V)** for ESP32 safety

---

## 🧪 Testing Steps

1. Power the ESP32 via USB  
2. Upload the code  
3. Open Serial Monitor (115200 baud)  
4. Shine light on LDR:
   - Low light → No output  
   - Medium light → LED + slow buzzer  
   - High light → LED + continuous buzzer  

---

## 💡 Tips for Better Performance

- Place LDR inside a **small tube** to focus forward light  
- Avoid ambient room lighting interference  
- Test using phone flashlight or vehicle headlight  

---

## 🚀 Optional Enhancements

- Add second LDR (left/right detection)  
- Add OLED display (I2C)  
- Use enclosure for real-world testing  

---

## 🛠️ Troubleshooting

**No readings?**
- Check wiring of LDR and resistor  

**LED not glowing?**
- Check polarity (+ / –)  

**Buzzer not working?**
- Ensure correct type (active recommended)  

**Wrong readings?**
- Recheck voltage divider connection  

---

## 📌 Conclusion
Once connected correctly, the ESP32 will continuously monitor light intensity and detect headlight glare in real time.

---