// #include <Servo.h>

// #define DEBUG true

// int const AXIS_X_PIN = A0;
// // int const AXIS_Y_PIN = A1;

// int const SERVO_X_PIN = 5;
// int const SERVO_Y_PIN = 6;

// int const BUTTON_PIN = 4;

// int lastServoX = -1;
// int lastServoY = -1;

// int XAxisValue;
// int YAxisValue;

// int servoX;
// int servoY;

// bool buttonState;
// bool buttonSwitch;

// double const precision = 1.;
// int const step = 20;

// Servo servo[2];

// void setup()
// {
//   Serial.begin(115200);

//   pinMode(SERVO_X_PIN, OUTPUT);
//   pinMode(BUTTON_PIN, INPUT_PULLUP);
//   pinMode(AXIS_X_PIN, INPUT);
//   // pinMode(AXIS_Y_PIN, INPUT);
//   pinMode(LED_BUILTIN, OUTPUT);

//   servo[0].attach(SERVO_X_PIN);
//   servo[1].attach(SERVO_Y_PIN);

//   digitalWrite(LED_BUILTIN, LOW);
// }

// double servoScaleX = .7; // 180. / 1024.
// double servoScaleY = .7; // 180. / 1024.

// int joystickToServoX(double axisValue) {
//   return (int)(axisValue * servoScaleX / (double)step) * step;
// }

// int joystickToServoY(double axisValue) {
//   return (int)(axisValue * servoScaleY / (double)step) * step;
// }

// void printInfo() {
//   Serial.print(servoScaleX);
//   Serial.print("; ");
//   Serial.print(servoScaleY);
//   Serial.print("  X: ");
//   Serial.print(XAxisValue);
//   Serial.print(", ");
//   Serial.print(servoX);
//   Serial.print("  Y: ");
//   Serial.print(YAxisValue);
//   Serial.print(", ");
//   Serial.println(servoY);
// }


// void loop()
// {
//   XAxisValue = 1024 - analogRead(AXIS_X_PIN);
//   // YAxisValue = 1024 - analogRead(AXIS_Y_PIN);

//   servoX = joystickToServoX(XAxisValue);
//   // servoY = joystickToServoY(YAxisValue);
  
//   buttonState = digitalRead(BUTTON_PIN);
//   if (buttonState == LOW and buttonSwitch == false) {
//       buttonSwitch = true;
//       servoScaleX = 180. / XAxisValue;
//       servoScaleY = 180. / YAxisValue;
//       Serial.print("Changed servoScale");
//   } else if (buttonState == HIGH) {
//       buttonSwitch = false;
//   }

//   if (servoX != lastServoX)
//   {
//     lastServoX = servoX;
//     servo[0].write(servoX);
//   }

//   if (servoY != lastServoY)
//   {
//     lastServoY = servoY;
//     servo[1].write(servoY);
//   }
//   #if DEBUG
//   printInfo();
//   #endif
//   delay(150);
// }