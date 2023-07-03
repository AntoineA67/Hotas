// #include <Joystick.h>

// // Create the Joystick
// Joystick_ Joystick;

// // Constant that maps the physical pin to the joystick button.
// const int pinToButtonMap = 2;
// const int pinToButtonMap2 = 3;
// // const int groundButton = 8;
// const int hallPin = A3;


// void setup() {
//   // Initialize Button Pins
//   // pinMode(groundButton, OUTPUT);
//   pinMode(pinToButtonMap, INPUT_PULLUP);
//   pinMode(pinToButtonMap2, INPUT_PULLUP);
//   // pinMode(hallPin, INPUT);

//   Serial.begin(115200);

//   // Initialize Joystick Library
//   Joystick.setXAxisRange(0, 200);
//   Joystick.begin();
// }

// // Last state of the button
// int lastButtonState = 0;
// int lastButtonState2 = 0;

// int lastXAxisValue = 0;

// void loop() {

//   const int currentXAxisValue = analogRead(hallPin);
//   if (currentXAxisValue != lastXAxisValue) {
//     Serial.println(currentXAxisValue);
//     Joystick.setXAxis(currentXAxisValue);
//     lastXAxisValue = currentXAxisValue;
//     // sendUpdate = true;
//   }

//   // Read pin values
//   int currentButtonState = !digitalRead(pinToButtonMap);
//   if (currentButtonState != lastButtonState) {
//     Joystick.setButton(0, currentButtonState);
//     lastButtonState = currentButtonState;
//   }

//   int currentButtonState2 = !digitalRead(pinToButtonMap2);
//   if (currentButtonState2 != lastButtonState2) {
//     Joystick.setButton(1, currentButtonState2);
//     lastButtonState2 = currentButtonState2;
//   }

//   delay(50);
// }