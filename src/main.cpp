// verändert nach: https://www.arduino.cc/en/tutorial/switch
/* switch
 *
 * Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 * press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 * a minimum delay between toggles to debounce the circuit (i.e. to ignore
 * noise).
 *
 * David A. Mellis
 * 21 November 2006
 */

#include <Arduino.h>

int ledPin = LED_BUILTIN;  // On-Board LED for status
int buttonPin = 6;         // manual on/off switch for Relay
int relayPin = 13;         // Relay for TIG switching

int state = LOW;     // the current state of the output pin
int reading;         // the current reading from the input pin
int previous = LOW;  // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;  // the last time the output pin was toggled
long debounce =
    200;  // the debounce time in ms, increase if the output flickers

void setup() {
    // pin declaration
    pinMode(buttonPin, INPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    reading = digitalRead(buttonPin);  // check button

    // if the input just went from LOW and HIGH and we've waited long enough
    // to ignore any noise on the circuit, toggle the output pin and remember
    // the time
    if (reading == HIGH && previous == LOW && millis() - time > debounce) {
        if (state == HIGH)  // turn off
            state = LOW;
        else  // turn on
            state = HIGH;

        time = millis();  // reset time
    }

    // change pins accordingly
    digitalWrite(relayPin, state);
    digitalWrite(ledPin, state);

    previous = reading;  // save current status for next run
}
