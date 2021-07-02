const int trigPin_F = 13;
const int echoPin_F = 2;
const int trigPin_L = 3;
const int echoPin_L = 4;
const int trigPin_R = 5;
const int echoPin_R = 6;
float duration_F, distance_F;
float duration_L, distance_L;
float duration_R, distance_R;
void sonar_value(void);
int ENA = 9; //Enable Pin of the Right Motor (must be PWM)
int IN1 = 7; //Control Pin
int IN2 = 8;
int ENB = 10; //Enable Pin of the Left Motor (must be PWM)
int IN3 = 11;
int IN4 = 12;
int condition = 0;
//Speed of the Motors
#define ENASpeed 255
#define ENBSpeed 255
void conditions(void);
void motor_control(void);
void setup() {
  //sonar
pinMode(trigPin_F, OUTPUT);
pinMode(echoPin_F, INPUT);
pinMode(trigPin_L, OUTPUT);
pinMode(echoPin_L, INPUT);
pinMode(trigPin_R, OUTPUT);
pinMode(echoPin_R, INPUT);
Serial.begin(9600);
//motor
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT); }
void loop(){
  sonar_value();
  conditions();
  motor_control(); }
void sonar_value(){
  //front
  digitalWrite(trigPin_F, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_F, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_F, LOW);
  duration_F = pulseIn(echoPin_F, HIGH);
  distance_F = (duration_F*.0343)/2;
  Serial.print(" Distance_F: ");
  Serial.print(distance_F);
  //right
  digitalWrite(trigPin_R, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_R, LOW);
  duration_R = pulseIn(echoPin_R, HIGH);
  distance_R = (duration_R*.0343)/2;
  Serial.print(" Distance_R: ");
  Serial.print(distance_R);
  //left
  digitalWrite(trigPin_L, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_L, LOW);
  duration_L = pulseIn(echoPin_L, HIGH);
  distance_L = (duration_L*.0343)/2;
  Serial.print(" Distance_L: ");
  Serial.println(distance_L);
  delay(100); }
void conditions(){
  if((distance_F<35)&&(distance_L<25)&&(distance_R<25)){condition = 0; }
else if((distance_F<35)&&(distance_L<25)&&(distance_R>25)){condition = 6; }
else if((distance_F<35)&&(distance_L>25)&&(distance_R<25)){ condition = 5;}
else if((distance_F<35)&&(distance_L>25)&&(distance_R>25)){condition = 2;}
else if((distance_F>35)&&(distance_L<25)&&(distance_R<25)){ condition = 1;}
else if((distance_F>35)&&(distance_L<25)&&(distance_R>25)){condition = 4;}
else if((distance_F>35)&&(distance_L>25)&&(distance_R<25)){condition = 3;}
else if((distance_F>35)&&(distance_L>25)&&(distance_R>25)){condition = 1;}
else{ condition = 0;}                     }
void motor_control(){
  analogWrite(ENA, ENASpeed);
  analogWrite(ENB, ENBSpeed);
if(condition == 0){//stop
   //motor a stop
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b stop
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);  }
 else if(condition == 1){//forward
   //motor a forward
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b forward
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);  }
   else if(condition == 2){//reverse
   //motor a BACKWARD
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b BACKWORD
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   delay(600);
   //motor a stop
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b BACKWORD
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   delay(400);
   //motor a FOORWARD
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b FORWARD
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);   }
   else if(condition == 3){//TURN LEFT
   //motor a FORWARD
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b STOP
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);  }
    else if(condition == 4){//TURN RIGHT
   //motor a STOP
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b FORWARD
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);  }
   else if(condition == 5){//TURN LEFT + BACK
   //motor a BACKWARD
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b BACKWORD
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   delay(600);
   //motor a stop
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b BACKWORD
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   delay(400);
   //motor a FOORWARD
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b FORWARD
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);  }
   else if(condition == 6){//TURN RIGHT + BACK
   //motor a BACKWARD
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b BACKWORD
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);  
   delay(600);
   //motor a BACKWARD
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b STOP
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);  
   delay(400);
   //motor a FOORWARD
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b FORWARD
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);   }     }
