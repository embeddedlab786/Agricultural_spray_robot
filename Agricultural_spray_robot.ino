#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(A0, A1);

Servo servo_1;
Servo servo_2;

int motor_r2 = 6;
int motor_r1 = 7;

int motor_l2 = 8;
int motor_l1 = 9;

int state;
int speed = 130;

int pos1 = 90;
int pos2 = 90;

int pump = 4;
int pwm = 5;

void setup(){
servo_1.attach(2);
servo_2.attach(3);
servo_1.write(pos1); 
servo_2.write(pos2); 

pinMode(motor_l1, OUTPUT);
pinMode(motor_l2, OUTPUT); 
pinMode(motor_r1, OUTPUT);
pinMode(motor_r2, OUTPUT);

pinMode(pump, OUTPUT);

pinMode(pwm, OUTPUT);

// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
BT.begin(9600); // Setting the baud rate of Software Serial Library 
 
 delay(1000);
 }

void loop(){
//if some date is sent, reads it and saves in state
if(BT.available() > 0){     
state = BT.read(); 
Serial.println(state);
if(state > 15){speed = state;}      
}
  
   // if the state is '1' the DC motor will go forward
     if (state == 1){forword();Serial.println("Forward!");}

// if the state is '2' the motor will Backword
else if (state == 2){backword();Serial.println("Backword!");}
    
// if the state is '3' the motor will turn left
else if (state == 3){turnLeft();Serial.println("Turn LEFT");}
    
// if the state is '4' the motor will turn right
else if (state == 4){turnRight();Serial.println("Turn RIGHT");}
    
// if the state is '5' the motor will Stop
else if (state == 5) {stop();Serial.println("STOP!");}    

else if (state == 6) {Serial.println("lift");  if(pos1<180){pos1 = pos1+1;}} 
else if (state == 7) {Serial.println("right"); if(pos1>0){pos1 = pos1-1;}} 
else if (state == 8) {Serial.println("up");    if(pos2>0){pos2 = pos2-1;}}  
else if (state == 9) {Serial.println("down");  if(pos2<180){pos2 = pos2+1;}} 

else if (state == 10){Serial.println("pump on");digitalWrite(pump, HIGH);} 
else if (state == 11){Serial.println("pump off");digitalWrite(pump, LOW);} 

servo_1.write(pos1); 
servo_2.write(pos2); 

analogWrite(pwm, speed);
delay(30);
}


void stop(){
    digitalWrite(motor_l1, LOW);
    digitalWrite(motor_l2, LOW); 
    digitalWrite(motor_r1, LOW);
    digitalWrite(motor_r2, LOW);
}

void forword(){
    digitalWrite(motor_l1, LOW);
    digitalWrite(motor_l2, HIGH); 
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW);  
}

void backword(){
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW); 
    digitalWrite(motor_r1, LOW);
    digitalWrite(motor_r2, HIGH);   
}


void turnRight(){
    digitalWrite(motor_l1, LOW);
    digitalWrite(motor_l2, HIGH); 
    digitalWrite(motor_r1, LOW);
    digitalWrite(motor_r2, HIGH);  
}

void turnLeft(){
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW); 
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW); 
}

