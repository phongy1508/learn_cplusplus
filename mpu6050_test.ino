#include <Wire.h> // Uses Wire library
const int MPU = 0x68; // 0x68 is the signal register in the MPU and we keep this register a constant
float AccX;

void setup() {
  Serial.begin(19200);
  Wire.begin();
  // ESP32 default I2C pins are usually SDA = GPIO21, SCL = GPIO22
  // Wake up MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(20);

  // Set accelerometer range to +/- 8g
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission(true);
  delay(20);

  // Set gyro range to +/- 1000 deg/s
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0x10);
  Wire.endTransmission(true);
  delay(20);

  Serial.print("MPU6050 started.");
}

void loop(){
  // Start reading ACCEL_XOUT_H
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  // Request 2 bytes: X high byte and X low byte starting from 0x3B
  Wire.requestFrom(MPU, 2, true);

  // Combine first byte shift left 8 and second byte (3B and 3C)
  AccX = (Wire.read() << 8 | Wire.read())/4096.0;

  Serial.println(AccX);
  delay(50);
}