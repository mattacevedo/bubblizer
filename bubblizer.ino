#include <HX711.h>
#include <LiquidCrystal_I2C.h>

// hardware
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows
HX711 scale;

// load cell pins
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

const float CALIBRATION_FACTOR = 202702.36; // you will need to customize this for your own load cell
const float OFFSET = 0.56; // and customize this one too
const float CANISTER_WEIGHT = 8.04; // this is the weight of an empty canister
const float CANISTER_CAPACITY = 5;
const float UPDATE_TRIGGER = 0.3;

float storedWeight = 1000; // setting top an arbitrarily huge value to ensure that scale display resets

const String STATUS_MESSAGE = "Status: ";
const String TANK_MESSAGE = "CO2 Tank at ";
const String WEIGHT_MESSAGE = "Remaining: ";


void setup() {

  // initialize LCD and turn on backlight
  lcd.init();
  lcd.backlight(); 

  // initialize the scale
  scale.set_scale(CALIBRATION_FACTOR);
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  // show initial message on LCD
  lcd.clear(); 
  
  lcd.setCursor(0, 0);
  lcd.print(" **Bubblizer 5000**"); 

  lcd.setCursor(0, 1);
  lcd.print("Counting bubbles..."); 

}

void loop() {
  
  // get average of last 20 readings
  float reading = scale.get_units(10);
  
  // determine weight of C02 remaining;
  float weightRemaining = reading - CANISTER_WEIGHT  - OFFSET;
  
  // get percentage of weight remaining (but as an int, not a decimal, hence the *100)
  float percentage = round( ((weightRemaining) / CANISTER_CAPACITY) * 100);

  /*
    The load cell reading might fluctuate a bit, 
    so to make sure it updates after only a meaningful change (e.g. .3 lbs),
    we compare the weight to the last stored weight.
    Then we store the new weight.
  */
  float weightChange = storedWeight-weightRemaining;
  if ( abs(weightChange) > UPDATE_TRIGGER ) {
      updateDisplay(percentage, weightRemaining);
      storedWeight = weightRemaining;
  }
}

// update display with new readings
void updateDisplay(int percentage, float weightRemaining) {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(" **Bubblizer 5000**");

  // shows the current status
  lcd.setCursor(0, 1);            
  if(percentage < 10 && percentage >= 6) {
    lcd.print("Status: REFILL SOON");
  } else if (percentage < 6) {
    lcd.print("Status: REFILL NOW");
  } else {
    lcd.print("Status: OK");
  }
  
  // shows the percenrage
  String tankMessage = "CO2 tank at ";
  tankMessage.concat(percentage);
  tankMessage.concat("%");
  lcd.setCursor(0, 2);
  lcd.print(tankMessage);

  // shows the weight remaining
  String weightMessage = String(weightRemaining, 2);
  weightMessage.concat("lbs remaining");
  lcd.setCursor(0, 3);
  lcd.print(weightMessage); 
}

