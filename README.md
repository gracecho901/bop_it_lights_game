Game description: the objective of this game is to hit the correct controls attached to the flashing lights. Kind of like a bop it! But instead of bopping, twisting,
or pulling it, there are inputs the use must get correct on the Circuitboard express to win the game. Red light flashes mean hit button A, green light flashes mean hit button B,
and blue light flash mean shift the slide switch. The game gets progressively faster and harder, and ends after 15 rounds or 3 strikes. Every 5 correct responses mean level up,
and that comes with a timer speed increase. There is a positive sound played after the correct input is hit and a wrong sound played after incorrect input.


## INPUT/OUTPUTS

| Input/Output | Type   | Raw Values     | Function                          | Notes/Mapping                                           |
|--------------|--------|----------------|-----------------------------------|----------------------------------------------------------|
| Button A     | Input  | press / not    | `CircuitPlayground.leftButton()`  | Respond to red                                           |
| Button B     | Input  | press / not    | `CircuitPlayground.rightButton()` | Respond to green                                         |
| Slide Switch | Input  | left / right   | `CircuitPlayground.slideSwitch()` | Respond to blue by toggling<br>Must flip from previous position (L ⇄ R) |
| Neopixels    | Output | RGB (0–255)    | `setPixelColor()`                 | Display target color                                     |
| Speaker      | Output | Sound tones    | `playTone()`                      | Feedback (right or wrong)                                |


Video demonstration of game:
https://youtu.be/pXiMkCwvsi4
