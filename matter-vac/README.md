# Tesvor Thread Controller with Matter
This project describes how to use an ESP32-H2 microcontroller for controlling a Tasvor x500, by replacing its wifi chip.

Main features are:
* Controlling and viewing the status of the robot
* support of Matter over Thread **(not certified)**, thereby compatible with HomeKit, HomeAssistant, Google Home, Alexa, Samsung SmartThings and more.
Missing feature:
* Room Mapping

## Integration in your Smart Home System
As this project uses Matter over Thread, you can easily integrate it scanning the QR code:
 <img src="" alt="QR Code" width="100">
 Config Code: 3497-011-2332

### Change DISCRIMINATOR, PIN & SPAKE2P_SALT

#### New DISCRIMINATOR, PIN

#### New SPAKE2P_SALT & SPAKE2P_VERIFIER

### Regenerate the QR Code

#### Step 1: Setup the CHIP tool

1. **Clone the Matter SDK with submodules:**
   If you haven't already cloned the repository with submodules, do so using the following command:

   ```sh
   git clone --recurse-submodules https://github.com/project-chip/connectedhomeip.git
   cd connectedhomeip
   ```

2. **Initialize and update submodules:**
   If you have already cloned the repository but didn't initialize submodules, run:

   ```sh
   git submodule update --init --recursive
   ```

   This command ensures that all the submodules are properly initialized and updated.


3. **Run the environment setup script:**
   After the submodules are initialized, run the environment setup script again.

   ```sh
   source scripts/activate.sh
   ```

#### Step 2: Generate the QR Code

1. **Generate the Setup Payload:**
   Use the `chip-tool` to generate the setup payload string with your actual values.

   ```sh
   ./out/host/chip-tool payload generate --discriminator <your-discriminator> --pin <your-setup-code>
   ```

   For example:
   ```sh
   ./out/host/chip-tool payload generate --discriminator 3840 --pin 20202021
   ```

2. **Generate the QR Code Image:**
   Use the setup payload string to generate the QR code image.

   ```sh
   ./out/host/chip-tool payload qr "<setup-payload-string>"
   ```

   For example:
   ```sh
   ./out/host/chip-tool payload qr "MT:YNJV74SR40DM8GW93QK8YA28Z30"
   ```