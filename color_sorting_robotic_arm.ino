 //servo
 #include<Servo.h>
 Servo s1 ;
 Servo s2 ;
 Servo s3 ;
 Servo s4 ;
 int pin1 = 3 ;
 int pin2 = 11 ;
 int pin3 = 9 ;
 int pin4 = 10 ;

//sonar
int trig=6;
int vcc=7;
int gnd=4;
int echo=5;
float min_val=0;
float ultra_distance[90]={0};
int angle[91]={0};

//color sensor
#define S0 1
#define S1 2
#define S2 12
#define S3 13
#define sensorOut 8
int frequency = 0;
void color_detection(void);
int condition = 0;
int R = 0;
int G = 0;
int B = 0;

void setup() {
  //servo
  s1.attach(pin1,600,2300);
  s1.write(600);
  s2.attach(pin2);
  s3.attach(pin3);
  s4.attach(pin4);

  //sonar
 pinMode(trig,OUTPUT);
 pinMode(gnd,OUTPUT);
 pinMode(vcc,OUTPUT);
 pinMode(echo,INPUT);
 digitalWrite(trig,LOW);
 digitalWrite(gnd,LOW);
 digitalWrite(vcc,HIGH);
 digitalWrite(echo,LOW);

 //color sensor
 pinMode(S0, OUTPUT);
 pinMode(S1, OUTPUT);
 pinMode(S2, OUTPUT);
 pinMode(S3, OUTPUT);
 pinMode(sensorOut, INPUT);
 digitalWrite(S0,HIGH);
 digitalWrite(S1,LOW);

 //serial monitor
 Serial.begin(9600);
}

void loop(){
s1.write(0);
delay(600);
s2.write(120);
delay(600);
s3.write(0);
delay(600);
s4.write(180);
delay(600);

 int j=0;
 int index=-2;// check index value
  
     for (int i=0; i<=100;i+=1)
          {
         s1.write(i);
         delay(50);
         angle[j]=i;
         ultra_distance[j]=measure_distance_cm();
         delay(20);
         Serial.print(" the iteration = ");
         Serial.print(i);
          Serial.print("  ultra_distance =   ");
         Serial.println(ultra_distance[j]);
         j+=1;   
         if (i==90){break;} 
         }
       for (j=0;j<=90;j+=1)
       {min_val=max(min_val,ultra_distance[j]);
      
        }
         
   for (j=0;j<=90;j+=1)
       {if (min_val>ultra_distance[j])
       {
        min_val=ultra_distance[j];
        index=j;}
       
        }
        
       Serial.print("the min value =");
       Serial.println(min_val);
       Serial.print("the index value =");
       Serial.println(index);
       

        s1.write(angle[index]);
        delay(1000);
        s3.write(20);
        delay(1000);
        s2.write(47);
        delay(1000);
        s4.write(120);
        delay(2000);
        for(int m=0;m<100;m--){
        color_detection();
        delay(1000);
        if(condition ==1){   //red
        s2.write(120);
        delay(1000);
        s1.write(0);
        delay(1000);
        s2.write(47);
        delay(1000);
        s4.write(180);
        delay(1000);
        s2.write(120);
        delay(1000);  
        break;}

        else if(condition ==2){  //green
        s2.write(120);
        delay(1000);
        s1.write(30);
        delay(1000);
        s2.write(47);
        delay(1000);
        s4.write(180);
        delay(1000);
        s2.write(120);
        delay(1000); 
        break;}

        else if(condition ==3){  //blue
        s2.write(120);
        delay(1000);
        s1.write(60);
        delay(1000);
        s2.write(47);
        delay(1000);
        s4.write(180);
        delay(1000);
        s2.write(120);
        delay(1000);  
        break;}
                }  
       }

float measure_distance_cm()
{
  float distance =0;
  long time_value=0;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  time_value=pulseIn(echo,HIGH);
  distance=0.033*time_value/2;
  return distance;
    }

void color_detection(){
      digitalWrite(S2,LOW);
      digitalWrite(S3,LOW);
      frequency = pulseIn(sensorOut, LOW);
      Serial.print("R= ");
      Serial.print(frequency);
      Serial.print("  ");
      delay(100);
      R = frequency;

      digitalWrite(S2,HIGH);
      digitalWrite(S3,HIGH);
      frequency = pulseIn(sensorOut, LOW);
      Serial.print("G= ");
      Serial.print(frequency);
      Serial.print("  ");
      delay(100);
      G = frequency;

      digitalWrite(S2,LOW);
      digitalWrite(S3,HIGH);
      frequency = pulseIn(sensorOut, LOW);
      Serial.print("B= ");
      Serial.print(frequency);
      Serial.println("  ");
      delay(100);
      B = frequency;

      if((R>168)&&(R<175)&&(G>217)&&(G<221)&&(B>162)&&(B<171)){condition = 1; }     //red
      else if((R>225)&&(R<236)&&(G>215)&&(G<225)&&(B>170)&&(B<177)){condition = 2; }//green 
      else if((R>219)&&(R<225)&&(G>190)&&(G<200)){condition = 3; }//blue 
    }    
