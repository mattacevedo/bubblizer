# Bubblizer 5000
I like carbonated water. A lot. For home carbonated water production, I turned a Sodastream into the **Bubblizer 5000**, which uses a 5lb canister for cheap, plentifyl CO2 and an Arudino-based setup to monitor remaining CO2. 

You can do it too. Here's what's needed.

* Sodastream machine. I use the Fizzi (the plug-in electronic one), but any standard machine will do. You don't need the Sodastream brand CO2 cartridge because they're too expensive and too inconvenient to re-fill.
* Standard 5lb CO2 canister, which I refill at my local gas store.
* Sodastream-to-standard-canister hose adapter. Fairly widely available online.
* Arduino Uno
* Dismantled kitchen scale for the housing and load censor. I used the [Ozeri Pronto Digital Multifunction Kitchen and Food Scale](https://www.amazon.com/dp/B004164SRA)
* HX711 amplifier board
* 20x4 I2C LCD display
* Housing for the Uno and the display. [I got one from Etsy that I like a lot.](https://www.etsy.com/listing/1437252583/arduino-unomega-4x20lcd-enclosure)

## Not a Tutorial, But a Starting Point
1. Connect the CO2 canister to the SodaStream machine with the hose adapter.
2. Take apart the kitchen scale to access the load censor. [Connect it to the HX711, connect that to Uno, and calibrate.](https://randomnerdtutorials.com/arduino-load-cell-hx711/)
3. [Connect the display](https://arduinogetstarted.com/tutorials/arduino-lcd-20x4) and build everything in the housing.
4. Load the code from INO file from this respository.
5. Put your CO2 canister on the scale.
6. Drink bubble water and monitor your usage
