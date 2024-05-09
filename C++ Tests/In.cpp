#include <HardwareSerial.h>

HardwareSerial MySerial(1); // Use UART1

// UART settings
const int rxPin = 16; // RX pin
const int txPin = 17; // TX pin
const int baudRate = 115200; // Baud rate

// Define the sequences to listen for
const uint8_t sequenceStart[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05, 0x02, 0x01, 0x00, 0x01, 0x01, 0x13};
const uint8_t sequenceStop[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05, 0x02, 0x01, 0x00, 0x01, 0x00, 0x12};
const uint8_t sequenceCharge[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05, 0x02, 0x01, 0x00, 0x01, 0x00, 0x12};
const uint8_t sequenceStopCharge[] = {0x55, 0xAA, 0x03, 0x07, 0x00, 0x05, 0x02, 0x01, 0x00, 0x01, 0x00, 0x12};
const size_t sequenceLength = 12; // Length of the sequences

// Buffer for incoming data
uint8_t buffer[sequenceLength];
size_t bufferIndex = 0;

void setup() {
  MySerial.begin(baudRate, SERIAL_8N1, rxPin, txPin);
  Serial.begin(115200);
  Serial.println("UART Listener Started");
}

void loop() {
  if (MySerial.available()) {
    // Read a byte and add it to the buffer
    uint8_t incomingByte = MySerial.read();
    buffer[bufferIndex] = incomingByte;
    bufferIndex = (bufferIndex + 1) % sequenceLength;

    // Check for sequences
    if (memcmp(buffer, sequenceStart, sequenceLength) == 0) {
      onVacuumStart();
    } else if (memcmp(buffer, sequenceStop, sequenceLength) == 0) {
      onVacuumStop();
    } else if (memcmp(buffer, sequenceCharge, sequenceLength) == 0) {
      onVacuumCharge();
    } else if (memcmp(buffer, sequenceStopCharge, sequenceLength) == 0) {
      onVacuumStopCharging();
    }
  }

  delay(10); // Small delay to avoid CPU overload
}

// Define the action functions
void onVacuumStart() {
  Serial.println("Vacuum has started.");
  // Add your code here
}

void onVacuumStop() {
  Serial.println("Vacuum has stopped.");
  // Add your code here
}

void onVacuumCharge() {
  Serial.println("Vacuum is charging.");
  // Add your code here
}

void onVacuumStopCharging() {
  Serial.println("Vacuum stopped charging.");
  // Add your code here
}
