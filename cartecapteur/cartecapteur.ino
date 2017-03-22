// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

//#define TRIGGER_PIN  7 premier  // Arduino pin tied to trigger pin on the ultrasonic sensor.
// deuxieme#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int rx_byte = 0;
NewPing sonar(2, 3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonard(4, 5, MAX_DISTANCE);
NewPing sonarg(6, 7, MAX_DISTANCE);
int lineSensor1 = 0;
int lineSensor2 = 0;
int lineSensor3 = 0;
int lineSensor4 = 0;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
pinMode(lineSensor1, INPUT);
pinMode(lineSensor2, INPUT);
pinMode(lineSensor3, INPUT);
pinMode(lineSensor4, INPUT);
}


void son(){
  delay(500);
  int dist = sonar.ping_cm();
  int distd = sonard.ping_cm();
  int distg = sonarg.ping_cm();
  
  if (dist >= 40){
   Serial.println("ok");
   Serial.println(dist); 
   }
   else{
   if ( distd>>distg){
    Serial.println("droite");
    Serial.println(distd);
    }
   if (distg>>distd){
    Serial.println("gauche");
    Serial.println(distg);
    }
   }
  }




void line(){
 /* Read the Line Sensor if HIGH (BLack line) or LOW (White Line) */

lineSensor1 = digitalRead(8);
lineSensor2 = digitalRead(9);
lineSensor3 = digitalRead(10);
lineSensor4 = digitalRead(11);



/* Set conditions for Forward, Left and Right */

if (lineSensor4==HIGH && lineSensor3==HIGH && lineSensor2==LOW && lineSensor1==LOW)

{

// LEFT turn

Serial.print("gauche");

}

else if (lineSensor4==LOW && lineSensor3==LOW && lineSensor2==HIGH && lineSensor1==HIGH)

{

// RIGHT turn

Serial.print("droite");

}

else

{

// if (lineSensor4==LOW && lineSensor3==HIGH && lineSensor2==HIGH && lineSensor1==LOW) //



// FORWARD

Serial.print("ok");

} 
  }
void loop() {
if(Serial.available()){
    
        rx_byte = Serial.read();
        }

    if(rx_byte != -1)
    {
      switch(rx_byte)
      {
      case 'w':
       son();  

      case 'l':
      line();

      case 'd':
      break;
      
      }
    }
       
        
    
    }

