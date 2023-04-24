// TUTORIAL: WATER SENSOR, PHOTORESISTORS, AND MOTOR
// DELFINA
// This code should be able to operate the water sensor, photoresistors and the motor.

#include <Servo.h>  //Servo motor library
Servo servo_rightleft;     //Declare servo

#include <SPI.h>
#include <MFRC522.h> 

//Initialize variables for servo code
int ldrright = A0;         // right LDR pin
int ldrleft = A1;          // left LDR pin
int photoSensorValue = 0;
int numReadings = 4;       // number of readings to average

int topl = 0;
int topr = 0;

int motorPin = 8;
int servo_threshold = 3;                  //measurement sensitivity
int currentPos = servo_rightleft.read();  // Get the current position of the servo
int flat_pos = 100;                       // Set the desired flat position

int waterSensorPin = A2;   //analog pin for water sensor

//int NIGHTledPin = 4;
//#define LED_BUILTIN 12      // Set LED pin

//RFID pins
//#define RST_PIN 9          // Set RST Pin  
//#define SS_PIN 10          // Set SS Pin

//MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Define the threshold values for triggering the motor action and adjusting the motor position
int rainThreshold = 500; //change the threshold value 
int sunThreshold = 30;   //change the threshold value
int nightThreshold = 30; //change the night threshold value

//float batteryVoltage = analogRead(A4) * 5.0 / 1023.0;
//float solarVoltage = analogRead(A5) * 5.0 / 1023.0;

void setup() {
 // {
 // pinMode(blueledPin, OUTPUT);
 // pinMode(buttonPin, INPUT_PULLUP); 
 // }

  pinMode(motorPin, OUTPUT);           // Initialize the digital pins for the motor

  //pinMode(NIGHTledPin, OUTPUT);
  //pinMode(LED_BUILTIN, OUTPUT);       // initialize digital pin output

  Serial.begin(9600);                 // Set up the serial communication for debugging, opens serial port, sets data rate to 9600 bps

/*  while (!Serial);                     // If no serial port is opened, do nothing (for ATMEGA32U4 Arduinos)
    SPI.begin();                       // Init SPI bus
    mfrc522.PCD_Init();                // Init MFRC522
    delay(4);                          // Optional delay
    mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
*/
  Serial.println("CLEARDATA");         //clear all data that’s been place in already
  Serial.print("servo_threshold: "); 
  Serial.print(servo_threshold);       //print servo Threshold
  Serial.print(" | rainThreshold: ");
  Serial.print(rainThreshold);         //print Rain Threshold
  Serial.print(" | sunThreshold: ");
  Serial.print(sunThreshold);          //print Sunlight Threshold
  Serial.print(" | nightThreshold: ");
  Serial.println(nightThreshold);      //print Sunlight Threshold
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  servo_rightleft.attach(motorPin);   //Servo motor right-left movement
  
  // Reset the servo position
  for (int pos = currentPos; pos <= flat_pos; pos++) {
      servo_rightleft.write(pos);         // Move the servo to the next position
      delay(200);                         // Adjust this delay to make the movement slower or faster
  }
}
  void automaticsolartracker() {
    //capturing analog values of each LDR
    topr = analogRead(ldrright);      //capturing analog value of right LDR
    topl = analogRead(ldrleft);       //capturing analog value of left LDR
  
    //Get the difference
    int diffazi = topl - topr;        //Get the difference in average between the right and left LDRs

    //left-right movement of solar tracker
    if (abs(diffazi) >= servo_threshold) { //Change position only if light difference is bigger then the threshold_value
      int targetPos = 0;
      if (diffazi > 0) {
        targetPos = -45;
      }
      else {
        targetPos = 45;
      }
  
      int currentPos = servo_rightleft.read();
      int increment = (targetPos - currentPos) / 100;
      if (increment == 0) {
        increment = 1;
      }      
      for (int i = 0; i < 2; i++) {    //movement graduation
        currentPos += increment;
        servo_rightleft.write(currentPos);  // Move the servo to the next position
      delay(200);                           // Adjust this delay to make the movement slower or faster
      }
    }

  int currentPos = servo_rightleft.read();
  topr = analogRead(ldrright);      //capturing analog value of right LDR
  topl = analogRead(ldrleft);       //capturing analog value of left LDR

  // Print the sensor values to the serial monitor for debugging
  
  Serial.print(" | topr: ");
  Serial.print(topr);
  Serial.print(" | topl: ");
  Serial.print(topl);
  Serial.print(" | currentPos: ");
  Serial.println(currentPos);
  }

void loop() {

 {
 /*   //capturing analog values of each LDR
    topr = analogRead(ldrright);      //capturing analog value of right LDR
    topl = analogRead(ldrleft);       //capturing analog value of left LDR
      int reading = topr + topl;

    if (photoSensorValue <= nightThreshold) { 
      digitalWrite(NIGHTledPin, HIGH);
    } else {
      digitalWrite(NIGHTledPin, LOW); 
      }
  */}

{
  // if button is pushed, turn LED on for 2 minutes, then turn off
 // if (digitalRead(buttonPin) == HIGH);
  //{
 //   digitalWrite(blueledPin, HIGH);
  //  delay(5000); 
  //  digitalWrite(blueledPin, LOW); 
 // }
}

  int waterSensorValue = analogRead(waterSensorPin);  // Read the value from the water sensor and photosensor
  /*
  int reading = 0;
    for (int i = 0; i < numReadings; i++) {         // read the analog value from the two LDRs and add them up
      reading += analogRead(ldrright);
      reading += analogRead(ldrleft);
    }    
    photoSensorValue = reading / (numReadings * 2); // calculate the average
  
  int currentPos = servo_rightleft.read();
  topr = analogRead(ldrright);      //capturing analog value of right LDR
  topl = analogRead(ldrleft);       //capturing analog value of left LDR
*/
  // Print the sensor values to the serial monitor for debugging
  Serial.print("Water Sensor: ");
  Serial.print(waterSensorValue);
  Serial.print(" | Photo Sensor average: ");
  Serial.print(photoSensorValue);
  Serial.print(" | topr: ");
  Serial.print(topr);
  Serial.print(" | topl: ");
  Serial.print(topl);
  Serial.print(" | currentPos: ");
  Serial.print (currentPos);
  /*Serial.print(" | solarVoltage: ");
  Serial.print (solarVoltage);
  Serial.print(" | batteryVoltage: ");
  Serial.println (batteryVoltage);

  // Check if solar voltage is greater than battery voltage
  if (solarVoltage > batteryVoltage) {
    Serial.println("Charging battery"); // Send a message to the software serial port
    // Charging the battery using the solar charge controller
  } else {
    Serial.println("Running on battery"); // Send a message to the software serial port
    // Running the Arduino on battery power
  }
*/
  delay (5000);

  if (waterSensorValue > rainThreshold) { // Check if it's raining based on the water sensor value
    
    digitalWrite(motorPin, HIGH);         // Trigger the motor action by setting the motor pin to high

    for (int pos = currentPos; pos <= flat_pos; pos++) {
      servo_rightleft.write(pos);         // Move the servo to the next position
      delay(10);                          // Adjust this delay to make the movement slower or faster
    }
    
  } /*
  // Check if it's not raining and the sun intensity is high based on the photosensor value
  else if (waterSensorValue <= rainThreshold && photoSensorValue > sunThreshold) {
  //adding panel code
    {       // Read the Battery voltage from the boost converter
    if (batteryVoltage < 12.0) {        // If the voltage is less than 12V, turn off the motor
      digitalWrite(motorPin, LOW);
      }
    else {                            // If the voltage is greater than or equal to 12V, turn on the motor
      digitalWrite(motorPin, HIGH);   // Adjust the roof position to create shade by setting the motor pin to high
      automaticsolartracker(); // Call automatic solar tracker function
    }
  }
  }
  else {                         // Stop the motor action by setting the motor pin to low
    digitalWrite(motorPin, LOW);    
  }
    delay(200); // Wait for a short delay before repeating the loop
*/
  {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
 /* if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
    }

  if ( ! mfrc522.PICC_ReadCardSerial()) {  // Select one of the cards
    return;
    }

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(8000);                       // turn on for 8 seconds
  digitalWrite(LED_BUILTIN, LOW);    // turn off LED
  delay(1000);                       // wait for a second

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
 */ }
}