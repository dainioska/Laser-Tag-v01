//TESTAS for LASER TAG robotic
//versija 2021-10-13
#include <Servo.h>

Servo servoH; //servo Horizontal position
Servo servoW; //servo Vertical position

int del = 170; //value DELAY
int count = 0;
int buttonSt = 0;
int pos = 65; //variable to store the servo position
int posH = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);  //pin button START mode
  pinMode(3, OUTPUT); //pin LED(red) START OK
  pinMode(4, OUTPUT); //pin LED(green) SETUP OK
  pinMode(8, OUTPUT); //pin motor forward
  pinMode(9, OUTPUT); //pin motor backward
  pinMode(10, OUTPUT); //pin motor forward
  pinMode(11, OUTPUT); //pin motor backward
  
  digitalWrite(3, LOW); 
  digitalWrite(4, HIGH); // Setup OK
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(11, LOW); 
  
  servoH.attach(5);  //pin servo H
  servoW.attach(6);  //pin servo V
  servoH.write(pos);
  servoW.write(pos);
  Serial.println("LASER_TAG_motor setup OK");
  delay(3000);        
}

void loop() {
  buttonSt = digitalRead(2);
  
  if(buttonSt == HIGH){
    digitalWrite(3,HIGH);
    motorStop();
    delay(2000);
    for (posH = 65; posH >= 15; posH -= 1) { 
      servoH.write(posH);
      //Serial.print("posHFw= ");
      //Serial.println(posH);
      motorForward(); 
      count = del + posH;  
      Serial.print("countFw= ");
      Serial.println(count); 
      delay(count);                      
  }
    motorStop(); 
    delay(2000);
    for (posH = 15; posH <= 65; posH += 1) {
      servoH.write(posH); 
      //Serial.print("posHBw= ");
      //Serial.println(posH);
      motorBackward();  
      count = del - posH;
      Serial.print("countBw= ");
      Serial.println(count);      
      delay(count);                      
  }
  }
  else{ 
    motorStop();
    servoH.write(pos);
    servoW.write(pos);
    digitalWrite(3, LOW);  
    delay(500);
    digitalWrite(3, HIGH);
    delay(500); 
  }
}

void motorStop(){
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW); 
  digitalWrite(10, LOW); 
  digitalWrite(11, LOW);     
}

void motorForward(){
  digitalWrite(8, HIGH); 
  digitalWrite(9, LOW); 
  digitalWrite(10, HIGH); 
  digitalWrite(11, LOW);            
}

void motorBackward(){
   digitalWrite(8, LOW); 
   digitalWrite(9, HIGH); 
   digitalWrite(10, LOW); 
   digitalWrite(11, HIGH);  
}
