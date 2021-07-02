

    //Sonar
    const int trigPin = 3;
    const int echoPin = 2;
    float duration, distance;
    int Led_front = 22;

    //DHT + LCD
    #include "DHT.h"
    #define DHTPIN 7 
    #define DHTTYPE DHT22 
    DHT dht(DHTPIN, DHTTYPE);

    #include <Wire.h> 
    #include <LiquidCrystal_I2C.h>
    LiquidCrystal_I2C lcd(0x3F,20,4);

    //Bluetooth
    #include<Servo.h>
    int pin1 = 8 ;
    //int p1 = 28;
    Servo s1 ;
    int ENA = 4;
    int IN1 = 9;
    int IN2 = 6;
    int ENASpeed = 0;
    int Led_1 = 24;
    int Led_2 = 26; 

    //RFID SECURITY
    #include <SPI.h>
    #include <MFRC522.h>
    #define SS_PIN 53
    #define RST_PIN 5
    #define BUZZER 49
    MFRC522 mfrc522(SS_PIN, RST_PIN);
    Servo myServo; 
    

void setup(){

  //sonar
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Led_front, OUTPUT);

  // DHT + LCD
  dht.begin();

  lcd.init();                  
  lcd.init();
  lcd.backlight();

  //Bluetooth
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(Led_1, OUTPUT);
  pinMode(Led_2, OUTPUT);
  //pinMode(p1, OUTPUT);
  s1.attach(pin1);  
  s1.write(90);

  //RFID SECURITY
  SPI.begin();      
  mfrc522.PCD_Init();   
  myServo.attach(10); 
  myServo.write(90);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);

  Serial.begin(9600);
}

void loop(){

    //SONAR
    digitalWrite(Led_front,LOW);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    //Serial.print(" Distance: ");
    //Serial.println(distance); 
    if(distance<15){ digitalWrite(Led_front, HIGH);}
    delay(50);

    // DHT + LCD
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    lcd.setCursor(5,0);
    lcd.print("Smart Home");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.setCursor(10,1);
    lcd.print(h);
    lcd.setCursor(16,1);
    lcd.print("%");
    lcd.setCursor(0,2);
    lcd.print("Temperature: ");
    lcd.setCursor(13,2);
    lcd.print(t);
    lcd.setCursor(19,2);
    lcd.print("C");

    //fan speed
    lcd.setCursor(0,3);
    lcd.print("Fan Speed = ");
    if(t<25){ENASpeed = 150; lcd.setCursor(13,3); lcd.print(" LOW  "); }
    else if((t>=25) && (t<=31)){ENASpeed = 200; lcd.setCursor(13,3); lcd.print("MEDIUM"); }
    else{ENASpeed = 255; lcd.setCursor(13,3); lcd.print(" HIGH "); }

    //BLUETOOTH
    analogWrite(ENA,ENASpeed);
    //digitalWrite(p1,HIGH);
              
    if(Serial.available() == 0);{
    char val = Serial.read();
    Serial.println(val);
        if(val == 'C'){
          digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW); }
        else if(val == 'c'){
          analogWrite(ENA,0);
          digitalWrite(IN1,LOW);
          digitalWrite(IN2,LOW); }
        else if(val == 'A'){ digitalWrite(Led_2,HIGH);}
        else if(val == 'a'){ digitalWrite(Led_2,LOW); }
        else if(val == 'B'){ digitalWrite(Led_1,HIGH);}
        else if(val == 'b'){ digitalWrite(Led_1,LOW); }
        else if(val == 'D'){ s1.write(0);  }
        else if(val == 'd'){ s1.write(120); }
    }

    // RFID SECURITY
    if ( ! mfrc522.PICC_IsNewCardPresent()) { return;}
    if ( ! mfrc522.PICC_ReadCardSerial()) { return;}
    String content= "";
    byte letter;
     for (byte i = 0; i < mfrc522.uid.size; i++) 
  {  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX)); }

     content.toUpperCase();
       if (content.substring(1) == "3B 9D A8 F2") 
  { myServo.write(0);
    delay(5000);
    myServo.write(90); }

     else   {
    tone(BUZZER, 500);
    delay(1000);
    noTone(BUZZER);
  }
}
    
