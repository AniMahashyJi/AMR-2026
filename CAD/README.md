The mechanical structure of the Autonomous Mobile Robot (AMR) was designed using CAD to ensure proper placement of all electronic and mechanical components.
The chassis is primarily constructed using acrylic plates for the base structure and aluminium X-connectors (standoffs) for vertical support and rigidity. This combination provides a lightweight yet sufficiently strong frame for indoor robotic navigation experiments.

Three-Layer Chassis Architecture

The robot consists of three stacked acrylic plates, each dedicated to specific subsystems of the robot.
Layer 1 – Locomotion Layer (Bottom Layer)

The bottom layer acts as the base of the robot and supports the locomotion system.
Components mounted on this layer include:
1. DC geared motors with integrated wheels
2. Wheel encoders attached to the motors
3. Motor mounting brackets
4. Caster wheel for balance and support

The locomotion system follows a differential drive configuration, where the left and right wheels are controlled independently. This enables the robot to move forward, backward, and rotate in place.
The encoders integrated with the motors provide rotational feedback, which is used to calculate wheel speed and displacement for odometry calculations.


The middle layer is dedicated to the robot’s control electronics and communication components.

Typical components mounted on this layer include:
1. Microcontroller board (such as Arduino Mega)
2. Motor driver modules
3. Power distribution circuits
4. Voltage regulators or buck converters

Separating this layer from the sensor layer helps in organizing wiring and reducing electrical interference.

Layer 3 – Sensor and Processing Layer (Top Layer)

The top layer is designed for mounting sensors and computational hardware.
Components mounted on this layer include:
 1. LiDAR sensor for environmental scanning
 2. Main processing unit (Jetson / Raspberry Pi)
 3. Communication modules

The LiDAR is positioned on the top layer to ensure an unobstructed field of view, allowing accurate environment scanning for mapping and obstacle detection.
