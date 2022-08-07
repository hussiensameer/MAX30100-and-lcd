#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
  #include <LiquidCrystal_I2C.h>

#define REPORTING_PERIOD_MS     1000
 LiquidCrystal_I2C lcd(0x27, 16, 2);
PulseOximeter pox;
uint32_t tsLastReport = 0;
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    lcd.begin();   // LCD screen
  lcd.backlight();
lcd.clear(); // Clear LCD screen
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        lcd.setCursor(0, 1);
          lcd.print("Heart rate:");
        Serial.print(pox.getHeartRate());
          lcd.print(pox.getHeartRate());
        Serial.print(" SpO2:");
        lcd.setCursor(0, 0);
          lcd.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
          lcd.print(pox.getSpO2());
        Serial.println("  %");
   lcd.print("%");
        tsLastReport = millis();
              
              
    }      
}
