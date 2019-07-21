#include <Adafruit_NeoPixel.h>          // Library for NeoPixels

#define pinPix 3                       // Pin driving NeoPixel Ring or String
#define numPix 16                      // Number of NeoPixels in the Ring or Strip
#define flash 6                      //Number of times for eye to flash
#define R 255
#define G 39
#define B 0
#define steps 200
//Set up neopixel ring
Adafruit_NeoPixel myNeoPixels = Adafruit_NeoPixel(numPix, pinPix, NEO_GRB + NEO_KHZ800);


#define LEDPIN 13                      // Board LED pin
#define SENSORPIN 2                    // IR Sensor Pin
int sensorState = 0, lastState=0;   //sensor variables


void setup() {
  myNeoPixels.begin();   // Initialize the NeoPixel array in the Arduino's memory,
  myNeoPixels.show();    // turn all pixels off, and upload to ring or string

  pinMode(LEDPIN, OUTPUT);      
  pinMode(SENSORPIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //breathe(20, 100, 255,39,0);       // Pause; Number of steps; Full-on R,G,B values
  
  // read the state of the pushbutton value:
  sensorState = digitalRead(SENSORPIN);
  
  //sensor state low is beam broken
  if (sensorState == LOW) {     
    // turn LED on:
    digitalWrite(LEDPIN, HIGH);
    for (int i=0;i<flash;i++){
      for (int i=0;i<numPix;i++){
        myNeoPixels.setPixelColor(i,R,G,B);
      }
      myNeoPixels.show();
      delay(100);
      for (int i=0;i<numPix;i++){
        myNeoPixels.setPixelColor(i,0,0,0);
      }
      myNeoPixels.show();
      delay(100);
    }
    delay(3000);
    int tmpR, tmpG, tmpB;
    for (int s=1; s<=steps; s++) {
      tmpR = (R * s) / steps;     // Multiply first to avoid truncation errors  
      tmpG = 0.25*(G * s) / steps;
      //tmpB = (B * s) / steps;

      for (int i=0; i<numPix; i++) {
        myNeoPixels.setPixelColor(i,tmpR,tmpG,tmpB);
      }
      myNeoPixels.show();
      delay(30);
    }
    
     
  } 
  else {
    // turn LED on:
    digitalWrite(LEDPIN, LOW);
    for (int i=0;i<numPix;i++){
      myNeoPixels.setPixelColor(i,R,G,B);
    }
    myNeoPixels.show(); 
  }

}
