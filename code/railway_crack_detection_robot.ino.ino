#include <SoftwareSerial.h>

// ===============================
// GSM MODULE (SIM800L)
// RX -> D6
// TX -> D7
// ===============================
SoftwareSerial gsm(6, 7);

// ===============================
// GPS MODULE (GY-NEO6MV2)
// RX -> D4
// TX -> D5
// ===============================
SoftwareSerial gps(4, 5);

// ===============================
// L298N MOTOR DRIVER
// ===============================
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// ===============================
// IR SENSOR (Line / Gap Detection)
// OUT -> D2
// ===============================
#define IR_SENSOR 2

// ===============================
// ULTRASONIC SENSOR
// TRIG -> D12
// ECHO -> D13
// ===============================
#define TRIG 12
#define ECHO 13

long duration;
int distance;

String gpsData = "";
bool alertSent = false;

// ===============================
// SETUP
// ===============================
void setup() {
  Serial.begin(9600);

  gsm.begin(9600);
  gps.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(IR_SENSOR, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.println("Railway Crack Detection Robot Started");
}

// ===============================
// MOTOR FUNCTIONS
// ===============================
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ===============================
// ULTRASONIC DISTANCE
// ===============================
int getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) {
    return 999;   // No object detected
  }

  return duration * 0.034 / 2;
}

// ===============================
// SEND SMS
// ===============================
void sendSMS(String msg) {
  gsm.println("AT+CMGF=1");
  delay(1000);

  // Replace with your own phone number
  gsm.println("AT+CMGS=\"+919290992032\"");
  delay(1000);

  gsm.print(msg);
  delay(1000);

  gsm.write(26);   // CTRL + Z
  delay(5000);
}

// ===============================
// LOOP
// ===============================
void loop() {

  // -------- Read GPS Data --------
  while (gps.available()) {
    char c = gps.read();
    gpsData += c;
    Serial.write(c);

    // Keep only the latest part of the GPS stream
    if (gpsData.length() > 150) {
      gpsData.remove(0, 50);
    }
  }

  // -------- Read Sensors --------
  int irState = digitalRead(IR_SENSOR);
  distance = getDistance();

  Serial.print("IR: ");
  Serial.print(irState);
  Serial.print("  Distance: ");
  Serial.println(distance);

  // ==================================
  // OBSTACLE DETECTION (Ultrasonic)
  // ==================================
  if (distance > 0 && distance < 20) {
    stopRobot();

    if (!alertSent) {
      sendSMS("Obstacle detected! Robot stopped.");
      alertSent = true;
    }

    delay(500);
    return;
  }

  // ==================================
  // BLACK LINE / GAP DETECTION (IR)
  // ==================================
  // Most IR sensors give LOW on black line.
  if (irState == LOW) {

    // Black line detected -> Move forward
    forward();
    alertSent = false;
  }
  else {

    // Gap / Crack detected
    stopRobot();

    if (!alertSent) {
      String smsText = "ALERT! Track gap detected.\n";
      smsText += "Robot stopped.\n";
      smsText += "GPS Data:\n";
      smsText += gpsData;

      sendSMS(smsText);
      alertSent = true;
    }
  }

  delay(100);
}
