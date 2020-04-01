  /*
    Arduino and ADXL345 Accelerometer Tutorial
     by Dejan, https://howtomechatronics.com
*/

#include <Wire.h>  // Wire library - used for I2C communication

//Variables 
int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs

float right_trigger = -0.4; // Global VAR position to the right arrow

float left_trigger = 0.4; // Global VAR position to the left arrow

int ledStripe[] = {3,4,5,6,7,8,9,10,11,12,13};
int leftLed[] = {9,10,11,12,13}; //pins for left arrow 
int rightLed[] = {7,6,5,4,3}; //pins for right a dfrrow
int breakLight[] = {8}; //intialize ledw d (safety led)  

int pinCount = 11; // total number of pins  

unsigned long duration;

//Variables 

int startRead(){
  
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  X_out = X_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read()| Wire.read() << 8); // Y-axis value
  Y_out = Y_out/256;
  Z_out = ( Wire.read()| Wire.read() << 8); // Z-axis value
  Z_out = Z_out/256;
  
 }


int keepRightBlink(){

  for(int x = 0; x < 5; x++) {
      digitalWrite(rightLed[x], HIGH); 
      delay(10);                    
      digitalWrite(rightLed[x], LOW);  
      delay(50);                       
    }
}

int keepLeftBlink(){
  
  for(int x = 0; x < 5; x++) {
      digitalWrite(leftLed[x], HIGH); 
      delay(10);                     
      digitalWrite(leftLed[x], LOW); 
      delay(50);                     
    }
}

void keepSafeBreakLight(){
      digitalWrite(breakLight, HIGH); 
      delay(300); 
      digitalWrite(breakLight, LOW); 
      delay(300);
  }


void setup() {
  
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  Wire.begin(); // Initiate the Wire library
  
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();

  // LED ARROW ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Pin LEDs
  // Initialize the pinMode for all the LEDs  
  for(int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledStripe[thisPin], OUTPUT);
  } 

  
  pinMode(8,OUTPUT); // BReak Light Pin
  digitalWrite(8,HIGH); 

/*
    digitalWrite(breakLight, HIGH); 
    delay(300); 
    digitalWrite(breakLight, LOW); 
    delay(300);
 */

   duration = pulseIn(breakLight, HIGH);
   Serial.println(duration);
 

  
}

void loop() {
    //Start acceleromter data
    startRead();

    if (X_out < right_trigger){

    right_trigger = X_out + 0.3;
  
    keepLeftBlink();
   
    
    /* TESTERS
    Serial.print('\n');
    Serial.print('\r');
    Serial.print("============ X ==============");
    Serial.print(X_out);
    Serial.print('\n');
    Serial.print('\r');
    */
   
 } 


 if (X_out > left_trigger){

    left_trigger =  X_out - 0.3;
  
    keepRightBlink();
    
    /* TESTERS
    Serial.print('\n');
    Serial.print('\r');
    Serial.print("============ X ==============");
    Serial.print(X_out);
    Serial.print('\n');
    Serial.print('\r');
    */
   
 } 
 
 
  if(Y_out > left_trigger){ right_trigger = -0.4;} // Check the Y position and if is greater than 0.4 then reset the trigger to -0.4 

  if(Y_out > 0.4){left_trigger = 0.4;} // Check the Y position and if is lower than -0.4 then reset the trigger to 0.4
  
  /*
  Serial.print("Xa=     ");
  Serial.print(X_out);
  Serial.print("      Ya= ");
  Serial.print(Y_out);
  Serial.print("      Za= ");
  Serial.println(Z_out);
*/

  Serial.print("Right Trigger ");
  Serial.print(right_trigger);
  Serial.print("  Left Trigger ");
  Serial.print(left_trigger);
    

  Serial.print("============ X Trigger ==============");
  Serial.print(X_out);
  Serial.print('\n');
  Serial.print('\r');
 
    
  return ;

  
}
