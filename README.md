# Data-Driven Vehicle Control using CAN Protocol 🚗📡

This project demonstrates a **multi-node vehicle control system** using the **Controller Area Network (CAN)** protocol with the **LPC21xx microcontroller series**. The system simulates core automotive features such as temperature monitoring, window control, and proximity sensing (obstacle detection) — mimicking real-time data-driven communication between different Electronic Control Units (ECUs).

---

## 📁 Files Structure
```
project-root/
├── MainNode/
│   ├── mainTxNode.c
│   ├── lcd.c/h
│   ├── ds18b20.c/h
│   ├── external_interrupt.c/h
│   ├── can.c/h
│   ├── defines.h
│   ├── delay.c/h
│   └── pin_function_defines.h
│
├── DistanceNode/
│   ├── adc.c/h
│   ├── can.c/h
│   ├── lcd.c/h
│   ├── defines.h
│   └── delay.c/h
│
├── WindowNode/
│   ├── node_window.c
│   ├── can.c/h
│   ├── defines.h
│   └── delay.c/h
│
├── can_defines.h
├── types.h
└── README.md
```

---

## 🔌 Hardware Requirements
- **LPC2129 Development Boards (3 Units)**
- **CAN Transceivers (MCP2551)**
- **DS18B20 Temperature Sensor**
- **GP2D12 IR Distance Sensor**
- **16x2 LCD Display**
- **Buzzer**
- **External Interrupt Buttons (4)**
- **LEDs for Window Control (8)**
- **Power Supply 5V/3.3V**

---

## 🔧 Features by Node

### 🧠 Main Node (Master ECU)
- Handles **LCD display**, **external interrupts**, **DS18B20 temperature sensor**.
- Acts as a transmitter based on external triggers (EINT0–EINT3).
- Interacts with **window** and **distance nodes** via CAN.
- Displays vehicle status (Engine, Window, Temperature).
- Controls buzzer warning for obstacle detection.

### 📏 Distance Node
- Uses **GP2D12 Analog IR Sensor** via ADC.
- Measures obstacle distance and returns it via CAN.
- Works as a slave ECU responding to main node.

### 🪟 Window Node
- Receives control frames via CAN.
- Controls virtual window LEDs (8-bit output).
- Simulates window up/down actions.

---


## 🔁 Communication Flow

```text
User Button Press
    ↓
Main Node triggers CAN Tx (Window/Distance ID)
    ↓
→ Window Node controls LEDs (based on data)
→ Distance Node sends obstacle range
    ↓
Main Node reads and displays data
          +
    Activates buzzer if obstacle < 12cm
```

---

## 🧠 Interrupts Used
- **EINT0** – Reverse Mode Activation
- **EINT1** – Window Up
- **EINT2** – Window Down
- **EINT3** – Engine ON/OFF Toggle

---


## 🔄 CAN Protocol Usage

All nodes use **CAN1** (11-bit identifier, standard frame) for communication. Each node:
- Initializes CAN controller
- Configures **TX/RX message buffers**
- Encodes message using the `CAN_Frame` structure:
  ```c
  struct CAN_Frame {
    u32 ID;
    struct {
      u8 RTR : 1;
      u8 DLC : 4;
    } vbf;
    u32 Data1, Data2;
  };
  ```
---

## 📬 CAN Message IDs
| ID | Function           |
|----|--------------------|
| 2  | Window Up/Down     |
| 3  | Reverse Gear Alert |
| 5  | Obstacle Distance  |

---

## 🛠️ How to Build & Run
1. **IDE:** Keil uVision or any ARM-compatible IDE.
2. **Simulate:** Proteus 8.0 or later for virtual testing.
3. **Flash:** Use Flash Magic to program HEX into LPC2129.
4. **Test:** Press interrupt buttons to simulate window and obstacle detection.

---
## 🚦 How to Test

1. **LCD Testing**  
   Check whether the LCD displays static messages.

2. **Sensor Testing**  
   - Connect DS18B20: Display temperature on LCD.
   - Connect GP2D12: Display distance (verify conversion accuracy).

3. **Interrupt Testing**  
   Press SW1, SW2, and SW3 (engine) and observe LCD/control behavior.

4. **CAN Testing**  
   - Trigger SW1/SW2 to send data to window node and watch LEDs.
   - Move object in front of GP2D12 to test reverse alert → observe buzzer activation.

5. **Integration**  
   Run all three nodes simultaneously and verify CAN communication and coordination.

## 🖼️ Block Diagram

```
+-------------------+           +------------------+           +--------------------+
|    Main Node      |  <=====>  |   Window Node    |  <=====>  |  Distance Node     |
| - LCD Display     |           | - LED-based      |           | - GP2D12 Sensor    |
| - DS18B20 Temp    |           |   Window Status  |           | - Reverse Alert Tx |
| - External Switch |           +------------------+           +--------------------+
| - CAN Tx/Rx       |
+-------------------+
```



## 📊 Sensor Calibration
**GP2D12 Sensor Equation:**
```
Distance (cm) = 27.86 / (ADC_Value - 0.42)
```
- Returns 1234 if out of range or too close.
- Triggers **buzzer ON** if distance < 12cm.

---

## 💡 Highlights
- Real-time CAN communication ⚙️
- Custom LCD characters for UI 🔤
- Interrupt-based user control 🚦
- Sensor interfacing: One-wire & analog 🧪
- Modular and scalable node design 🧩

---

## 🤝 Credits

- Developed as part of **Embedded Systems Training**
- Based on **ARM7 LPC2129** architecture
- Guided by trainers from **Vector India**

## 🏁 Final Output

If your system:
- Displays engine temperature
- Controls window LEDs via switches
- Alerts when reversing near an object

## ✍️ Author

This project was developed by **RAJESH GURI** as part of an academic and practical exploration of CAN-based embedded vehicle systems.
