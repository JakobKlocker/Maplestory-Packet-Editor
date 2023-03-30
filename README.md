# Maplestory v62 Packet Editor
Packet editor for Maplestory v62. This is the internal C++ source which sends the packets it logged via TCP to a C# GUI. 
It also listens/recv so the C# GUI can send Packets via the interface. The C# source is not included.

# Feautures

- Send Packets
- Log Send & Recv Packets
- '*' randomizes the Byte
- '[XX]'increases the byte by one, usefull function to find exploits (After sending [00] the next packet will contain [01] and so on)
- Filter out packets when logging
- Marco window to spam packets and/or to send packets in a specific sequence
- Load/Save profile


Ignoring Headers:

<img src="https://user-images.githubusercontent.com/108685788/228879011-b4795788-fee0-4869-93a3-235be4e70fa0.gif" Width="50%" Height="50%"/>


Ignored Header Interface:

<img width="510" alt="PacketEditor_1" src="https://user-images.githubusercontent.com/108685788/228879429-080f6302-b289-4433-990a-146de460b322.png">

Increasing Byte:

<img src="https://user-images.githubusercontent.com/108685788/228883922-b5ec0681-2399-4dbb-935b-0f34142b1f52.gif" Width="50%" Height="50%"/>

Macro Window:

<img src="https://user-images.githubusercontent.com/108685788/228884842-35ee85ca-9199-4ae9-a072-dcd5b185d831.gif" Width="75%" Height="75%"/>

Colaborated with https://github.com/BasBijkerk
