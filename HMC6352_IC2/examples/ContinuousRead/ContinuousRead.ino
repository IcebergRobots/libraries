#include <Wire.h>
#include "HMC6352.h"

HMC6352 myCompass;
float heading;

void setup()
{
  Serial.begin(9600);
  delay(10);
  Wire.begin();
  delay(10);

  myCompass.setOutputMode(0);
  //Continuous Mode, Periodic on ,Rate 20Hz
  myCompass.setOperationalMode(0x72);
  Serial.print("Output mode: ");
  Serial.println(myCompass.getOutputMode());
}

void loop()
{
  heading = myCompass.requestData();
  Serial.println(heading);
  delay(100);
}