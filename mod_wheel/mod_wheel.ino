#include "USB.h"
#include "USBMIDI.h"


USBMIDI MIDI;
const int channel = 1;     // MIDI channel
const int sliderPin = 4;  // control number
const int configPin = 1;  // the cc adress of the mod wheel is ussually "1"


int mappedVal = 0;
int lastMappedVal = 0;

// made for esp32s2/s3. this specific projects requires "native USB", so if you plan to use otcher MCUs check that beforehand.
// Also, if you cant seem to be able to upload, try enetering dowload mode, by holding-down "boot" while restarting the esp32.
// Also Also, Make sure to have 'USB CDC on boot' ENABLED. otherwise midi-over-usb will not work whatsoever.

void setup() {

  USB.begin();
  delay(200);
  MIDI.begin();
}

void loop() {
  int sliderValue = analogRead(sliderPin);

  mappedVal = map(sliderValue, 0, 8200, 0, 128);
  // "0" and "8200" are edge values of my specific potentiometer.
  // use analog.Read() to know your minimum & maximum values.

  if( abs(lastMappedVal - mappedVal) > 2 ) { //decreases the number of "steps". Used to prevent the effect of noise so the esp32 only fires when changes are made.
    
    lastMappedVal = mappedVal;
      MIDI.controlChange(configPin, mappedVal, channel); 
  }
  delay(100);
}