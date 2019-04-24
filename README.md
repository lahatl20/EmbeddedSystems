# EmbeddedSystems
This is code for a ultraviolet (UV) data logger with a solar tracking system. The project utilizes two micro-controllers. 
The UV sensor, on one micro-controller, sends its data to the other micro-controller that has the sd card module that stores 
the information. One of the micro-controllers is also used for the solar tracking system which utilizes four photo-resistors and 
two stepper motors

1. ECS - This file holds the code for the solar tracking system as well as the sd card module
2. ECS2 - This file holds the code for the uv sensor as well as the altitude sensor
3. card_test & read_write_test - These files were used to ensure the SD card module was functioning properly
4. uv_sensor_test - This file was used to test the UV sensor and ensure it worked
5. altimeter_test - This file was used to test the altitude sensor and ensure it worked
6. motor_test - This file was used to test the stepper motors and ensure they worked
7. tracker_concept - This file was used to test the concept of the solar tracking system using photoresistors and some LEDs
