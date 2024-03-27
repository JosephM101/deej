#include <Arduino.h>
#include "config.h" // Settings are stored here

// put function declarations here:
void updateSliderValues();
void sendSliderValues();
void printSliderValues();
void handlePortAutodetectRequests();

int analogSliderValues[NUM_SLIDERS];

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  handlePortAutodetectRequests();
  
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void handlePortAutodetectRequests() {
  #if ENABLE_PORT_AUTODETECT == true
    const String requestString = "DEEJ";
    const String responseString = "OK";

    if (Serial.available() > 0) {
      String received = Serial.readString();
      if (received == requestString) {
        Serial.write(responseString.c_str()); // Send the response string.
      }
    }
  #endif
}