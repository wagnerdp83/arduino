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
 


void setup() {
  
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  Wire.begin(); // Initiate the Wire library
  
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();

  // Pin LEDs
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  
  digitalWrite(8,HIGH); // Break light should always be ON and blinking

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
  
  /* TESTER
  Serial.print("Xa=     ");
  Serial.print(X_out);
  Serial.print("      Ya= ");
  Serial.print(Y_out);
  Serial.print("      Za= ");
  Serial.println(Z_out);

  Serial.print("Right Trigger ");
  Serial.print(right_trigger);
  Serial.print("  Left Trigger ");
  Serial.print(left_trigger);
    

  Serial.print("============ X Trigger ==============");
  Serial.print(X_trigger);
  Serial.print('\n');
  Serial.print('\r');
  */
    
  return ;
  
}

int keepRightBlink(){
      digitalWrite(7, HIGH);
      delay(99);
      
      digitalWrite(7, LOW);
      delay(100);

}

int keepLeftBlink(){
      digitalWrite(9, HIGH);
      delay(100);
      digitalWrite(9, LOW);
      delay(100);

}
