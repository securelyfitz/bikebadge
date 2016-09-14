# 503 party bike badge - 2015
http://503.party/
hardware and software files for attiny-based bicycle badge with rotating flashy reverse-mount LED wheels

## Hardware Description
This project is designed as the badge for donors to the 503 party fund in 2015. The circuit is inteded to use the minimum number of components to get a rotating wheel effect with the LEDs while having a completely clean PCB top side.

## Hardware Theory
Since the number of GPIOs are limited in a tiny chip, some fancy schematic-ing was done.
The bike handlebars (brakes slow down) and pedals (go faster) are two metal areas used as capacitive sensors. This takes up 3 pins - 1 to drive all of them, plus 1 for each sensor.
That leaves 2 pins to control 16 LEDs (14 in final revision for aesthetic reasons) that have to flash in a specific progression:
* the two wheels are identical, so really we need to drive 8 LED positions
* the wheels have two 'pulses' going around them, 180 degrees out of phase, so opposite LEDs are always identical. 4 LED positions
* If LEDs are identical 180 degrees out of phase, then they're opposite 90 degrees out of phase. That means half the LEDs are inversions of the other half. 2 LEDs positons.

If we wire 1 led between VCC and a GPIO, and a second one between a GPIO and GND, then one will be on when GPIO is 1, and the other will be on when GPIO is 0
If we do PWM, then (duty cycle B) = (1 - duty cycle A)
This makes very simple code possible

## Bill of Materials:
* 14x OSRAM reverse-gullwing LEDs (LYT776 YELLOW LED is what i used, 475-2801-1-ND)
* 14x 200 Ohm 1206 SMT Resistor (digikey 311-10MERCT-ND)
* 2x 10M Ohm 0603 Resistor (digikey 311-200GRCT-ND)
* 1x ATTiny85 soic8 ()
* 1x 20mm through-hole CR2032 holder and battery

In quantity, BOM cost is about $2-$5 depending on if you can find the reverse-gullwing LEDs

##Building
All of the components are different sizes - if the pads line up it's in the right spot, just make sure pin 1 of the attiny aligns to the dot, and the 'noch' on the LEDS all point clockwise around the wheel.

##Software Description
This code is an Arduino sketch. I used the Sparkfun TinyAVR Programmer and follow the linked hookup guide to get it working: https://www.sparkfun.com/products/11801

The code for sensing the capacitive buttons is based on Paul Stoffregen's updated CapacitiveSensor libarry: https://github.com/PaulStoffregen/CapacitiveSensor
The LEDs are lit with PWM inside a loop. i is rotation point in radians of the wheel
```
for (float i=0;i<(3.1415*2);i+=(3.1415/revs)){
    analogWrite(pwm0,127*(cos(i)+1));
    analogWrite(pwm1,127*(sin(i)+1));
}
```


