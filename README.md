# railways_crack_detection
 Railway Track Crack Detection Robot

A smart Arduino-based railway track monitoring robot that follows a black line representing a railway track and detects cracks or gaps. When a gap is detected, the robot stops and sends an SMS alert with GPS information using GSM and GPS modules.

✨ Features

- Black line following using IR sensor
- Railway crack/gap detection
- Ultrasonic obstacle detection
- SMS alert using SIM800L GSM module
- GPS location reporting using GY-NEO6MV2
- Battery-powered operation (no USB required)

 🛠 Components Used

- Arduino Uno
- L298N Motor Driver
- 2 DC Geared Motors
- IR Line Tracking Sensor
- HC-SR04 Ultrasonic Sensor
- SIM800L GSM Module
- GY-NEO6MV2 GPS Module
- Battery Pack
- Robot Chassis
- Jumper Wires and Breadboard

## 🔌 Pin Connections

| Component | Arduino Pin |
|----------|-------------|
| IR Sensor OUT | D2 |
| GPS RX | D4 |
| GPS TX | D5 |
| GSM RX | D6 |
| GSM TX | D7 |
| L298N IN1 | D8 |
| L298N IN2 | D9 |
| L298N IN3 | D10 |
| L298N IN4 | D11 |
| Ultrasonic TRIG | D12 |
| Ultrasonic ECHO | D13 |

⚙️ Working

1. Robot follows the black line using the IR sensor.
2. Ultrasonic sensor checks for obstacles.
3. If the black line disappears (track crack/gap), the robot stops.
4. GSM module sends an SMS alert.
5. GPS module provides the latest location information.
 🚀 Future Improvements

- Multiple IR sensors for better line following.
- AI-based vision system for real crack detection.
- IoT dashboard for remote monitoring.
- Google Maps link in SMS alerts.
 📷 Project Images

robot photos and wiring diagrams in the `images/` folder.

 📄 License

This project is licensed under the MIT License.
