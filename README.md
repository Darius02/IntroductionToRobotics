# Introduction To Robotics

## Repository containing homeworks from the Introduction to Robotics course.

![iStock-966248982](https://user-images.githubusercontent.com/75308520/200678473-f2f08229-7c09-4214-8df1-5cef34e78a1f.jpg)


### Homework #1

Task Requirements: Controlling RGB LED using Potentiometers

Use a separate potentiometer in controlling each of the color of the RGB led (Red, Green and Blue).

Picture of the setup:

![IMG_9615](https://user-images.githubusercontent.com/75308520/197857681-ae8fad75-cc71-4b96-8512-ef3aa84cd28f.jpg)

[Click here for video](https://www.youtube.com/watch?v=CbO2Ixi61wY)


### Homework #2

Task Requirements: Crosswalk

Building the traffic lights for a crosswalk.

Picture of the setup:

![IMG_9641](https://user-images.githubusercontent.com/75308520/199349412-0b250412-1242-4664-9e34-30efd1b9bf4e.jpg)

[Click here for video](https://www.youtube.com/watch?v=XCQfLF9p-PE)


### Homework #3

Task Requirements: Using a joystick to control the position of the segment and ”draw” on the display.

The system has the following states:

  State 1: Current  position  blinking. Can use the joystick to move from one position to neighbours. Short pressing the button toggles State 2. Long pressing the       button in State 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
  
  State 2: The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the Y axis should change the segment state from   ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back to State 1.
  
  Picture of the setup:
  
  ![h3](https://user-images.githubusercontent.com/75308520/200677497-75c1cb8e-bc65-4616-878c-65d777013ee9.jpeg)
  
  [Click here for video](https://www.youtube.com/watch?v=avmJ3c8Ojbo)
  
  
  
  ### Homework #4
  
  Task Requirements: Using a joystick to control the values on each digit of a 4-digit 7-segment display connected to a shift register.
  
  The system has the following states:
  
  State 1: Allows the user to move the joystick up and down in order to shift between the displays, while the dot of the current display is blinking. Pressing the
  buttton allows you to lock the current digit and enter the second state.
  
  State 2: The decimal point stays always on and the axis can not longer be used to cycle through the 4 digits. Using the other axis, the number on the current digit     IN HEX can be incremented or decremented. Pressing the button again returns to the previous state. When changing the number, it can be incremented for each joystick   movement - it does not increment continuosly if the joystick is kept in one position.
  
  State 3: Reset: toggled by long pressing the buttononly in the first state. When resetting, all the digits go back to 0 and the current position is set to the first   (rightmost) digit, in the first state.
  
  Picture of the setup:
  
  ![IMG_9716](https://user-images.githubusercontent.com/75308520/202033683-40d6ccb7-703d-4628-9e10-1e70ce616656.jpg)
  
  [Click here for video](https://www.youtube.com/watch?v=pVjWSul-lE4)

  
  
