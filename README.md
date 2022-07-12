# IoTSystem
Basic IoT infrastructure based on the platform NodeMCU (ESP8266), initially designed to monitor and log data from sensors in a plantation, highly scalable.

Background:

Developed as my gratuation project for my Electronics & Programming couse in high school, this team project was proposed as a challenge with the objective of being a device that could be brought to reality to help the community and with the final goal of creating a well-thought, big and complex project that could be inspirational for junior students for them to participe in STEM fields.

The IoT technology was used because it is highly flexible in terms of the purpose it can accomplish. Wether is at home or industrial sector, the IoT architecture has many advantages over a classic system. Things that were important for my team, since we wanted to work with something different and challenging while trying to show the application of it in whatever career the future students choose.    


This IoT system was initially designed as a centralized operation (but easily scalable to a descentralized one, making use of multiple master nodes) with two classes of nodes, which work together to gather, display, upload and work with the sensors' data.


Master Node:

Acts as mainly as a client connecting to the slaves nodes' networks. Once it has gathered all the new information from every slave, it will wait until a new update window is open while uploading the information to a database, displaying the user with the latest information and listening to the physical interface in case the user interacted with the device in-place.


Slave nodes:

Equipped with the actual sensors, the nodes are meant to be implemented around the plantation and be powered up by battery means. Given the restrictions that battery-powered devices present, every certain amount of time the nodes will set up and maintain a wireless local network and a local server that allow master nodes to connect and through a HTTPS_GET, request obtain the latest information of the sensors. After the given amount of time has passed, the slaves nodes with turn off completely to save energy, waking up every X amount of time the user set up by means of a physical clock. It's by the repetition of this cycle that the whole system is capable of saving energy while keeping up with the update rate the user prefered.


Slave code:

![alt text](https://github.com/acanon74/IoTSystem/blob/main/readme_images/CODE_SLAVE.png?raw=true)

Slave circuit:

![alt text](https://github.com/acanon74/IoTSystem/blob/main/readme_images/PROTEUS_CIRCUIT_SLAVE.jpg?raw=true)

Master code:

![alt text](https://github.com/acanon74/IoTSystem/blob/main/readme_images/CODE_MASTER.png?raw=true)

Master circuit:

![alt text](https://github.com/acanon74/IoTSystem/blob/main/readme_images/PROTEUS_CIRCUIT_MASTER.jpg?raw=true)

General network diagram:

![alt text](https://github.com/acanon74/IoTSystem/blob/main/readme_images/Network Implementation.png?raw=true)

Futher things to be implemented:

-Actual interaction with a database system
-Display information in a webpage
-More hardware optimization
-Optimize the network for connection with multiple master nodes simultaneously
-Next iteration of the prototype, covering all the above features

More information:

A document with deeper technical knowledge exists, I am in the process of translating it to english. It will be reference here in the future.

Note: 
Even though the code and circuits work, I am aware of the flaws these have. This is not a perfect implementation of an idea (like if something even can be perfect), that's why I encourage the reader to use implement whatever changes they see practical. However, in the present I am still working on this project, looking forward to improve the code and write more to put something together of a better quality as my knowledge and abilities grow.
