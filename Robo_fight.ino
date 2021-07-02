
#include <AFMotor.h>
#include <Servo.h>


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int pwm;


void setup() {
  pwm = 255;
  motor1.setSpeed(pwm);
  motor2.setSpeed(pwm);
  motor3.setSpeed(pwm);
  motor4.setSpeed(pwm);

  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0);
  char val = Serial.read();
  Serial.println(val);

  motor1.setSpeed(pwm);
  motor2.setSpeed(pwm);
  motor3.setSpeed(pwm);
  motor4.setSpeed(pwm);

  if (val == '0') {
    pwm = 0;
  }
  else if (val == '1') {
    pwm = 30;
  }
  else if (val == '2') {
    pwm = 60;
  }
  else if (val == '3') {
    pwm = 90;
  }
  else if (val == '4') {
    pwm = 120;
  }
  else if (val == '5') {
    pwm = 150;
  }
  else if (val == '6') {
    pwm = 180;
  }
  else if (val == '7') {
    pwm = 210;
  }
  else if (val == '8') {
    pwm = 240;
  }
  else if (val == '9') {
    pwm = 255;
  }

  else if (val == 'S') { //stop
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);

  }

  else if (val == 'F') { //FORWARD
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }

  else if (val == 'B') { //BACKWARD
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }

  else if (val == 'L') { //LEFT
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
  }

  else if (val == 'R') { //RIGHT
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
  }

  else if (val == 'G') { //LITTLE LEFT FORWARD
    motor1.run(RELEASE);
    motor2.run(FORWARD);
    motor3.run(RELEASE);
    motor4.run(FORWARD);
  }

  else if (val == 'I') { //LITTLE RIGHT FORWARD
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    motor3.run(FORWARD);
    motor4.run(RELEASE);
  }

  else if (val == 'H') { //LITTLE LEFT BACKWARD
    motor1.run(BACKWARD);
    motor2.run(RELEASE);
    motor3.run(BACKWARD);
    motor4.run(RELEASE);
  }

  else if (val == 'J') { //LITTLE RIGHT BACKARD
    motor1.run(RELEASE);
    motor2.run(BACKWARD);
    motor3.run(RELEASE);
    motor4.run(BACKWARD);
  }
}
