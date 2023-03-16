#include <Arduino_MKRENV.h>
#include <WiFiNINA.h>

// Define the ports of sensors and actuators
int redPin = 25;
// int greenPin = 25;
int bluePin = 27;
int butPin = 3;
int ledPin = 1;

void setup()
{
    Serial.begin(9600);

    if (!ENV.begin())
    {
        Serial.println("Failed to initialise MKR ENV shield");
        while (1)
            ;
    }

    WiFiDrv::pinMode(25, OUTPUT);
    WiFiDrv::pinMode(26, OUTPUT);
    WiFiDrv::pinMode(27, OUTPUT);

    // pinMode(redPin, OUTPUT);
    // pinMode(greenPin, OUTPUT);
    // pinMode(bluePin, OUTPUT);
    pinMode(butPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    // Read the temperature from the built-in sensor
    float temperature = ENV.readTemperature();
    Serial.print("Original Temperature=");
    Serial.print(temperature);

    // Map the temperature reading to an RGB value between red and blue
    int r = map(temperature, 20, 30, 0, 255);
    int b = map(temperature, 20, 30, 255, 0);
    int g = 0; // We don't need green
    Serial.print(" Value of mapped r,g,b =");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);
    // Serial.println();

    // Set the RGB LED to the mapped color
    WiFiDrv::analogWrite(redPin, r);
    // WiFiDrv::analogWrite(greenPin, g);
    WiFiDrv::analogWrite(bluePin, b);

    // Read from the button
    int butValue = digitalRead(butPin);
    // Serial.print(pirValue);

    // Control the LED Socket based on PIR motion sensor
    if (butValue == 1)
    {
        digitalWrite(ledPin, HIGH);
        Serial.println("high");
    }
    else
    {
        digitalWrite(ledPin, LOW);
        Serial.println("low");
    }

    delay(1000);
}