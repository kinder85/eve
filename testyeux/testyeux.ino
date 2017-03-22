#include "LedControl.h"

 
int rx_byte = 0;
LedControl lc=LedControl(12,11,10,2);  // Pins: DIN,CLK,CS, # of Display connected



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
void check(){
  SetLeftEye(eyeToRight);

    SetRightEye(eyeToRight);

    delay(500);
    SetLeftEye(eyeToLeft);

    SetRightEye(eyeToLeft);

    delay(500);
}
void checkgauche(){
  
}
void exa(){
 

    SetLeftEye(eye2ToUpperLeft);

    SetRightEye(eye2ToUpperLeft);

    delay(2000);
    SetLeftEye(eyeOff);

    SetRightEye(eyeOff);

    delay(1000);

   
}
void loop()

{
 
if(Serial.available() > -1){
    
    
int rx_byte = Serial.read();  
 
 
 
 
 if (rx_byte == 'l') {
      lov();
         

    }
    // if it's an L (ASCII 76) turn off the LED:
    if (rx_byte == 'e') {
      exa();
                  

    }
   if (rx_byte == 'c') {
      check();
                  

    }//move back in max speed
  

else{
  normal();
}
}
   
}
