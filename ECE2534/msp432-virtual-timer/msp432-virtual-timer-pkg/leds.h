#ifndef LEDS_H
#define LEDS_H

typedef enum {black, red, green, yellow, blue, magenta, cyan, white} color_t;

void InitLEDs();
void SensorColorLEDSet(color_t c);
void MainColorLEDSet(color_t c);

#endif
