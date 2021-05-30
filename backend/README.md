To generate Python code to interact with the files in orders folder:
Install grpcio-tools: pip install grpcio-tools

To run the code locally, install the dependencies into a virtual env:
For Linux/macOS, run these commands:

$ python3 -m venv venv
$ source venv/bin/activate  # Linux/macOS only
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
$ python -m pip install -r marketplace/requirements.txt