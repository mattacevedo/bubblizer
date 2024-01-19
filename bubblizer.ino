

#include <HX711.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

HX711 scale;
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const float CALIBRATION_FACTOR = 202702.36; // update this
const float CANISTER_WEIGHT = 8.04;
const float CANISTER_CAPACITY = 5;
const float OFFSET = 0.56;

float storedWeight = 1000; // setting top an arbitrarily huge value to ensure that scale display resets

const String STATUS_MESSAGE = "Status: ";
const String TANK_MESSAGE = "CO2 Tank at ";
const String WEIGHT_MESSAGE = "Remaining: ";




void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  
  scale.set_scale(CALIBRATION_FACTOR);
  
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  

  lcd.clear(); 
  
  lcd.setCursor(0, 0);
  lcd.print(" **Bubblizer 5000**"); 

  lcd.setCursor(0, 1);
  lcd.print("Counting bubbles..."); 
  

}

void loop() {
  
  // get average of last 20 readings
  float reading = scale.get_units(10);
  
  // determine weight of C0 remaining;
  float weightRemaining = reading - CANISTER_WEIGHT  - OFFSET;
  
  // get percentage of weight remaining (but as an int, not a decimal, hence the *100)
  float percentage = round( ((weightRemaining) / CANISTER_CAPACITY) * 100);


  float weightChange = storedWeight-weightRemaining;
  if ( abs(weightChange) > 0.3 ) {
      updateDisplay(percentage, weightRemaining);
      storedWeight = weightRemaining;
      Serial.print("weight change detected");

  }
}


void updateDisplay(int percentage, float weightRemaining) {


  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(" **Bubblizer 5000**");

  lcd.setCursor(0, 1);            
  if(percentage < 10 && percentage >= 6) {
    lcd.print("Status: REFILL SOON");
  } else if (percentage < 6) {
    lcd.print("Status: REFILL NOW");
  } else {
    lcd.print("Status: OK");
  }
  

  String tankMessage = "CO2 tank at ";
  tankMessage.concat(percentage);
  tankMessage.concat("%");
  lcd.setCursor(0, 2);
  lcd.print(tankMessage);

  String weightMessage = String(weightRemaining, 2);
  weightMessage.concat("lbs remaining");
  lcd.setCursor(0, 3);
  lcd.print(weightMessage); 
}

