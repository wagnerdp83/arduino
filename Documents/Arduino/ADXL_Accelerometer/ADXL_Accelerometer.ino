  /*
    Arduino and ADXL345 Accelerometer Tutorial
     by Dejan, https://howtomechatronics.com
*/

#include <Wire.h>  // Wire library - used for I2C communication


int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs

float X_trigger = -0.4;

float Y_trigger = 0.4;

int stopBlink;

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
  //delay(100);

  // Pin LEDs
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  
  digitalWrite(8,HIGH); // Break light should always be ON and blinking

  //Read acceleromter data

  startRead();

  /*
  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print("   Ya= ");
  Serial.print(Y_out);
  Serial.print("   Za= ");
  Serial.println(Z_out);

  Serial.print("X Trigger ");
  Serial.print(X_trigger);
  Serial.print("  Y Trigger ");
  Serial.print(Y_trigger);
  */
  

}

void loop() {
    
    startRead();
   
 // Let the left arrow blinking
 if (X_out < X_trigger){

    X_trigger = X_out + 0.3;
  
    keepLeftBlink();
    /*
    Serial.print('\n');
    Serial.print('\r');
    Serial.print("============ X ==============");
    Serial.print(X_out);
    Serial.print('\n');
    Serial.print('\r');
    */
   
 } 
 
 if(Y_out > Y_trigger){X_trigger = -0.4; } 

    /*
    Serial.print("============ X Trigger ==============");
    Serial.print(X_trigger);
    Serial.print('\n');
    Serial.print('\r');
    */
}

int keepRightBlink(){
      digitalWrite(7, HIGH);
      delay(100);
      digitalWrite(7, LOW);
      delay(100);
}

int keepLeftBlink(){
      digitalWrite(9, HIGH);
      delay(100);
      digitalWrite(9, LOW);
      delay(100);

}
