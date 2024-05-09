#include <HardwareSerial.h>

HardwareSerial RXSerial(1); // Use UART1
const unsigned long timeout = 2; // Timeout in milliseconds


// UART settings
const int rxPin = 16; // RX pin
const int txPin = 17; // TX pin
const int baudRate = 115200; // Baud rate

// Define the message types
const uint8_t batteryUpdateMsg[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x08};
const uint8_t deviceStatusMsg[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05};
const size_t msgIdentLength = 6; // Length of the message identifiers
const size_t totalMsgLength = 256; // Max message length


// Buffer for incoming data and message history
uint8_t buffer[totalMsgLength];
size_t bufferIndex = 0;

// Time of last message received
unsigned long lastTime = millis();



// Compare two Array pointers
bool compareArrays(const uint8_t *arr1, const uint8_t *arr2, size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

// Process the message
void processMassage(){
  if (compareArrays(buffer, batteryUpdateMsg, 6)) {
        onBatteryUpdate();
      } else if (compareArrays(buffer, deviceStatusMsg, 6)) {
        onDeviceStatus();
      } else {
        Serial.println("Unknown message type");
      }
}


void setup() {
  RXSerial.begin(baudRate, SERIAL_8N1, rxPin, txPin);
  Serial.begin(115200);
  Serial.println("UART Listener Started");
}

void loop() {

  while (RXSerial.available()) {
    buffer[bufferIndex] = RXSerial.read();
    bufferIndex = (bufferIndex + 1) % totalMsgLength;
    lastTime = millis(); // Update the time of the last received character
  }

  if ((millis() - lastTime >= timeout) && (bufferIndex > 0)) {
    processMassage();
    // Clear the message for the next read
    bufferIndex = 0;
  }

}

void onBatteryUpdate() {
  uint8_t batteryLevel = buffer[13];
  Serial.print("Battery Update: New level is ");
  Serial.print(batteryLevel);
  Serial.println("%");
  // Add your code here
}

void onDeviceStatus() {
  // Check the last ten messages for a known device status pattern
  if (isWakeUp() || isVacuumStart() || isVacuumStop() || isChargeStart() || isChargeStop()) {
    Serial.println("Recognized a device status pattern");
  } else {
    Serial.println("Unrecognized Device Status Pattern.");
  }
}

bool isWakeUp() {
  // Define the pattern for "Device Wake-Up"
  // Add code to compare the pattern with the last messages in history
  // Return true if pattern matches, otherwise false
}

bool isVacuumStart() {
  // Define the pattern for "Vacuum Start"
  // Similar to isWakeUp(), check for this specific pattern
}

bool isVacuumStop() {
  // Define the pattern for "Vacuum Stop"
  // Similar to isWakeUp(), check for this specific pattern
}

bool isChargeStart() {
  // Define the pattern for "Charge Start"
  // Similar to isWakeUp(), check for this specific pattern
}

// Checks if the sequence matches the "Charging Stopped" pattern
bool isChargeStop() {
    // Define the pattern for "Charging Stopped"
    const uint8_t chargeStopPattern[][msgLength] = {
        {0x02, 0x01, 0x00, 0x01, 0x00, 0x12},
        {0x01, 0x01, 0x00, 0x01, 0x01, 0x12},
        {0x05, 0x04, 0x00, 0x01, 0x00, 0x18},
        {0x05, 0x04, 0x00, 0x01, 0x00, 0x18},
        {0x03, 0x04, 0x00, 0x01, 0x00, 0x16},
        {0x02, 0x01, 0x00, 0x01, 0x00, 0x12}
    };

    const size_t patternLength = sizeof(chargeStopPattern) / sizeof(chargeStopPattern[0]);

    // Check if there are enough messages in history
    if ((historyIndex < patternLength) && (messageHistory[maxHistory - 1][0] != 0)) {
        // Not enough messages or the history is not fully populated yet
        return false;
    }

    // Starting index for comparison in the message history
    size_t startIndex = (historyIndex + maxHistory - patternLength) % maxHistory;

    for (size_t i = 0; i < patternLength; i++) {
        size_t index = (startIndex + i) % maxHistory;
        if (memcmp(messageHistory[index], chargeStopPattern[i], msgLength) != 0) {
            return false; // Pattern does not match
        }
    }

    // Pattern matches, clear history
    memset(messageHistory, 0, sizeof(messageHistory));
    historyIndex = 0;
    Serial.println("Device stopped charging");
    return true;
}

void onOtherMessage() {
  Serial.println("Other Type of Message Received.");
  // Add your code here
}
