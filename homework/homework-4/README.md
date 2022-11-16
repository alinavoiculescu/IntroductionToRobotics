## :four::seven::tv: Homework 4 - <i> Building a hex number in 4 digit 7-display :four::seven::tv: </i> </h3> </b>
  
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
  