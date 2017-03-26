#include "LedControl.h"
#include <ShiftRegister74HC595.h>
#include <Scheduler.h>

 
int rx_byte = 0;
LedControl lc=LedControl(44,48,46,2);  // Pins: DIN,CLK,CS, # of Display connected
ShiftRegister74HC595 sr (1, 10, 8, 9);
int buttonState = 0;
int micState = 0;
const int buttonPin = 24;
const int micPin = 22;
const int ledPin =  5;


// Put values in arrays

byte eyeOff[] =

{

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000,

   B00000000

};



byte eyeOpened[] =

{

   B00111100,

   B01100110,

   B01000010,

   B11011011,

   B11011011,

   B01000010,

   B01100110,

   B00111100

};

byte pligauche[]
{
  B00000100,
  B00001010,
  B00010010,
  B00110011,
  B11110011,
  B01100110,
  B00111100 
};

byte plidroit[]
{
  B00100000,
  B01010000,
  B01001000,
  B11001100,
  B11001111,
  B01000010,
  B01100010,
  B00111100
};

byte eyeClosed[] =

{

  B00011000,

  B00011000,

  B00111100,

  B00111100,

  B00111100,

  B00111100,

  B00011000,

  B00011000

};

 

byte eyeToLeft[] =

{

   B00111100,

   B01100110,

   B01000010,

   B11000011,

   B11011011,

   B01011010,

   B01100110,

   B00111100

};

 

byte eyeToRight[] =

{

   B00111100,

   B01100110,

   B01011010,

   B11011011,

   B11000011,

   B01000010,

   B01100110,

   B00111100

};



byte love[] =

{

   B00001100,

   B00011110,

   B00111110,

   B01111100,

   B01111100,

   B00111110,

   B00011110,

   B00001100

};



byte happy[] =

{

   B00111100,

   B01000010,

   B10010101,

   B10100001,

   B10100001,

   B10010101,

   B01000010,

   B00111100

};



byte eye2Opened[] =

{

   B00111100,

   B01111110,

   B11111111,

   B11100111,

   B11100111,

   B11111111,

   B01111110,

   B00111100

};

 

byte eye2Closed[] =

{

  B00011000,

  B00011000,

  B00111100,

  B00111100,

  B00111100,

  B00111100,

  B00011000,

  B00011000

};

byte quest[]
{
  B00000000,
  B00011000,
  B00100100,
  B00001000,
  B00001000,
  B00000000,
  B00001000 
};

byte eye2ToUpperLeft[] =

{

   B00111100,

   B01111110,

   B11111111,

   B11111111,

   B11111111,

   B11110011,

   B01110010,

   B00111100

};

 

byte eye2ToRight[] =

{

   B00111100,

   B01100110,

   B11100111,

   B11111111,

   B11111111,

   B11111111,

   B01111110,

   B00111100

};

 

void setup()

{
  Serial.begin(115200);
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,1);  // Set intensity levels
  lc.setIntensity(1,1);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  pinMode(buttonPin, INPUT);
pinMode(micPin, INPUT);
pinMode(ledPin, OUTPUT);
Scheduler.startLoop(loop2);
}

 

void SetLeftEye(byte* mood)

{

  for (int i = 0; i < 8; i++)  

  {
    lc.setRow(1,i,mood[i]);
  }

}



void SetRightEye(byte* mood)

{

  for (int i = 0; i < 8; i++)

  {

    lc.setRow(0,i,mood[i]);

  }

}

void normal(){
  SetLeftEye(eyeOpened);

    SetRightEye(eyeOpened);

    delay(2000);

    SetLeftEye(eyeClosed);

    SetRightEye(eyeClosed);

    delay(400);

    

    

    
  } 
void lov()
{
  SetLeftEye(love);
  SetRightEye(love);
    delay(2000);
    
}

void colere()
{
  SetLeftEye(plidroit);
  SetRightEye(pligauche);
    delay(2000);
    
}
void triste()
{
  SetLeftEye(pligauche);
  SetRightEye(plidroit);
    delay(2000);
    
}
void joix()
{
  SetLeftEye(happy);
  SetRightEye(happy);
    delay(2000);
    
}

void question()
{
  SetLeftEye(quest);
  SetRightEye(quest);
    delay(2000);
    
}
void check(){
  SetLeftEye(eyeToRight);

    SetRightEye(eyeToRight);

    delay(500);
    SetLeftEye(eyeToLeft);

    SetRightEye(eyeToLeft);

    delay(500);
}

void exa(){
 

    SetLeftEye(eye2ToUpperLeft);
    SetRightEye(eye2ToUpperLeft);
    delay(1000);
    SetLeftEye(eyeOff);
    SetRightEye(eyeOff);
    delay(1000);

   
}
void loop2() {
  // put your main code here, to run repeatedly:
 buttonState = digitalRead(buttonPin);
 
  
    micState = digitalRead(micPin);
    if (buttonState == HIGH) {
      if (micState == LOW) {
      for (int i = 0; i < 8; i++) {
    
        sr.set(i, HIGH); // set single pin HIGH
        delay(50); 
    
        }
       for (int i = 8; i > 0; i--) {
    
        sr.set(i, LOW); // set single pin HIGH
        delay(50); 
    
        }
    }
    else{
        sr.setAllLow();
        }
    }
    delay(1);   
}
void loop()

{
 
if(Serial.available() > -1){
    
    
int rx_byte = Serial.read();  
 
 
 
 
 if (rx_byte == 'l') {
      lov();
         

    }
    
    if (rx_byte == 'e') {
      exa();
                  

    }
   if (rx_byte == 'c') {
      check();
                  

    }
    if (rx_byte == 'r') {
      colere();
                  

    }
    if (rx_byte == 'j') {
      joix();
                  

    }
    if (rx_byte == 't') {
      triste();
                  

    }
    if (rx_byte == 'q') {
      question();
                  

    }

else{
  normal();
}
}
 yield();  
}
