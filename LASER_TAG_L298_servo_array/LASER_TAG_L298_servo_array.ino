//LASER_TAG_project
//L298_servo_button_array_versija
//2021-10-21 test on board OK

#include <Servo.h>
Servo myservoH;
Servo myservoV;
int positionH = 90;         //state variable(servoH)
int positionV = 90;         //state variable(servoV)
boolean forward = false;   //state variab(servo)

//-------------***Time delay variables in miliseconds***-----------/////
int stp = 20000;
int x = 260;
int y = 140;
int z = 5;
int a1 = 80;  //5
int a2 = 70;  //10
int b1 = 50;  //15
int b2 = 40;   //20
int c1 = 30;  //25
int c2 = 20;  //30
int d1 = 1;  //35
int d2 = 1;  //40
int e1 = 1;  //45
int e2 = 1;  //50
int f1 = 1;  //55
int f2 = 1;  //60
int g1 = 1;  //65
int g2 = 50;  //70
int h1 = 60;  //75
int h2 = 60;  //80
int k1 = 70;  //85
int k2 = 80;  //90


///
int angMin[] = {90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70,
                69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,
                49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30,
                29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
                9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0
               }; // -90 degrees array//
////
int angMax[] = {90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
                111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
                131, 132, 133, 134, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150,
                151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
                171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 180
               }; // +90 degrees array//

////***Target angle 45 degrees ,start position line 3 meters x 1.5 meters***////
int period[] = {x + 1 * a1, x + 2 * a1, x + 3 * a1, x + 4 * a1, x + 5 * a1,
                x + 1 * a2, x + 2 * a2, x + 3 * a2, x + 4 * a2, x + 5 * a2,
                x + 1 * b1, x + 2 * b1, x + 3 * b1, x + 4 * b1, x + 5 * b1,
                x + 1 * b2, x + 2 * b2, x + 3 * b2, x + 4 * b2, x + 5 * b2,
                x + 1 * c1, x + 2 * c1, x + 3 * c1, x + 4 * c1, x + 5 * c1,
                y + 1 * c2, y + 2 * c2, y + 3 * c2, y + 4 * c2, y + 5 * c2,
                y + 1 * d1, y + 2 * d1, y + 3 * d1, y + 3 * d1, y + 3 * d1,
                z + 1 * d2, z + 1 * d2, z + 1 * d2, z + 1 * d2, z + 1 * d2,
                z + 1 * e1, z + 1 * e1, z + 1 * e1, z + 1 * e1, z + 1 * e1,
                z + 1 * e2, z + 1 * e2, z + 1 * e2, z + 1 * e2, z + 1 * e2,
                y + 1 * f1, y + 1 * f1, y + 1 * f1, y + 1 * f1, y + 1 * f1,
                y + 1 * f2, y + 2 * f2, y + 3 * f2, y + 4 * f2, y + 5 * f2,
                y + 1 * g1, y + 2 * g1, y + 3 * g1, y + 4 * g1, y + 5 * g1,
                y + 1 * g2, y + 2 * g2, y + 3 * g2, y + 4 * g2, y + 5 * g2,
                y + 1 * h1, y + 2 * h1, y + 3 * h1, y + 4 * h1, y + 5 * h1,
                y + 1 * h2, y + 2 * h2, y + 3 * h2, y + 4 * h2, y + 5 * h2,
                y + 1 * k1, y + 2 * k1, y + 3 * k1, y + 4 * k1, y + 5 * k1,
                y + 1 * k2, y + 2 * k2, y + 3 * k2, y + 4 * k2, y + 5 * k2,
                stp
               };

//--------------------------------------------------------------------//
//***parameters to L298N regulator***/////
int buttonSt = 0; //start button

unsigned long inter1 = 30000; //***Moving time in miliseconds***/////
unsigned long prev1 = 0;
int drt = 0 ;

void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP); //start button input
  pinMode(6, OUTPUT); //LED setup OK
  pinMode(7, OUTPUT); //LED start OK
  pinMode(8, OUTPUT); //pinA motor forward
  pinMode(9, OUTPUT); //pinB motor backward
  pinMode(10, OUTPUT); //pinA motor forward
  pinMode(11, OUTPUT); //pinB motor backward
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH); //setup OK
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  myservoH.attach(2); //pin servo Horizontal
  myservoV.attach(3); //pin servo Vertical
  myservoH.write (positionH); //setup position servo Horizontal
  myservoV.write (positionV); //setup position servo Vertical
  Serial.println("setup OK");
  delay(1000);
}

void loop() {
  //***start BUTTON code***//////
  buttonSt = digitalRead(5);
  if (buttonSt == HIGH) {
    digitalWrite(7, HIGH);


    //***SERVO_MIN code ***/////
    static uint32_t timer;
    static byte mode = 0;
    if (millis() - timer >= period[mode]) {
      timer = millis();
      if (++mode >= 91) mode = 0;  //***important TO CHANGE AN ANGLE parameter !!!***/////
      myservoH.write(angMin[mode]);
      Serial.print("angMin= ");
      Serial.print(angMin[mode]);
      Serial.print(" period= ");
      Serial.println(period[mode]);
    }

    //***SERVO_MAX code***/////
    //    static uint32_t timer;
    //    static byte mode = 0;
    //    if (millis() - timer >= period[mode]) {
    //      timer = millis();
    //      if (++mode >= 91) mode = 0;  //***important TO CHANGE AN ANGLE parameter !!!***/////
    //      myservoH.write(angMax[mode]);
    //      Serial.print("angMax= ");
    //      Serial.print(angMax[mode]);
    //      Serial.print(" period= ");
    //      Serial.println(period[mode]);
    //    }

    //Serial.println(drt);
    //***L298 motor code***/////
    if ( drt == 0)
    {
      //Serial.println(">>Fw ");
      motorForward();
    }
    else if ( drt == 1)
    {
      //Serial.println(">>Stop ");
      motorStop();
    }
    else if ( drt == 2)
    {
      //Serial.println(">>Bw ");
      motorBackward();
    }
    else {
      motorStop();
    }


    if (millis() - prev1 >= inter1)  {
      prev1 = millis();
      //      Serial.print("prev1= ");
      //      Serial.println(prev1);
      //      Serial.println(drt);
      if (drt == 0)
      {
        drt = 1;
      }
      else if ( drt == 1)
      {
        drt = 2;
      }
      else if ( drt == 2 )
      {
        drt = 0;
      }
      else {
        drt = 10;
      }

    }
  }
  else {
    motorStop();
  }
}


//*********void code*********/////

void motorStop() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void motorForward() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
}

void motorBackward() {
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}
