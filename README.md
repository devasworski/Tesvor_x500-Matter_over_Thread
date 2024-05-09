# Tesvor x500 with Matter over Thread

<img src="https://www.matteralpha.com/media/cache/resolve/full/thread-logo.webp" height='100px'> <img src="https://upload.wikimedia.org/wikipedia/commons/f/fd/Matter_logo.jpg" height='100px'>

## 🚧 Work in Progress. Contributions welcome 🚧

### Goal:
Replace the Wifi Chip within a Tesvor x500 with a ESP32 H2 to support Matter over Thread.

### Matter State Machine:
Not all States and state switches that are used within the matter protocol for Vaccumes are supported.
Oiginal can be found here: https://github.com/project-chip/connectedhomeip/tree/e079364d2f18aae6c4718cd7074ea62fae3f0360/examples/rvc-app
I could find the following information being communicated to the wifi chip:
- Wake up
- Vacuum start
- Vacuum stop
- Charge start
- Stops Charging
- Power Mode
- Quite Mode
- Battery Percentage
No information about the docking status could be found.

This would allow for follwong state State Machine within Matter:
<img width="1002" alt="Pasted Graphic" src="https://github.com/devasworski/Tesvor_x500-Matter_over_Thread/assets/34026653/96f7bd0f-c40f-49b8-b652-a36c1b02c4ba">

### Related Topcis
- Tasmoto for Tesvor x500: https://github.com/arendst/Tasmota/discussions/19554
