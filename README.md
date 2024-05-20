# Tesvor x500 with Matter over Thread

<img src="https://www.matteralpha.com/media/cache/resolve/full/thread-logo.webp" height='100px'> <img src="https://upload.wikimedia.org/wikipedia/commons/f/fd/Matter_logo.jpg" height='100px'>

## 🚧 Work in Progress. Contributions welcome 🚧
 **Warning**
Matter 1.2 support is needed to use this. Currently no major Smarthome platform supports this. This will lead to a error similar to this:
*"This device is currently not supported in the Home App"*

<img width="400" alt="State Machine" src="https://github.com/devasworski/Tesvor_x500-Matter_over_Thread/assets/34026653/1d1d448c-9261-4d6e-9f06-82ced4252290">


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
<img width="1002" alt="State Machine" src="https://github.com/devasworski/Tesvor_x500-Matter_over_Thread/assets/34026653/96f7bd0f-c40f-49b8-b652-a36c1b02c4ba">

### Related Topcis
- Tasmoto for Tesvor x500: https://github.com/arendst/Tasmota/discussions/19554

### Matter 1.2 Device Library Specification Chapter 12. Robotic Device Types

#### 12.1. Robotic Vacuum Cleaner Device Type
This section defines conformance for the Robotic Vacuum Cleaner device type.

#### 12.1.1. Revision History
This is the revision history for this document.

| Revision | Description                         |
|----------|-------------------------------------|
| 1        | [Initial release of this document](https://csa-iot.org/wp-content/uploads/2023/10/Matter-1.2-Device-Library-Specification.pdf)    |

#### Classification
| ID     | Device Name              | Superset | Class | Scope    |
|--------|--------------------------|----------|-------|----------|
| 0x0074 | Robotic Vacuum Cleaner   |          |Simple | Endpoint |

#### Conditions
Please see the Base Device Type definition for conformance tags.

#### 12.1.4. Cluster Requirements
Each endpoint supporting this device type SHALL include these clusters based on the conformance defined below.


| ID     | Cluster                  | Client/Server | Quality | Conformance |
|--------|--------------------------|---------------|---------|-------------|
| 0x0003 | Identify                 | Server        |         |M            |
| 0x0054 | RVC Run Mode             | Server        |         |M            |
| 0x0055 | RVC Clean Mode           | Server        |         |O            |
| 0x0061 | RVC Operational State    | Server        |         |M            |

#### 12.1.5. Element Requirements
The table below lists qualities and conformance that override the cluster specification requirements. A blank table cell means there is no change to that item and the value from the cluster specification applies.

| ID     | Cluster                | Element       | Name   | Constraint | Access | Conformance |
|--------|------------------------|---------------|--------|------------|--------|-------------|
| 0x0054 | RVC Run Mode           | Feature       | OnOff  |            |        | X           |
| 0x0055 | RVC Clean Mode         | Feature       | OnOff  |            |        | X           |
| 0x0061 | RVC Operational State  | Command       | Start  |            |        | X           |
| 0x0061 | RVC Operational State  | Command       | Stop   |            |        | X           |

### Matter 1.2 Application Cluster Specification
[Chapter 7. Robots](Chapter_7_Robots-Matter_Application%20Clusters%20-%20Matter-1.2-Application-Cluster-Specification.pdf)
