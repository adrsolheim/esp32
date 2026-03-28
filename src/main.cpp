#include <Arduino.h>



// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(2, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second
digitalWrite(2, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(1000);   
}