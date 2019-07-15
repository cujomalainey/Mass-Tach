protoc -omessages.pb --csharp_out=../Server/Protobufs messages.proto
python3 $(which nanopb_generator.py) messages.pb -D ../Sensor-Relay/src
