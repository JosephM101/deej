#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// Slider configuration
const int NUM_SLIDERS = 4;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3};

// ENABLE_PORT_AUTODETECT
// When enabled, the board will listen for "deej", and will respond with "ok". 
// This will allow the deej client to autodetect the serial port if it were to somehow change. 
// To enable in the client app, use 'auto' instead of specifying a COM port.
#define ENABLE_PORT_AUTODETECT true

#endif