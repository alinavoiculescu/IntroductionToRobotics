## :seven::seven::seven: Homework 3 - <i> Drawing on the 7-segment display :seven::seven::seven: </i>
  
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