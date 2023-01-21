#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 500    // 最小パルス幅(μs)
#define SERVOMAX 2400   // 最大パルス幅(μs)

#define S0MIN 60
#define S0MAX 120
#define S1MIN 60
#define S1MAX 120
#define S2MIN 60
#define S2MAX 120
#define SERVO0PIN 0
#define SERVO1PIN 1
#define SERVO2PIN 2

float mapf(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float limitAngle(float angle, float min, float max){
    angle = angle > max ? max: angle;
    angle = angle < min ? min: angle;
    return angle;
}
String message;
StaticJsonDocument<400> doc;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

float angle0;
float angle1;
float angle2;
int pulse0;
int pulse1;
int pulse2;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(100);
}

void loop() {
  if(Serial.available() > 0){
    message = Serial.readStringUntil('\n');
    Serial.print("message:");
    Serial.println(message);
    DeserializationError error =  deserializeJson(doc, message);
    // 成否判定して失敗したらスキップ
    if(error.code() != DeserializationError::Ok) return;
    angle0 = doc["servo0"];
    angle1 = doc["servo1"];
    angle2 = doc["servo2"];
    Serial.print(angle0);
    Serial.print(",");
    Serial.print(angle1);
    Serial.print(",");
    Serial.println(angle2);
    angle0 = limitAngle(angle0, S0MIN, S0MAX);
    angle1 = limitAngle(angle1, S1MIN, S1MAX);
    angle2 = limitAngle(angle2, S2MIN, S2MAX);
    pulse0 = int(mapf(angle0, 0, 180, SERVOMIN, SERVOMAX));
    pulse1 = int(mapf(angle1, 0, 180, SERVOMIN, SERVOMAX));
    pulse2 = int(mapf(angle2, 0, 180, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(SERVO0PIN, pulse0);
    pwm.writeMicroseconds(SERVO1PIN, pulse1);
    pwm.writeMicroseconds(SERVO2PIN, pulse2);
  }
  delay(100);
}


