// TUTORIAL: DAYTIME NIGHTTIME LIGHT
// KATHLEEN SCOPIS

// The following code uses photoresistors to turn and LED light on or off 
// depending on the outside brightness. 

int photoSensorValue = 0;

int ldrright = A0;    // right LDR pin
int ldrleft = A1;     // left LDR pin

int topl = 0;
int topr = 0;

int NIGHTledPin = 7;

int sunThreshold = 20;  //change the daylight threshold value
int nightThreshold = 10; //change the night threshold value

void setup() {

  pinMode(NIGHTledPin, OUTPUT);

  Serial.begin(9600);        // Set up the serial communication for debugging, opens serial port, sets data rate to 9600 bps

  Serial.println("CLEARDATA"); //clear all data that’s been place in already
  Serial.print(" | sunThreshold: ");
  Serial.println(sunThreshold);  //print Sunlight Threshold
  Serial.print(" | nightThreshold: ");
  Serial.println(nightThreshold);  //print Sunlight Threshold
  
}


void loop() {
    //capturing analog values of each LDR
    topr = analogRead(ldrright);      //capturing analog value of right LDR
    topl = analogRead(ldrleft);       //capturing analog value of left LDR
    int numReadings = 3;
    int reading = topr + topl;
    photoSensorValue = reading / (numReadings * 2); // calculate the average

    //Get the difference

    //left-right movement of solar tracker
    if (abs(photoSensorValue) <= nightThreshold) { 
           digitalWrite(NIGHTledPin, HIGH);
    }
      else
      {
    digitalWrite(NIGHTledPin, LOW); 
      }
}