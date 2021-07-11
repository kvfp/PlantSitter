# PlantSitter
Automatic plant watering system with various configurations - powered by Arduino!
> This endeavor with Arduino started out as a class project, but I expanded on it to apply more software and build a more sophisticated end-product!

## Project Files
https://drive.google.com/drive/folders/1NQMT7lRJZVqnV6E9HNil-Ppmle0Hhn1S
(videos + images included)

[![System1.jpg](https://i.postimg.cc/fLmVKsW1/System1.jpg)](https://postimg.cc/N9GGsWHx) [![System.jpg](https://i.postimg.cc/XJLb31sp/System.jpg)](https://postimg.cc/Kk1VDfS2)

## Description
I created a an Arduino system that would automatically water a plant based on its soil moisture percentage. In addition to this, I programmed a total of 5 watering "profiles":
1. Water if soil moisture is less 2%
2. Do not water at all (unless manually enabled by pressing the green button)
3. Water if soil moisture is less 30%
4. Water for 10 seconds, then wait another 10 seconds before watering again (for demo purposes)
5. Water once for 20 seconds every 24 hours

Each of the 5 profiles could be selected by cycling through them using a single button (the yellow one). Users can easily determine the profile they currently have selected through the number of beeps that sound after pressing the button.

## Notes
I would have preffered to use an LCD screen to implement the "profile" cycling menu, but I was having trouble powering the entire system with 5 volts. 😅 I hope to revisit this project in the future and upgrade it through a better power source and a more compact and practical design!

## Components Used
- 1 Arduino Uno
- 2 Breadboards
- 2 Buttons
- 1 Capacitive Soil Moisture Sensor
- 1 LED
- 1 5V Mini Water Pump
- 1 Watering Pipe
- 1 Piezo Buzzer
- 1 Water Container
- Some electrical tape
- A couple resistors
- Lots of wires
