#include "USB.h"
#include "USBMIDI.h"


USBMIDI MIDI;
const int channel = 1;     // MIDI channel
const int sliderPin = 4;  // control number
const int configPin = 1;  // Modulation wheel in midi usually uses address "1"


int mappedVal = 0;
int lastMappedVal = 0;

// made for esp32s2/s3. this specific eprojects requires "native USB", so if you plan to use otcher MCUs check that beforehand.
// Also, if you cant seem to be able to upload, try enetering dowload mode, by holding-down "boot" while restarting the esp32.
// Also Also, Make sure to have 'USB CDC on boot' enabled

void setup() {

  USB.begin();
  delay(500);
  MIDI.begin();
  delay(500);
  delay(1000);
}

void loop() {
  int sliderValue = analogRead(sliderPin);
  

  mappedVal = map(sliderValue, 0, 8200, 0, 128);
  // The first "0" and "8200" depend on your potentiometer.
  // use analog.Read() to know your minimum & maximum values.


  if( abs(lastMappedVal - mappedVal) > 1 ) {
    
    lastMappedVal = mappedVal;
      MIDI.controlChange(configPin, mappedVal, channel); 
  }
  delay(50);
}