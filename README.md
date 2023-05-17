Arduino RFID Project - Prototype for Animal Model Research
============
This is the initial prototype of an Arduino based RFID reader to be used to monitor the activity level of captive mice being used as research animal models. This device allows researcher to easily quantify how often each mouse enters specific area of the enclosure (e.g., near food/water dispenser) without relying on reviewing video recordings of activity. An Arduino based RFID reader was also a preferred solution since all components of the system are readily available, relatively cheap, and can be reasonably assembled by a researcher at scale. Multiple systems can be connected to a realtime Firebase database via webhook to simplify data aggregation.

---

## System in action:

Here's the system in action! Unique RFID tags are passed over the copper coil, read by the RDM RFID reader, and sent over WIFI to a cloud database via the Particle Photon. Note, these readers are not very precise, so duplicate reads are removed when processing the data.



![reader-in-action](images/reader-in-action.gif)

---

## Components
The system uses 3 components with the R3 used as the main development board, and Photon used to transfer data over WIFI and integrate with cloud infrastructure.
- Arduino R3
- RDM 6300 RFID reader
- Particle Photon MCR (similar to ESP32)


## Arduino R3
The Arduino R3, also known as Arduino Uno R3, is a microcontroller board widely used in electronic prototyping. It features digital and analog input/output pins and built-in communication interfaces. It can be programmed using the Arduino software environment, making it beginner-friendly. The board is popular for its versatility and extensive community support, making it suitable for a wide range of projects, from simple to complex.

## RDM 6300 RFID reader
The RDM 6300 RFID reader is a compact device used to read RFID tags. It operates at 125 kHz and communicates with tags via a simple serial interface. The reader is commonly used in access control, inventory management, and asset tracking applications.

## Particle Photon
The Particle Photon is a small Wi-Fi development board for IoT projects. It has a powerful microcontroller and built-in Wi-Fi, enabling easy internet connectivity. The board is suitable for collecting sensor data, controlling actuators, and communicating with other devices. It supports popular programming languages and offers a secure cloud infrastructure for device management. The Photon is popular among makers and professionals in the IoT field for its compact size and user-friendly features.

## Completed setup:

Note, the R3 and Photon shown powered through the onboard USBs can also be powered through the 5V pins.

![reader-in-action](images/hardware.jpg)

---

## Firebase 

Data is sent to a realtime NoSQL Firebase database with a webhook.

Firebase is a comprehensive mobile and web development platform provided by Google. It offers a wide range of backend services and tools that simplify the process of building and scaling applications. Firebase provides features such as real-time database, authentication, cloud storage, hosting, and cloud functions.

In addition to these features, Firebase provides cloud functions, allowing developers to run serverless backend code in response to events or HTTP requests.


![reader-in-action](images/firebase.jpg)


## License
>You can check out the full license [here](https://github.com/IgorAntun/node-chat/blob/master/LICENSE)

