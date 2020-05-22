#include <SoftwareSerial.h>
#define RX 2
#define TX 3

#define greenLED A0
#define redLED A1

char THIS_CUBE = 'B';
char OTHER_CUBE = 'A';

SoftwareSerial softSerial(RX, TX);

// Cube Face class
class Face {
  public:
    Face(uint8_t _inputPin, int _value) {
      inputPin = _inputPin;
      value = _value;
    }

    void init() {
      pinMode(inputPin, INPUT_PULLUP);
    }

    bool isActive() {
      return digitalRead(inputPin) == LOW;
    }

    int getValue() {
      return value;
    }

  private:
    uint8_t inputPin;
    int value;
};

const uint8_t MAX_FACES = 6;
Face Cube[MAX_FACES] = {
  // face1 inputPin, face1 value
  Face(4, 1),
  // face2 inputPin, face2 value
  Face(5, 2),
  // face3 inputPin, face1 value
  Face(6, 3),
  // face4 inputPin, face2 value
  Face(7, 4),
  // face5 inputPin, face1 value
  Face(8, 5),
  // face6 inputPin, face2 value
  Face(9, 6),
};

void setup() {
  // setup code
  Serial.begin(9600);
  softSerial.begin(4800);

  // initialize the input pins of the cube faces
  for (uint8_t face = 0; face < MAX_FACES; face++) {
    Cube[face].init();
  }
}

int lastValue = 0;
int thisCubeValue;
int incomingValue;
String str = "";

void loop() {
  // main code
  // Scan cube faces
  for (uint8_t face = 0; face < MAX_FACES; face++) {
    uint8_t thisCubeValue = Cube[face].getValue();
    if (Cube[face].isActive() && thisCubeValue != lastValue) {
  
  // Send face value to other cube
      softSerial.print(char(thisCubeValue));
      lastValue = thisCubeValue;
      str = "This Cube Send " + String(THIS_CUBE) + ": " + String(thisCubeValue);
      Serial.println(str);
      str = "Other Cube Read " + String(OTHER_CUBE) + ": " + incomingValue;
      Serial.println(str);
  
  // Read other cube face value, activate LEDs
      if (softSerial.available()) {
        incomingValue = softSerial.read();
        if (incomingValue == 1 && thisCubeValue == 6) {   //turn on green LED
          digitalWrite(greenLED, HIGH);
          digitalWrite(redLED, HIGH);
          THIS_CUBE = 'D';
          Serial.println("Success");
        } else {     //turn on red LED
          digitalWrite(greenLED, LOW);
          digitalWrite(redLED, LOW);
          THIS_CUBE = 'B';
          Serial.println("Fail");
        }
      }
    }
  }
  lastValue = 0;
  delay(500);
}
