#include <MorseNode.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


//**************
//*
//* Morsecode interpreter (dirty code ;) )
//*
//**************

const unsigned int SENSOR_PIN = A0;
const unsigned int BUTTON_PIN = 2;
const unsigned int DELAY = 50;
const unsigned int SENSOR_TOLERANCE = 20; // Sensor tolerance value
const unsigned int WORDS_PER_MINUTE = 4; // Not used
const unsigned int DIT_LENGTH_MS = 400; // general 1200 / WORDS_PER_MINUTE
const unsigned int DAH_LENGTH_MS = 500; // general DIT_LENGTH_MS * 3
const unsigned int WORD_GAP_MS = DIT_LENGTH_MS * 7;

int actionCounter = 0;
int characterCounter = 0;
int calibrateValue = 0;
int buttonState = 0;

bool isCalibrated = false;
bool isWordGap = false;

MorseNode &tree = MorseNode::getInstance();
MorseNode *treeCopy = NULL;

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Returns action enum for a GAP, DIT or DAH.
Action getAction(int milliseconds) {

    Action key = GAP;
    if (milliseconds >= DAH_LENGTH_MS) {
        key = DAH;
    } else if (milliseconds > 0 && milliseconds <= DIT_LENGTH_MS) {
        key = DIT;
    }
    return key;
}

// Calibrate the sensor
void calibrateSensor() {
    calibrateValue = analogRead(SENSOR_PIN);
}

// Return a boolean value if the light changes.
bool sensorAction() {
    int sensorValue = analogRead(SENSOR_PIN);
    return abs(sensorValue - calibrateValue) >= SENSOR_TOLERANCE;
}

// Traverse through the morsecode tree and return a node.
MorseNode *traverseTree(MorseNode &node, Action key) {

    //If the right or left edge equals with a DIT or DAH return the associated node or NULL.
    if (node.getRight() != NULL && node.getRight()->getAction() == key) {

        return node.getRight();
    } else if (node.getLeft() != NULL && node.getLeft()->getAction() == key) {

        return node.getLeft();
    }
    return NULL;
}

int row = -1;
int column = 0;

// Init lcd.
void lcdInit() {
    lcd.init(); //initialize the lcd
    lcd.backlight(); //open the backlight
}

// Write method for lcd display.
void lcdWrite(char *message, int row, int column, int delayTime) {
     Serial.print(column);
    lcd.setCursor(column, row);
    lcd.print(message);
    delay(delayTime);
}

// Write method for lcd display.
void lcdWrite(char *message, int delayTime) {
     
    row = (column == 0 && row < 4) ? row + 1 : (row < 4) ? row : 0; 
    lcdWrite(message, row, column, delayTime);
    column = ((column + strlen(message)) < 19) ? column + strlen(message) : 0; 
}

// Write method for lcd display.
void lcdWrite(char *message) {

    lcdWrite(message, 0);
}

// Clear method for lcd display.
void lcdClear() {

    row = -1;
    column = 0;
    lcd.clear();
}

void setup() {
    Serial.begin(9600);
    calibrateSensor();
    treeCopy = &tree;
    pinMode(BUTTON_PIN, INPUT);
    lcdInit();
}

void loop() {

    if (sensorAction()) {
        // If light sensitivity changes increment counter.
        actionCounter++;
    } else {
        characterCounter++; // Increment character counter for gap between alphanumeric characters.
        Action key = getAction(
                actionCounter * DELAY); // actionCounter * delay to determine the length of a specific DIT or DAH.
        actionCounter = 0; // Reset the action counter.

        if (key != GAP) {
            // Search for the next node with a DIT or DAH an return it.
            treeCopy = traverseTree(*treeCopy, key);
            characterCounter = 0; // Reset the character counter.
        } else {
            // Print the alphanumeric character only if the treeCopy or better the next node != NULL and the nextNode != tree which
            // means not the root node and the gap between letters is reached.
            if (treeCopy != NULL && treeCopy != &tree && characterCounter * DELAY >= DAH_LENGTH_MS * 2) {

                lcdWrite(treeCopy->getCharacter()); // Write the character to the lcd.
                treeCopy = NULL; // Set node to NULL.
                characterCounter = 0; // Reset the character counter.
                isWordGap = true; // Set wordGap to true for write a space between two words.
            } else if (isWordGap && characterCounter * DELAY >= WORD_GAP_MS) {

                lcdWrite(" "); // Write a space between two words.
                isWordGap = false; // Set word gap to false.
            }

            if (treeCopy == NULL) {

                treeCopy = &tree; // If node is null reset the actual binary search to the root node.
            }
        }
    }

    buttonState = digitalRead(BUTTON_PIN); // Read button state for calibartion.
    if (buttonState == HIGH && !isCalibrated) {

        // Write short three times countdown and calibrate.
        for (int i = 3; i > 0; i--) {
            lcdClear();
            char text[20];
            sprintf(text, "Calibrate in %d", i);
            lcdWrite(text, 0, 0, 1000); // Write text and delay 1000ms.
        }
        calibrateSensor();
        lcdClear();
        lcdWrite("Calibrated", 0, 0, 1000); // Write text and delay 1000ms.
        lcdClear();
        isCalibrated = true;
    } else if (buttonState == LOW && isCalibrated) {
        isCalibrated = false;
    }

    delay(DELAY);
}
