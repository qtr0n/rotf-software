# Software Architecture
Our Backend employs a 3-Microservice Scalable Architecture with a [HiveMQ](https://www.hivemq.com/) Message Broker for transferring the data using the MQTT Protocol as per the following System Architecture:

<p align="center">
<img src="https://github.com/theobscuredev/rotf-software/blob/main/backend/assets/Architecture.png">
</p>

The customer can give an order using the Chatbot User Interface which sends a request directly to the Main Server(Master) powered via Flask. After updating the database, a response is sent back to the user containing an estimated time for the food delivery computed by our Scheduling Algorithm. Simultaneously, the Main Server also sends a response which is the 'Slot' parameter to the interconnected Chatbot Server which is then used for completion of the order before appending the same in the database. 

A Subscription server is used to subscribe to the topics from the IoT devices (which include the on-board sensors), and is routed to the Master. HiveMQ is used as a Message Broker, a relay-server for the published topics. Publish-Subscribe process occurs between the HiveMQ Clients and the actual broker. User Authentication will be used for Data Security.

RPC(Remote Procedure Call) and Protobufs are used for Intra-Micro Service Communication which helps reduce the network latency and prevent the exposure of multiple API points.

The entire architecture is easily scalable as by creating multiple instances of the Chatbot Server and by using Load Balancers, the entire system can be horizontally scaled to handle multiple requests.

## Execution Steps:
Refer the [HiveMQ documentation](https://www.hivemq.com/docs/hivemq/4.6/user-guide/install-hivemq.html) for installation and setting up the Broker Server.

## Steps to run the protobufs:

To generate Python code to interact with the files in orders folder:
Install grpcio-tools: pip install grpcio-tools

To run the code locally, install the dependencies into a virtual env:
For Linux/macOS, run these commands:

$ python3 -m venv venv

$ source venv/bin/activate  

(venv) $ python -m pip install -r requirements.txt

For Windows:
C:\ python -m venv venv

C:\ venv\Scripts\activate.bat

(venv) C:\ python -m pip install -r requirements.txt

To generate Python code from the protobufs, run the following:
$ cd recommendations

$ python -m grpc_tools.protoc -I ../protobufs --python_out=. \ --grpc_python_out=. ../protobufs/order.proto

Without closing the previous terminal, open a new terminal and run the following command to run the Client-facing Order Microservice:
$ python order.py

To update the virtual environment corresponding to the Master Microservice, run the following command:
$ python -m pip install -r master/requirements.txt
