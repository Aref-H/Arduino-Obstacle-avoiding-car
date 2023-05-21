/*
* Author : AREF HEYDARI 
* Date : 1401/10/10
* Date : 31/12/2022
* This code has been written for a obstacle avoidance machine with three ultrasonic sensors.
*/
#include <Servo.h>      //including servo library
#include <NewPing.h>      //including newping library

#define echo_pin2 6    //Echo pin     //                         .                      ...part machine
#define trig_pin2 7 //Trigger pin     //                         .                      ...part machine
#define echo_pin3 2    //Echo pin     //                         .                      ...part machine
#define trig_pin3 3 //Trigger pin     //                         .                      ...part machine
#define echo_pin4 12    //Echo pin    //                         .                      ...part machine
#define trig_pin4 13 //Trigger pin    //                         .                      ...part machine

#define maximum_distance 200      //defining number 200 into the name maximum_distance  ...part machine


boolean goesForward = false;      //making a boolean with the name of goesForward that contains false  ...part machine

NewPing sonar(trig_pin2, echo_pin2, maximum_distance); //sensor function for detecting obstacle when in mode machine  ...part machine      
NewPing sonar2(trig_pin3, echo_pin3, maximum_distance); //sensor function for detecting obstacle when in mode machine  ...part machine
NewPing sonar3(trig_pin4, echo_pin4, maximum_distance); //sensor function for detecting obstacle when in mode machine  ...part machine

Servo servo_motor; //our servo name  ...part machine

int distance = 100;     //making a integer with the name of distance that contains number 100  ...part machine
int distancee = 100;      //making a integer with the name of distancee that contains number 100  ...part machine
int distanceee = 100;     //making a integer with the name of distanceee that contains number 100  ...part machine

//our L298N control pins
const int LeftMotorForward = A1;      //using const to prevent programmer from modifying it  ...part machine
const int LeftMotorBackward = A2;     //                                .                            
const int RightMotorForward = A3;     //                                .
const int RightMotorBackward = A4;    //                                .

  
void setup() { // put your setup code here, to run once
    
    pinMode(RightMotorForward, OUTPUT);     //make pin A3 with name RightMotorForward output  ...part machine
    pinMode(LeftMotorForward, OUTPUT);      //make pin A1 with name LeftMotorForward output  ...part machine
    pinMode(LeftMotorBackward, OUTPUT);     //make pin A2 with name LeftMotorBackward output  ...part machine
    pinMode(RightMotorBackward, OUTPUT);    //make pin A4 with name RightMotorBackward output  ...part machine

    servo_motor.attach(10);     // declare Servo Motor as output, servo pwm == pin 10  ...part machine

    servo_motor.write(87);      //turne servo to the dgree 87  ...part machine
    delay(2000);                //2 second delay
    distance = readPing();      //put resulte of readPing function into distance, obtacle detection first sensor  ...part machine
    
    distancee = readPing2();    //put resulte of readPing2 function into distancee, obtacle detection second sensor  ...part machine
    
    distanceee = readPing3();   //put resulte of readPing3 function into distanceee, obtacle detection third sensor  ...part machine
    delay(100);
    distance = readPing();      //                                                 .
    
    distancee = readPing2();    //                                                 .
    
    distanceee = readPing3();   //                                                 .
    delay(100);
    distance = readPing();      //                                                 .
    
    distancee = readPing2();    //                                                 .
    
    distanceee = readPing3();   //                                                 .
    delay(100);
    distance = readPing();      //                                                 . 
    
    distancee = readPing2();    //                                                 .
    
    distanceee = readPing3();   //                                                 .
    delay(100); 
}


void loop() { // put your setup code here, to run continusly
    
    int distanceRight = 0;  //make an integer with the name distanceRight and put 0 init  ...part machine
    int distanceLeft = 0;   //make an integer with the name distanceLeft and put 0 init   ...part machine
    delay(50);

    if ((distance <= 35) || ((distancee <= 21) || (distanceee <= 21))) {      /*if obstacle was in the range of 35cm of first sensor or 21cm of 
                                                                                sensor2 or sensor3, condition is true*/ 
      
      moveStop();                                                             //call moveStop function  ...part machine
      delay(300);                                                             //delay 300ms
      moveBackward();                                                         //call movebackward function  ...part machine
      delay(320);
      moveStop();                                                             //call moveStop function  ...part machine
      delay(300);
      distanceRight = lookRight();      //distanceRight == function lookRight result  ...part machine
      delay(300);
      distanceLeft = lookLeft();        //distanceLeft == function lookLeft result  ...part machine
      delay(300);

      if (distanceRight >= distanceLeft) {      //if there was no obstacle in the Right side, turn right  ...part machine
        turnRight();      //call function turnRight  ...part machine
        moveStop();       //call function moveStop  ...part machine
      }
      else {              //reverse of above part  ...part machine
        turnLeft();       //call function turnLeft  ...part machine
        moveStop();       //call function moveStop  ...part machine
      }
    }
    else {              //reverse of if statment with 35cm or 21cm condition  ...part machine
      moveForward();      //call function moveForward  ...part machine
    }
    distance = readPing();      //again start detecting obstacle with sensor1  ...part machine
    distancee = readPing2();    //again start detecting obstacle with sensor2  ...part machine
    distanceee = readPing3();   //again start detecting obstacle with sensor3  ...part machine
}


int lookRight() {     //lookRight function, machine will look right to find way  ...part machine
  servo_motor.write(17);    //servo will go to the degree 17
  delay(500);     //0.5 second delay
  int distance = readPing();      //integer distance equal to result of function readPing
  delay(100);     //delay
  servo_motor.write(87);      //servo goes back to 87 degree
  return distance;      //function will return distance as result
}


int lookLeft() {      //same as above function for looking left side  ...part machine
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(87);
  return distance;
  delay(100);
}


int readPing() {      /*function that calculate obstacle distance and return it in centimetre, first sensor  ...part machine
                        in this function we use syntax that NewPing library provides for calculating distance in meter, centimeter and inch
                        (we are using (cm) in this part)*/
  delay(55);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}


int readPing2() {     //same as above function for second sensor  ...part machine
  delay(55);
  int cm = sonar2.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}


int readPing3() {     //same as above function for third sensor  ...part machine
  delay(55);
  int cm = sonar3.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}


void moveStop() {     //function that make all wheels stop  ...part machine 

  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}


void moveForward() {      //function that command machine to move forward  ...part machine

  if (!goesForward) {     //when goesForward was made, it was a boolean that contained false. now it a condition that make it true 

    goesForward = true;

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);

    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
  }
}


void moveBackward() {     //when there is obstacle machine will stop and this is function that make it to move backward before looking left and right

  goesForward = false;      //when this function is called, goesForward will became false

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

}


void turnRight() {      //this function will make machine to turn right and after 400(ms), start to goes forward  ...part machine

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);

  delay(400);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

}


void turnLeft() {     //this function will make machine to turn left and after 400(ms), start to goes forward  ...part machine

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(400);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
  
