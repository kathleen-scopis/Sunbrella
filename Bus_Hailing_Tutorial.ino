// Tutorial: USING AN RFID TO HAIL THE BUS
// KATHLEEN SCOPIS

// Using an RC522 RFID to activate an LCD screen

// USE 1K RESISTOR

// initialize libraries
#include <SPI.h>
#include <MFRC522.h> 
#include <LiquidCrystal.h>

// initialize pins
#define RST_PIN         9          // Set RST Pin
#define SDA_PIN          10         // Set SS Pin

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E, DB4, DB5, DB6, DB7

MFRC522 mfrc522(SDA_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  // initialize digital pin output
 // pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);   // serial communications with the PC
  while (!Serial);    // If no serial port is opened, do nothing (for ATMEGA32U4 Arduinos)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  lcd.begin(16, 2);
}

void loop() {
  
  // If no new card is present, reset the loop
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }


  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  // print message onto LCD
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bus Hailed... 3 min away...      ");
    delay(700);
    Serial.print("LCD is working");
  }

  lcd.setCursor(0, 1);
  
  // scroll the display four positions to the left every 500ms
  for (int i = 0; i < 23; i++) {
    lcd.scrollDisplayLeft();
    delay(450);
  }
  delay(400);

 // Dump debug info about the card; PICC_HaltA() is automatically called
mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
 
}

