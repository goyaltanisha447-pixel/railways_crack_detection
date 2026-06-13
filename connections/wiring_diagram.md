# 🔌 Wiring Diagram

flowchart LR

    B[Battery Pack]
    L[L298N Motor Driver]
    A[Arduino Uno]

    IR[IR Sensor]
    US[HC-SR04 Ultrasonic]
    GSM[SIM800L GSM Module]
    GPS[GY-NEO6MV2 GPS Module]

    M1[Left DC Motor]
    M2[Right DC Motor]

    %% Power
    B -->|+12V / VIN| L
    B -->|GND| L
    L -->|5V| A
    L -->|GND| A

    %% Motors
    L --> M1
    L --> M2

    %% Motor control
    A -->|D8| L
    A -->|D9| L
    A -->|D10| L
    A -->|D11| L

    %% IR Sensor
    A -->|D2| IR
    L -->|5V| IR
    L -->|GND| IR

    %% GPS
    A -->|D4 (RX)| GPS
    A -->|D5 (TX)| GPS
    L -->|5V| GPS
    L -->|GND| GPS

    %% GSM
    A -->|D6 (RX)| GSM
    A -->|D7 (TX)| GSM
    L -->|GND| GSM

    %% Ultrasonic
    A -->|D12 (TRIG)| US
    A -->|D13 (ECHO)| US
    L -->|5V| US
    L -->|GND| US
    
    | Module          | Arduino Pin |
| --------------- | ----------- |
| IR Sensor OUT   | D2          |
| GPS RX          | D4          |
| GPS TX          | D5          |
| GSM RX          | D6          |
| GSM TX          | D7          |
| L298N IN1       | D8          |
| L298N IN2       | D9          |
| L298N IN3       | D10         |
| L298N IN4       | D11         |
| Ultrasonic TRIG | D12         |
| Ultrasonic ECHO | D13         |

power supply 
| From            | To          |
| --------------- | ----------- |
| Battery +       | L298N 12V   |
| Battery –       | L298N GND   |
| L298N 5V        | Arduino 5V  |
| L298N GND       | Arduino GND |
| IR Sensor VCC   | L298N 5V    |
| GPS VCC         | L298N 5V    |
| Ultrasonic VCC  | L298N 5V    |
| All module GNDs | Common GND  |
