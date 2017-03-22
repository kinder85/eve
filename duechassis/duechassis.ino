
int dir1PinA = 9;
int dir2PinA = 12;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed
int led = 13;
// Motor 2
int dir1PinB = 10;
int dir2PinB = 11;
int speedPinB = 6;
const char EOPmarker = '.'; 
char serialbuf[128];


#include <string.h> 
#define MAX_STRING_LEN 40 


void setup() {
  pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(speedPinB,OUTPUT);  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
void sharp_Right()
{
   analogWrite(speedPinA, 100);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 100);
digitalWrite(dir1PinB, HIGH);
digitalWrite(dir2PinB, LOW);
}

void sharp_Left()
{
   analogWrite(speedPinA, 100);//Sets speed variable via PWM 
digitalWrite(dir1PinA, HIGH);
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB, 100);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
}

void stop()                    //Stop
{
  analogWrite(speedPinA, 0);
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);    
analogWrite(speedPinB, 0);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);


}   
void advance(char a,char b,char z)          //Move forward
{
  analogWrite(speedPinA, a);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, b);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
//Serial.print("avan");
delay(z*100);

}  
void back_off (char a,char b,char z)          //Move backward
{
  analogWrite(speedPinA, a);
digitalWrite(dir1PinA, HIGH);
digitalWrite(dir2PinA, LOW);
  analogWrite(speedPinB, b);
digitalWrite(dir1PinB, HIGH);
digitalWrite(dir2PinB, LOW);;
//Serial.print("arr");
delay(z*100);

}
void turn_L (char a,char z)             //Turn Left
{
  analogWrite(speedPinA, 0);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, a);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
//Serial.print("droit");
delay(z*100);

}
void turn_R (char a,char z)             //Turn Right
{
  analogWrite(speedPinA, a);//Sets speed variable via PWM 
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 0);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
//Serial.print("droite");
delay(z*100);
}
void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available() > 0){
    
    static int bufpos = 0; //starts the buffer back at the first position in the incoming serial.read
      char inchar = Serial.read(); //assigns one byte (as serial.read()'s only input one byte at a time
      if (inchar != EOPmarker) { //if the incoming character is not the byte that is the incoming package ender
        serialbuf[bufpos] = inchar; //the buffer position in the array get assigned to the current read
        bufpos++; //once that has happend the buffer advances, doing this over and over again until the end of package marker is read.
       }
      else { //once the end of package marker has been read 
        serialbuf[bufpos] = 0; //restart the buff
        bufpos = 0; //restart the position of the buf
        int rx_byte = atoi(subStr(serialbuf, ",", 1));
        int y = atoi(subStr(serialbuf, ",", 2));
        int p = atoi(subStr(serialbuf, ",", 3));
        digitalWrite(led, HIGH);
        
  
 
 
 
 
 if (rx_byte == 1) {
      advance(y,y,p);
         

    }
    // if it's an L (ASCII 76) turn off the LED:
    if (rx_byte == 2) {
              back_off (y,y,p);
                  

    }//move back in max speed
  if (rx_byte == 4){
    turn_L(y,p);
    
    }
    if (rx_byte == 3){
      turn_R(y,p);
          
    }
    if (rx_byte == 5){
      stop();
    }

else{
  stop();
  digitalWrite(led, LOW);
}
}
}
}


char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[MAX_STRING_LEN];
  int i;
  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
}
 return sub;
}


