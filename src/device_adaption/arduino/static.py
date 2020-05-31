beginning = '''
#include <SoftwareSerial.h>     // board-to-board communication

// Declare pin numbers for serial communication between boards,
// and initialize the serial line object.
// In this example, we use digital pins 2 and 3.
#define RX 2
#define TX 3
SoftwareSerial comms(RX, TX);

// Declare variables for manual cycling of board's label.
// NOTE: manual cycling behavior is for demonstration purposes only.
const int BUTTON_PIN = 7;

// Declare a map of currLabel: nextLabel schemas.
struct label_changes {
    const int older;
    const int newer;
};

struct rule {
    label_changes pairs[2];     // Using only 2 node connective rules for now
};

/**
 * ========================================================
 * ======== Begin Code Generator Definitions ==============
 * ========================================================
 */

'''

end = '''
/**
 * ========================================================
 * ========== End Code Generator Definitions ==============
 * ========================================================
 */

// Declare a digital pin to be used to detect a mating event.
uint8_t EVENT_PIN = 4;

// Declare RGB LED pins for light status
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

bool READY = true;

bool ACTIVE = false;

void setup() {
    // setup code for node

    // Set up serial connections
    Serial.begin(9600);
    comms.begin(4800);

    // Set up RGB pins
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    // Set up button pin
    pinMode(BUTTON_PIN, INPUT);

    // set LED color to blue (inactive)
    color(0, 0, 255);
}

void loop() {
    // main code for node

    // Simulate immediate disconnect of connection events which are 
    // not part of the rule set.
    if (!READY) {
        // Disconnect/reset event is incomplete; cycle again.
        if (digitalRead(EVENT_PIN) != HIGH) return;
        // Otherwise, set READY to true
        READY = true;
        // set LED color to blue (inactive)
        color(0, 0, 255);
        Serial.println("Ready to switch labels -- current label is " + ((char)CURR_LABEL + '0'));
        // needs delay for user error
        delay(300);
        return;
    }

    if (!ACTIVE) { 
        // Check to see if button for board was pressed; 
        // if so; label needs to be cycled.
        if (digitalRead(BUTTON_PIN) == HIGH) {
            Serial.println("Cycling label because button press was detected.");
            cycleLabel();
            return;
        }

        // set to active on next reset button press
        if (digitalRead(EVENT_PIN) == HIGH) {
            Serial.println("Setting state to ACTIVE to find rule on next loop()");
            Serial.println("Current label is: " + String(CURR_LABEL));
            ACTIVE = true;
            delay(200);
            return;
        }
    }

    // Check activity state of connection pin
    if (READY && ACTIVE) { 
        // If connection pin lights up, proceed with board-to-board serial 
        // read/write
        performStateChange();
    }
}

void performStateChange() {
    /*
    // flush the buffer??
    while (comms.available()) {
        char t = comms.read();
    }
    */
    // Send state label to other board
    char toSend = char(CURR_LABEL);
    int sentChars = comms.print(toSend);
    Serial.println("Sent a total of " + String(sentChars) + " characters to neighbor. Sent char was " + toSend);
    // delay(300);
    // Read other cube face value, activate LEDs
    int waits = 0;
    while (comms.available() == 0) {
        // wait
        waits++;
    }
    if (comms.available()) {
        int charcount = comms.available();
        char incomingValue = comms.read();
        Serial.println("Char is " + String(incomingValue) + "; int is " + String((uint8_t) incomingValue));
        Serial.println("There were a total of " + String(charcount) + " characters available.");
        Serial.println("Read neighbor label is: " + String(incomingValue));
        // Check ruleset for values; perform label transition if 
        // two nodes are valid, and require connection break (reset) 
        // if nodes do not belong in valid rule.
        int rule_index = findLabel(incomingValue);
        if (rule_index != -1) {
            if (executeStateChange(rule_index)) {
                // LED green for funsies
                color(0, 255, 0);
                Serial.println("Rule successfully applied!");
                Serial.println("New label is: " + String(CURR_LABEL));
            } else {
                // LED orange -- rule found but not successfully applied?!
                color(255, 165, 0);
                Serial.println("A rule was found but could not be successfully applied.");
            }
        } else {
            disconnect(incomingValue);
        }
        // Stabilize state until user triggers next condition
        READY = false;
        ACTIVE = false;
        Serial.println("Hit reset button to switch node labels and try another rule.");
    } else {
        READY = false;
        ACTIVE = false;
        color(255, 150, 5);   // orange-ish
        Serial.println("SoftwareSerial comms are not available; check that all boards are powered and connected.");
    }
}

int findLabel(int otherNode) {
    int idx = -1;
    for (int i = 0; i < RULE_COUNT; i++) {
        if (
            (ruleset[i].pairs[0].older == CURR_LABEL && 
             ruleset[i].pairs[1].older == otherNode) 
                ||
            (ruleset[i].pairs[0].older == otherNode &&
             ruleset[i].pairs[1].older == CURR_LABEL)
                                                     ) {
                idx = i;
                break;
        }
    }
    return idx;
}

bool executeStateChange(int idx) {
    if (ruleset[idx].pairs[0].older == int(char(CURR_LABEL))) {
        CURR_LABEL = ruleset[idx].pairs[0].newer;
        return true;
    } else if (ruleset[idx].pairs[1].older == CURR_LABEL) {
        CURR_LABEL = ruleset[idx].pairs[1].newer;
        return true;
    }
    // TODO: reset CURR_LABEL_INDEX to match CURR_LABEL?
    return false;
}

void disconnect(int v) {
    Serial.println("A valid rule did not exist for this combination of labels.");
    Serial.println("This node: " + String(CURR_LABEL) + " Other node: " + String(v));
    Serial.print("Simulating node disconnect -- ");
    Serial.println("hit reset button connected to pin " + String(EVENT_PIN));
    // LED red for funsies
    color(255, 0, 0);
}

void cycleLabel() {
    // Set LED, print label cycling initiated
    color(255, 0, 255);
    Serial.println("Cycling label for this node.");
    Serial.print("Old label: " + String(CURR_LABEL));
    // Increment label index and update internal state of node
    CURR_LABEL_INDEX = (CURR_LABEL_INDEX + 1) % MAX_LABELS;
    CURR_LABEL = labels[CURR_LABEL_INDEX];
    Serial.println(" New label: " + String(CURR_LABEL));
    // Give user a chance to release button before next loop()
    delay(200);
    // Reset LED to blue (inactive)
    color(0, 0, 255);
}

void color(unsigned char r, unsigned char g, unsigned char b) {
    analogWrite(redPin, r);
    analogWrite(greenPin, g);
    analogWrite(bluePin, b);
}
'''
