#include <Arduino.h>
#include <SoftI2cMaster.h>

// Change to LDAC pin here
#define LDAC_PIN 2

// Define address here (0-7)
#define OLD_ADDRESS 0
#define NEW_ADDRESS 1

#ifdef CORE_TEENSY
  #define SDA_PIN 18
  #define SCL_PIN 19
#else // Arduino
  #define SDA_PIN A4
  #define SCL_PIN A5
#endif

SoftI2cMaster i2c;

void setup() {
  Serial.begin(9600);
  pinMode(LDAC_PIN, OUTPUT);

  i2c.init(SCL_PIN, SDA_PIN);
  delay(250);

  writeAddress(OLD_ADDRESS, NEW_ADDRESS, LDAC_PIN);
  delay(250);

  uint8_t addr = readAddress(LDAC_PIN);
  Serial.println("Address: ");
  Serial.println(addr);
  Serial.println("Done.");
}

void loop() {}

uint8_t readAddress(int LDACpin) {
  digitalWrite(LDACpin, HIGH);
  int ack1 = i2c.start(0B00000000);
  int ack2 = i2c.ldacwrite(0B00001100, LDACpin); // modified command for LDAC pin latch
  int ack3 = i2c.restart(0B11000001);
  uint8_t address = i2c.read(true);
  i2c.stop();
  delay(100);
  digitalWrite(LDACpin, HIGH);
  Serial.println("");
  Serial.println(ack1);
  Serial.println(ack2);
  Serial.println(ack3);
  return address;
}

void writeAddress(int oldAddress, int newAddress, int LDACpin) {
  digitalWrite(LDACpin, HIGH);
  int ack1 = i2c.start( 0B11000000 | (oldAddress << 1));
  int ack2 = i2c.ldacwrite(0B01100001 | (oldAddress << 2), LDACpin); // modified command for LDAC pin latch
  int ack3 = i2c.write( 0B01100010 | (newAddress << 2));
  int ack4 = i2c.write( 0B01100011 | (newAddress << 2));
  i2c.stop();
  delay(100); // wait for eeprom write
  Serial.println("");
  Serial.println(ack1);
  Serial.println(ack2);
  Serial.println(ack3);
  Serial.println(ack4);
}
