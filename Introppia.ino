#include "Arduino.h"

#define GATE_PIN 9
#define POT_PIN A0

void setup()
{
    Serial.begin( 9600 );
    pinMode( GATE_PIN, OUTPUT );
    digitalWrite( GATE_PIN, LOW );
}

// The loop function is called in an endless loop
void loop()
{
    int speed;
    speed = map( analogRead( POT_PIN ), 0, 1024, 0, 255 );
    Serial.println( speed );
    analogWrite( GATE_PIN, speed );
}
