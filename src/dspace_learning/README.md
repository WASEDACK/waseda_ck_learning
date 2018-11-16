# dspace_learning 

## vocabulary 
- ethernet 以太网
- socket 插座
- plug 插头
- RTW real—time workshop  可以把simulink模型编译成为C代码
- RTI real-time interface  可以把C代码跑在硬件系统上
- CDP control development package 


## Note
- **Vehicle CAN**:
- **ROS**:
- **DIO**:
- **Matlab**      
xlsread() function can import the data from excel files as a matrix.

## questions
1. IP
2. Flash Setup
3. Baudrate:500 kbit/s
4. DIO: 读取刹车灯信息？
5. confirm the dspace development process.

## matlab_file_learing

### dspace settings in simulink
1. **RTI CAN controller setuo**:    
one CAN controller setup block must always be present before your using it.
2. **Ethernet UDP Setup**:     
To initialize the Ethernet interface.    
In Options Page, if you set remote IP address = 0.0.0.0 and port number=0, this socket will listen to any IP and Port.
3. **RTICAN Receive**:      
There must be a CAN controller setup before you use this block.
To receive and decode a CAN message with a particular identifier.
4. **DIO**     
To provide channel-wise read access to a single bit of a digital I/O port.   Digital (High/Low)->1/0
5. **1-D selector**        
read element by index.
6. **   ** 
