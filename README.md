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