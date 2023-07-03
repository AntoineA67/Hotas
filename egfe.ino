#include <Joystick.h>
#include <EEPROM.h>

const uint8_t buttonCount = 8;
Joystick_ controller(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, buttonCount,
                     0, true, true, false,
                     true, true, false,
                     false, false, false,
                     false, false);

int const BTN_A_PIN = 16;
int const BTN_B_PIN = 3;
int const BTN_C_PIN = 15;
int const BTN_D_PIN = 5;
int const BTN_E_PIN = 14;
int const BTN_F_PIN = 7;

int const TRIG_1 = 2;
int const TRIG_2 = 4;

int const AXIS_Y1_PIN = A0;
int const AXIS_Y2_PIN = A1;
int const AXIS_X1_PIN = A8;
int const AXIS_X2_PIN = A10;
int const AXIS_RX_PIN = A3;
int const AXIS_RY_PIN = A2;

int const buttonPins[buttonCount] = {
    BTN_A_PIN,
    BTN_B_PIN,
    BTN_C_PIN,
    BTN_D_PIN,
    BTN_E_PIN,
    BTN_F_PIN,
    TRIG_1,
    TRIG_2};

int lastButtonValue[buttonCount];
int lastXAxisValue = -1;
int lastYAxisValue = -1;
int lastRxAxisValue = -1;
int lastRyAxisValue = -1;

typedef struct s_AxisValues {
    int zero;
    int min;
} t_AxisValues;

t_AxisValues y1;
t_AxisValues y2;
t_AxisValues x1;
t_AxisValues x2;

// Function to write an int value to EEPROM
void writeIntToEEPROM(int address, int value) {
  byte lowByte = (value & 0xFF);
  byte highByte = ((value >> 8) & 0xFF);
  EEPROM.update(address, lowByte);
  EEPROM.update(address + 1, highByte);
}

void setup() {
    Serial.begin(115200);

    EEPROM.get( 0, y1 );
    EEPROM.get( 4, y2 );
    EEPROM.get( 8, x1 );
    EEPROM.get( 12, x2 );

    controller.setXAxisRange(0, 1023);
    controller.setYAxisRange(1023, 0);

    controller.setRxAxisRange(0, 1023);
    controller.setRyAxisRange(1023, 0);

    controller.begin(false);

    for (int i = 0; i < buttonCount; i++) {
        pinMode(buttonPins[i], (buttonPins[i] == TRIG_1 || buttonPins[i] == TRIG_2) ? INPUT : INPUT_PULLUP);
        lastButtonValue[i] = -1;
    }

    pinMode(AXIS_X1_PIN, INPUT_PULLUP);
    pinMode(AXIS_X2_PIN, INPUT_PULLUP);

    pinMode(AXIS_Y1_PIN, INPUT_PULLUP);
    pinMode(AXIS_Y2_PIN, INPUT_PULLUP);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    // Serial.println("Set up !");
}


void loop() {
    const int currentX1AxisValue = analogRead(AXIS_X1_PIN);
    const int currentX2AxisValue = analogRead(AXIS_X2_PIN);

    const int currentY1AxisValue = analogRead(AXIS_Y1_PIN);
    const int currentY2AxisValue = analogRead(AXIS_Y2_PIN);

    if (Serial.available()) {
        String s = Serial.readString();
        if (s == "zero") {
            x1.zero = currentX1AxisValue;
            x2.zero = currentX2AxisValue;
            y1.zero = currentY1AxisValue;
            y2.zero = currentY2AxisValue;
            writeIntToEEPROM(0, y1.zero);
            writeIntToEEPROM(4, y2.zero);
            writeIntToEEPROM(8, x1.zero);
            writeIntToEEPROM(12, x2.zero);
            Serial.println("Zero set");
        } else if (s == "x") {
            if (currentX1AxisValue < currentX2AxisValue) {
              x1.min = currentX1AxisValue;
              writeIntToEEPROM(10, x1.min);
              Serial.println("X Min set");
            }
            else {
              x2.min = currentX2AxisValue;
              writeIntToEEPROM(14, x2.min);
              Serial.println("X Max set");
            }
        }else if (s == "y") {
            if (currentY1AxisValue < currentY2AxisValue) {
              y1.min = currentY1AxisValue;
              writeIntToEEPROM(2, y1.min);
              Serial.println("Y Max set");
            }
            else {
              y2.min = currentY2AxisValue;
              writeIntToEEPROM(6, y2.min);
              Serial.println("Y Min set");
            }
        }
    }
    bool sendUpdate = false;
    int f = 0;

    if (currentY1AxisValue < y1.zero) {
      f = 1023 - (double)(currentY1AxisValue - y1.min) / (double)(y1.zero - y1.min) * 512;
    } else {
      f = ((double)(currentY2AxisValue - y2.min) / (double)(y2.zero - y2.min) * 512);
    }
    if (f > 1023) {
      f = 1023;
    } else if (f < 0) {
      f = 0;
    }
    if (f != lastYAxisValue) {
      controller.setYAxis(f);
      lastYAxisValue = f;
      sendUpdate = true;
    }
    if (currentX1AxisValue < x1.zero) {
      f = (double)(currentX1AxisValue - x1.min) / (double)(x1.zero - x1.min) * 512;
    } else {
      f = 1023 - ((double)(currentX2AxisValue - x2.min) / (double)(x2.zero - x2.min) * 512);
    }
    if (f > 1023) {
      f = 1023;
    } else if (f < 0) {
      f = 0;
    }
    if (f != lastXAxisValue) {
      controller.setXAxis(f);
      lastXAxisValue = f;
      sendUpdate = true;
    }

    for (int i = 0; i < buttonCount; i++)
    {
      const int buttonValue = digitalRead(buttonPins[i]);

      if (buttonValue != lastButtonValue[i])
      {
        controller.setButton(i, (buttonPins[i] == TRIG_1 || buttonPins[i] == TRIG_2) ? buttonValue : !buttonValue);
        lastButtonValue[i] = buttonValue;
        sendUpdate = true;
      }
    }
    const int currentRxAxisValue = analogRead(AXIS_RX_PIN);
    if (currentRxAxisValue != lastRxAxisValue)
    {
      controller.setRxAxis(currentRxAxisValue);
      lastRxAxisValue = currentRxAxisValue;
      sendUpdate = true;
    }

    const int currentRyAxisValue = analogRead(AXIS_RY_PIN);
    if (currentRyAxisValue != lastRyAxisValue)
    {
      controller.setRyAxis(currentRyAxisValue);
      lastRyAxisValue = currentRyAxisValue;
      sendUpdate = true;
    }

    if (sendUpdate) {
        controller.sendState();
    }
    delay(50);
}