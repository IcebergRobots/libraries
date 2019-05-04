#include <Arduino.h>
#include <WSWire.h>
#include <HMC6352.h>

// void constructor
HMC6352::HMC6352()
{
  address_ = 0x21;	// this is 0x42 shifted once to the right
};

// user-specified address
HMC6352::HMC6352(int address)
{
  address_ = address;
};

float HMC6352::getHeading()
{
  Wire.beginTransmission(address_);
  Wire.write(c_getDataStandby_);
  Wire.endTransmission();

  delay(7);
  
  return(requestData());

}

float HMC6352::requestData(){
  
  Wire.requestFrom(address_, 2);
  while(Wire.available() == 0){
  }
  byte highByte	= Wire.read();
  byte lowByte	= Wire.read();
  return((highByte*256+lowByte)/10.0);
}

int HMC6352::getOperationalMode()
{
  Wire.beginTransmission(address_);
  Wire.write(c_readFromRAM_);
  Wire.write(c_operationalModeAddressRAM_);
  Wire.endTransmission();

  delay(1);

  Wire.requestFrom(address_, 1);

  int modeValue = Wire.read();

  return(modeValue&3);
}

int HMC6352::getOutputMode()
{
  Wire.beginTransmission(address_);
  Wire.write(c_readFromRAM_);
  Wire.write(c_outputModeAddressRAM_);
  Wire.endTransmission();

  delay(1);

  Wire.requestFrom(address_, 1);

  int modeValue = Wire.read();

  return(modeValue&7);
}

void HMC6352::setOutputMode(const int& mode)
{
  int setMode = mode;
  // sanity check on the input
  if (setMode > 4 || setMode < 0) 
  {
    setMode = 0;	// fall-back to heading measurements
  }
  Wire.beginTransmission(address_);
  Wire.write(c_writeToRAM_);				// command
  Wire.write(c_outputModeAddressRAM_);	// argument 1 - address
  Wire.write(setMode);					// argument 2 - data
  Wire.endTransmission();

  delay(1);
}

void HMC6352::setOperationalMode(const int& mode){
  int setMode = mode;
  // sanity check on the input
  if (setMode > 115 || setMode < 0) 
  {
    setMode = 0;	// fall-back to heading measurements
  }
  Wire.beginTransmission(address_);
  Wire.write(c_writeToRAM_);				// command
  Wire.write(c_operationalModeAddressRAM_);	// argument 1 - address
  Wire.write(setMode);					// argument 2 - data
  Wire.endTransmission();

  delay(1); 
}

void HMC6352::calibration(void)
{
  //start calibration
  Wire.beginTransmission(address_);
  Wire.write(c_startCalibration_);
  Wire.endTransmission();

  //Rotate the module several times during this period.
  delay(30000);

  //end calibration
  Wire.beginTransmission(address_);
  Wire.write(c_endCalibration_);
  Wire.endTransmission();
  return;
}