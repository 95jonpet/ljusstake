/*
 * A program for handling the light show of the 
 * "ljusstake project".
 *
 * Author: Peter Jonsson <95jonpet.se>
 * Version: 2015-12-02
 */

#include <Adafruit_NeoPixel.h>

#define DATA_PIN 6
#define NUM_LEDS 7
#define BRIGHTNESS 32
#define DELAY 20

// Initialize the led strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

uint8_t red = 255;
uint8_t green = 255;
uint8_t blue = 255;

/*
 * Set up everything and start the light show.
 */
void setup() {
    randomSeed(analogRead(0)); // Random seed

    strip.begin();
    strip.show();
    strip.setBrightness(BRIGHTNESS);
}

/*
 * The looping function in which the light show
 * takes place.
 */
void loop() {
    //rainbow(DELAY);
    //normal(10000);
    //randomColor(10000);
    uint8_t nextRed, nextGreen, nextBlue;
    nextRed = random(256);
    nextGreen = random(256);
    nextBlue = random(256);

    while (red != nextRed || green != nextGreen || blue != nextBlue) {
        red += constrain(nextRed - red, -1, 1);
        green += constrain(nextGreen - green, -1, 1);
        blue += constrain(nextBlue - blue, -1, 1);

        uint8_t i;
        for (i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(red, green, blue));
        }

        strip.show();
        delay(DELAY);
    }

    delay(5000);
}

/*
 * Displays a normal and quite boring white color
 * for all LEDs.
 */
void normal(unsigned int duration) {
    uint16_t i;
    for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    }

    strip.show();
    delay(duration);
}

void randomColor(unsigned int duration) {
    uint8_t red, green, blue;
    red = random(256);
    blue = random(256);
    green = random(256);

    uint16_t i;
    for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
    }

    strip.show();
    delay(duration);
}

/*
 * Displays a rainbow.
 */
void rainbow(uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel((i + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

/*
 * Input a value 0 to 255 to get a color value.
 * The colors are a transition r - g - b - back to r.
 */
uint32_t Wheel(byte WheelPos) {
    if (WheelPos < 85) {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}
