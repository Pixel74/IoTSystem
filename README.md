# IoTSystem
Basic IoT infrastructure based on the platform NodeMCU (ESP8266), initially designed to monitor and log data from sensors in a plantation, highly scalable.


This IoT systems is design as a centralized operation with two classes of nodes.

Slave nodes:

Equipped with the actual sensors, the nodes are meant to be implemented around the plantation and be powered up by battery means, given the restrictions that battery-powered devices present, every certain amount of time the nodes will set up and maintain a wireless local network and a local server that allow master nodes to connect, and through a HTTPS_GET request obtain the current information of the sensors, after the given amount of time has passed, the slaves nodes with turn off completely to save energy, waking up every X amount of time the user set up by means of a physical clock. It's by the repetition of this cycle that the whole system is capable of saving energy while keeping up with the update rate the user prefered.

Master Node:

Acts as mainly as a client connecting to the slaves nodes' networks, once it has gathered all the new information from every slave, it will wait until a new update windows is open while uploading the information to a database, displaying the user with the latest information and listening to the physical buttons in case the user interacted with the device.

Slave code:
Slave circuit:

Master code:
Master circuit:

General network diagram:

Futher things to be implemented:

-Actual interaction with a database system
-Display information in a webpage
-More hardware optimization
-Optimize the network for connection with multiple master nodes simultaneously
-Next iteration of the prototype, covering all the above features

More information:
