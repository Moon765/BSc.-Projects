int ENA = 3; //Enable Pin of the Right Motor (must be PWM)
int IN1 = 1; //Control Pin
int IN2 = 2;

int ENB = 6; //Enable Pin of the Left Motor (must be PWM)
int IN3 = 4;
int IN4 = 5;

//Speed of the Motors
#define ENASpeed 100
#define ENBSpeed 100
//SENSOR PIN
float sensor1 = A1;
float sensor2 = A2;
float sensor3 = A3;
float sensor4 = A4;
float sensor5 = A5;
float sensor6 = A6;
float sensor7 = A7;
float sensitivity = 7;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0; 
int f = 0;
int g = 0;
//ir digital ARRAY
int sensor[7]={0, 0, 0, 0, 0, 0, 0};
//motor control
int control;
void read_sensor_values(void);
void conditions(void);
void motor_control(void);

void setup(){
  //motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //ir
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  pinMode(sensor5,INPUT);
  pinMode(sensor6,INPUT);
  pinMode(sensor7,INPUT);
  pinMode(sensitivity,OUTPUT);
}

void loop(){
  // IR SENSITIVITY
  analogWrite(sensitivity,255);
  //MOTOR SPEED
  analogWrite(ENA, ENASpeed);
  analogWrite(ENB, ENBSpeed);
  read_sensor_values();
  conditions();
  motor_control();
}

void read_sensor_values(){
  a = analogRead(sensor1);
  b = analogRead(sensor2);
  c = analogRead(sensor3);//not using because of critical point
  d = analogRead(sensor4);
  e = analogRead(sensor5);//not using because of critical point
  f = analogRead(sensor6);
  g = analogRead(sensor7);
// analog to digital conversion
  if (a > 100){
    sensor[0] = HIGH;}
  else{ 
  sensor[0] = LOW;}
  
  if (b > 100){
    sensor[1] = HIGH;}
  else{ 
  sensor[1] = LOW;}

    if (c > 100){
    sensor[2] = HIGH;}
  else{ 
  sensor[2] = LOW;}

  if (d > 100){
    sensor[3] = HIGH;}  
  else{ 
  sensor[3] = LOW;}

    if (e > 100){
    sensor[4] = HIGH;}
  else{ 
  sensor[4] = LOW;}

  if (f > 100){
    sensor[5] = HIGH;}
  else{ 
  sensor[5] = LOW;}

  if (g > 100){
    sensor[6] = HIGH;}
  else{ 
  sensor[6] = LOW;}
}

void conditions(){
  if((sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0))
  control = 0;
  else if((sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0))// FORWARD
  control = 1;

  else if((sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0))// RIGHT +
  control = 2;

  else if((sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1))// LEFT +
  control = 3;

  else
  control = 0;
}

void motor_control(){
  
  if(control == 0){//   STOP
        //motor a stop
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b stop
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW); 
  }
  
  else if(control == 1){// GO FORWARD
        //motor a forward
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b forward
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);  
  }

  else if(control == -1){// GO BACKWORD
    //motor a backword
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b backword
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH); 
  }

  else if(control == 2){// TURN RIGHT (FORWARD MOVEMENT)
      //motor a stop
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b forward
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
  }

  else if(control == -2){// TURN LEFT (BACKWORD MOVEMENT)
      //motor a stop
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW);
   //motor b backward
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
  }

  else if(control == 3){// TURN LEFT (FORWARD MOVEMENT)
        //motor a forward
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b stop
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);
  }

  else if(control == -3){// TURN RIGHT ( BACKWORD MOVEMENT)
      //motor a backword
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b STOP
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);
     }
     
  else if(control == 4){// TURN RIGHT ( CENTER MOVEMENT)
      //motor a backword
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   //motor b forward
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
  }     

  else if(control == -4){// TURN LEFT (CENTER MOVEMENT)
      //motor a forward
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   //motor b backward
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
  }

}

