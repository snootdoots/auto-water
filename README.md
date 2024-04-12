# auto-water
Code for our ENGR 100 final project, AutoWater, an autonomous solar-powered plant waterer.

# Requirements
Requires the HX711 Arduino library.

# Functions
```readSoil()```: returns the current moisture value of the soil\
```sendBluetooth()```: sends a bluetooth signal\
```readWeight()```: uses sendBluetooth to send a bluetooth signal if weight falls below threshold\
```moveServo(time)```: moves servo to down position for the amount of seconds provided\
```checkAndWater()```: calls readSoil() to check if moisture is below a threshold, and waters if it is
