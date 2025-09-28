# Mechatronic Alarm Clock
Made as part of my interview for the Arkwright Engineering Scholarship. 

> A pdf summary of the project can be found [here](https://github.com/clement-jin/curtain-alarm/blob/main/supporting-material/Motor%20Alarm%20Design.pdf), and the presentation used in the interview [here](https://github.com/clement-jin/curtain-alarm/blob/main/supporting-material/Arkwright%20Presentation.pptx)

This alarm clock raises the curtains at a set time while beeping. It included a motor, buzzer module, custom 3D printed parts, and a 7-segment display programmable using buttons.
Thank you to Dr David Roche for supporting my application process. 

## Requirements
The ```SevSeg``` library from [https://github.com/DeanIsMe/SevSeg](https://github.com/DeanIsMe/SevSeg) is used to control the display. 
This project used Arduino UNO. 

## Files
- ```curtain_driver.ino``` is the main file containing the program loop.
- ```clock.cpp``` keeps time and updates the display
- ```alarm.cpp``` drives the motor and turns on the audio alarm.
- ```UI.cpp``` defines different user modes: ```display_on, display_off, change_current_time, change_alarm_time``` and how to change between them.
