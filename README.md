# Introduction to Robotics (2022 - 2023)
Introduction to Robotics laboratory homeworks, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

<br>

## Homework
<details>
  <summary>
    <b> <h3> :closed_book::green_book::blue_book: Homework 1 - <i> Controlling RGB led using potentiometers :closed_book::green_book::blue_book: </i> </h3> </b>
  </summary>
  
  ---
  
  ### Task requirements
  
<ul>
  <li><b>Components</b>: RGB led (1 minimum), potentiometers (3 minimum), resistors and wires (per logic)</li>
  <li><b>Technical Task</b>: Use a separat potentiometer to control each color of the RGB led (<b>R</b>ed, <b>G</b>reen and <b>B</b>lue). The control must be done with </b>digital electronics</b>.</li>
</ul> 

  ---

  ### Pictures of the setup
  
  <img src ="https://i.imgur.com/x1Uiysn.jpg" alt="Picture 1 - Controlling RGB led using potentiometers" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/u4WvUqu.jpg" alt="Picture 2 - Controlling RGB led using potentiometers" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/KkWl6Fi.jpg" alt="Picture 3 - Controlling RGB led using potentiometers" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/5WkeNwB.jpg" alt="Picture 4 - Controlling RGB led using potentiometers" style="width: 480px; height: 360px;"/>
 
  ---
  
  ### Video
  <a href="http://www.youtube.com/watch?feature=player_embedded&v=-FrS52ZmgYk" target="_blank"><img src="http://img.youtube.com/vi/-FrS52ZmgYk/0.jpg" alt="Video - Controlling RGB led using potentiometers" width="480" height="360" border="10"></a>

---

</details>

<details>
  <summary>
    <b> <h3> :green_heart::yellow_heart::heart: Homework 2 - <i> Traffic lights for a crosswalk :green_heart::yellow_heart::heart: </i> </h3> </b>
  </summary>
  
  ---
  
  ### Task requirements
  
<ul>
  <li><b>Components</b>: 5 LEDs, 1 button, 1 buzzer, resistors and wires (per logic)</li>
  <li><b>Technical Task</b>: Building the traffic lights for a crosswalk using 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).
  
  **The system has the following states:**
  1. **State 1** (default, reinstated after state 4 ends): green light for cars,
red light for people, no sounds. Duration: indefinite, changed by
pressing the button.
2. **State 2** (initiated by counting down 8 seconds after a button press):
the light should be yellow for cars, red for people and no sounds.
Duration: 3 seconds.
3. **State 3** (initiated after state 2 ends): red for cars, green for people
and a beeping sound from the buzzer at a constant interval. Duration:
8 seconds.
4. **State 4** (initiated after state 3 ends): red for cars, blinking green
for people and a beeping sound from the buzzer, at a constant interval,
faster than the beeping in state 3. This state should last 4
seconds.
  </li>
</ul> 

  ---

  ### Pictures of the setup
  
  <img src ="https://i.imgur.com/CUIfB7L.jpg" alt="Picture 1 - Traffic lights for a crosswalk" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/OVHloTe.jpg" alt="Picture 2 - Traffic lights for a crosswalk" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/7dJZcMp.jpg" alt="Picture 3 - Traffic lights for a crosswalk" style="width: 480px; height: 360px;"/>
 
  ---
  ### Video
  <a href="http://www.youtube.com/watch?feature=player_embedded&v=1RqH47JnsUs" target="_blank"><img src="http://img.youtube.com/vi/1RqH47JnsUs/0.jpg" alt="Video - Traffic lights for a crosswalk" width="480" height="360" border="10"></a>

---
</details>

<details>
  <summary>
    <b> <h3> :seven::seven::seven: Homework 3 - <i> Drawing on the 7-segment display :seven::seven::seven: </i> </h3> </b>
  </summary>
  
  ---
  
  ### Task requirements
  
<ul>
  <li><b>Components</b>: 1 7-segment display, 1 button, 1 joystick, resistors and wires (per logic)</li>
  <li><b>Technical Task</b>: Control the position of the segment and "draw" on the display using the joystick.
  
  **The system has the following states:**
  1. **State 1** (default, but also initiated after a button press in State 2):
  Current position blinking. The joystick can be used to move from one position to the neighbors. Short pressing of the button toggles state 2. Long pressing the button in state 1 resets the entire display by turning all the segments OFF and moving from the current position to the decimal point.
2. **State 2** (initiated after a button press in State 1):
The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X axis should change the segment state from ON to OFF or from OFF to ON. Clicking on the joystick should save the segment state and exit back to state 1.
  </li>
</ul> 

<b>Possible movements</b>:
| Current segment | UP  | DOWN | LEFT | RIGHT |
|-----------------|-----|------|------|-------|
| a               | N/A | g    | f    | b     |
| b               | a   | g    | f    | N/A   |
| c               | g   | d    | e    | dp    |
| d               | g   | N/A  | e    | c     |
| e               | g   | d    | N/A  | c     |
| f               | a   | g    | N/A  | b     |
| g               | a   | d    | N/A  | N/A   |
| dp              | N/A | N/A  | c    | N/A   |
  ---

  ### Pictures of the setup
  
  <img src ="https://i.imgur.com/cXHN0bn.jpg" alt="Picture 1 - Drawing on the 7-segment display" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/VBTUKkL.jpg" alt="Picture 2 - Drawing on the 7-segment display" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/ZzNt7pO.jpg" alt="Picture 3 - Drawing on the 7-segment display" style="width: 480px; height: 360px;"/>
 
  ---
  ### Video
  <a href="https://www.youtube.com/watch?v=Fd4zxVryrGY&list=LL&index=1&ab_channel=AlinaVoiculescu" target="_blank"><img src="http://img.youtube.com/vi/Fd4zxVryrGY/0.jpg" alt="Video - Drawing on the 7-segment display" width="480" height="360" border="10"></a>

---
</details>


<details>
  <summary>
    <b> <h3> :four::seven::tv: Homework 4 - <i> Building a hex number in 4 digit 7-display :four::seven::tv: </i> </h3> </b>
  </summary>
  
  ---
  
  ### Task requirements
  
<ul>
  <li><b>Components</b>: a joystick, a 4 digit 7-segment display, a 74hc595 shift
register</li>
  <li><b>Technical Task</b>: Use the joystick to move through the 4 digit 7-segment displays digits, press the button to lock in on the current digit and use the other axis to increment or decrement the number. Keep the button pressed to reset all the digit values and the current position to the first digit in the first state.
  
  **The system has the following states:**
  1. **State 1**: a joystick axis can be used to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, the selected digit will be locked in and the program will enter in the second state.
2. **State 2**: in this state, the decimal point stays always on, no longer blinking and the axis that cycles through the 4 digits can be no longer used. Instead, using the other axis, the number on the current digit can be incremented and decremented IN HEX (aka from 0 to F). Pressing the button again returns to the previous state.
3. **Reset**: toggled by long pressing the button only in the first state. When resetting, all the digits go back to 0 and the current position is set to the first (rightmost) digit, in the first state.
  </li>
</ul> 

  ---

  ### Pictures of the setup
  
  <img src ="https://i.imgur.com/yxmYtBn.jpg" alt="Picture 1 - Building a hex number in 4 digit 7-display" style="width: 360px; height: 480px;"/>
  <img src ="https://imgur.com/W2JihMU.jpg" alt="Picture 2 - Building a hex number in 4 digit 7-display" style="width: 360px; height: 480px;"/>
  <img src ="https://i.imgur.com/Zxklf2Y.jpg" alt="Picture 3 - Building a hex number in 4 digit 7-display" style="width: 360px; height: 480px;"/>
 
  ---
  ### Video
  <a href="https://www.youtube.com/watch?v=A91C275eRAI&list=LL&index=1&ab_channel=AlinaVoiculescu" target="_blank"><img src="http://img.youtube.com/vi/A91C275eRAI/0.jpg" alt="Video - Drawing on the 7-segment display" width="480" height="360" border="10"></a>

---
</details>


<details>
  <summary>
    <b> <h3> :snake::video_game::red_circle: Homework 5 - <i> Matrix minigame with LCD menu :snake::video_game::red_circle: </i> </h3> </b>
  </summary>
  
  ---
  
  ### Task requirements
  
<ul>
  <li><b>Components</b>: an LCD 16x2, a joystick, a led matrix 8x8, a MAX7219 Driver, a potentiometer</li>
  <li><b>Technical Task</b>: create a matrix minigame with an LCD menu
  
  **System description:**
   - **Game**: a joystick can be used to move across the matrix in order to get to the blinking food and eat it; when the food is eaten, the score will increase by 1 and the food will be generated again, randomly
   - **Menu**: a joystick can be used to scroll on the LCD with the joystick
    <br>
    **Functionalities:** <br>
    1. When powering up a game, a greeting message should be shown for a few moments. <br>
    2. Should contain the following categories: <br>
      (a) **Start game**: starts the game <br>
      (b) **Highscore**: shows the first 3 highscores <br>
      (c) **Settings**: here the difficulty can be set <br>
      (d) **About**: contains details about the game and the creator of the game <br>
      (e) **How to play**: short and informative description <br>
    3. While playing the game, all relevant info should be displayed (lives, score) <br>
  </li>
</ul> 

  ---

  ### Pictures of the setup
  
  <img src ="https://i.imgur.com/jZFoK1Z.jpg" alt="Picture 1 - Matrix minigame with LCD menu" style="width: 480px; height: 360px;"/>
  <img src ="https://imgur.com/TweGm4n.jpg" alt="Picture 2 - Matrix minigame with LCD menu" style="width: 480px; height: 360px;"/>
  <img src ="https://i.imgur.com/48i0qy3.jpg" alt="Picture 3 - Matrix minigame with LCD menu" style="width: 480px; height: 360px;"/>
 
  ---
  ### Video
  <a href="https://www.youtube.com/watch?v=ohBLwzHHevQ&list=LL&index=1&ab_channel=AlinaVoiculescu" target="_blank"><img src="http://img.youtube.com/vi/ohBLwzHHevQ/0.jpg" alt="Video - Matrix minigame with LCD menu" width="480" height="360" border="10"></a>

---
</details>