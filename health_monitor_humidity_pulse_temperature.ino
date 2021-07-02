//lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            2
#define DHTTYPE           DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

//Pulse sensor
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 550;
PulseSensorPlayground pulseSensor;

void setup() {
  //lcd
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Health Monitor");

  //DHT
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

  //pulse
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("pulseSensor Object is created");
  }

  //serial monitor
  Serial.begin(9600);

}

void loop() {
  /*This code is prepared by Mahadi Hasan Moon
    American International University-Bangladesh
    Department on Engineering 
  DHT   */
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float moon = 32 + 5 + event.temperature * 1.8 ;
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("Temperature:");
    lcd.setCursor(12, 1);
    lcd.print(moon);
    lcd.setCursor(18, 1);
    lcd.print("*F");
    delay(100);
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    lcd.setCursor(0, 2);
    lcd.print("Humidity: ");
    lcd.setCursor(10, 2);
    lcd.print(event.relative_humidity);
    lcd.setCursor(16, 2);
    lcd.print("%");
    delay(100);
  }

  //pulse
  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    lcd.setCursor(0, 3);
    lcd.print("BPM: ");
    lcd.println(myBPM);
  }
  delay(20);
}
