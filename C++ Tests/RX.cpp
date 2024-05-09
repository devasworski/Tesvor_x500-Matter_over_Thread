#include <HardwareSerial.h>

HardwareSerial MySerial(1); // Use UART1

// UART settings
const int rxPin = 16; // RX pin
const int txPin = 17; // TX pin
const int baudRate = 115200; // Baud rate

// Define the message types
const uint8_t batteryUpdateMsg[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x08};
const uint8_t deviceStatusMsg[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05};
const size_t msgLength = 6; // Length of the message identifiers
const size_t totalMsgLength = 15; // Total message length for battery updates
const size_t maxHistory = 10; // Maximum number of messages to keep in history

// Buffer for incoming data and message history
uint8_t buffer[totalMsgLength];
uint8_t messageHistory[maxHistory][totalMsgLength]; // Store last ten messages
size_t bufferIndex = 0;
size_t historyIndex = 0;

void setup() {
  MySerial.begin(baudRate, SERIAL_8N1, rxPin, txPin);
  Serial.begin(115200);
  Serial.println("UART Listener Started");
  memset(messageHistory, 0, sizeof(messageHistory)); // Initialize history buffer
}

void loop() {
  if (MySerial.available()) {
    // Read a byte and add it to the buffer
    uint8_t incomingByte = MySerial.read();
    buffer[bufferIndex] = incomingByte;
    bufferIndex = (bufferIndex + 1) % totalMsgLength;

    // Check for full message received
    if (bufferIndex == 0) {
      // Store the message in history and update history index
      memcpy(messageHistory[historyIndex], buffer, totalMsgLength);
      historyIndex = (historyIndex + 1) % maxHistory;

      // Process the message
      if (memcmp(buffer, batteryUpdateMsg, msgLength) == 0) {
        onBatteryUpdate(buffer[13]); // 14th byte is at index 13
      } else if (memcmp(buffer, deviceStatusMsg, msgLength) == 0) {
        onDeviceStatus();
      }
    }
  }

  delay(10); // Small delay to avoid CPU overload
}

void onBatteryUpdate(uint8_t batteryLevel) {
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
