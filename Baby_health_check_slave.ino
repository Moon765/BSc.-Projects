#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

#include <EasyTransfer.h>
EasyTransfer ET;
struct RECEIVE_DATA_STRUCTURE {
  int16_t blinks;
  int16_t pause;
};
RECEIVE_DATA_STRUCTURE mydata;

int buzzer = 12;

void setup() {
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  // initialize the LCD
  lcd.begin();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Health Monitor");

  pinMode(buzzer, OUTPUT);
}

void loop() {
  if (ET.receiveData()) {

    float m = mydata.blinks;
    float n = mydata.pause;
    float i = m/10;
    float j = n/10;

    Serial.println(i);
    Serial.println(j);
    //lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Temperature:");
    lcd.setCursor(0, 2);
    lcd.print(i);
    lcd.setCursor(6, 2);
    lcd.print("*c");

    lcd.setCursor(10, 2);
    lcd.print(j);
    lcd.setCursor(16, 2);
    lcd.print("*F");

    //buzzer
    if ( j >= 102 ) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      //delay(50);
      }
    else {digitalWrite(buzzer, LOW);}
  }
  delay(50);
}
