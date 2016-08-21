#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "server.h"

#include <string>
#include <iostream>

class Server;

class Device {
protected:
	/**
	 * The port under which the device is registered to the server.
	 */
	unsigned int port;

	/**
	 * The name of the device.
	 */
	std::string name;

	/**
	 * A reference to the server.
	 */
	Server &server;
public:
	/**
	 * Constructor for a device with the following initializers.
	 * @_port the port used to register on the server
	 * @_name the name of the device
	 * @_server a reference to the server
	 */
	Device(unsigned int _port, std::string _name, Server &_server) : 
			port(_port),
			name(_name),
			server(_server) { }
	virtual ~Device(void) { };

	/**
	 * Shall be implemented by the derived devices for specific processing
	 * when a message is received.
	 * @msgType the type of the message to be processed
	 * @msg the contents of the message
	 */
	virtual void processMessage(unsigned int msgType, const std::string &msg) = 0;

protected:
	/**
	 * Handles the common cases for all the devices for type 0, 1 and 2
	 * messages.
	 * @msgType the type of the message to be processed
	 * @msg the contents of the message
	 */
	bool handleCommonMessage(unsigned int msgType, const std::string &msg);
};

class Dev1 : public Device {
	/**
	 * Boolean value to mark the first device to answer when identifying
	 * all the devices.
	 */
	bool findFirst;

	/**
	 * The port of the first device that answered when identifying all the
	 * devices.
	 */
	unsigned int firstDevicePort;
public:
	/**
	 * Constructor for a Dev1 class with the same parameters as the
	 * base class.
	 * @_port the port used to register on the server
	 * @_name the name of the device
	 * @_server a reference to the server
	 */
	Dev1(unsigned int _port, std::string _name, Server &_server) :
			Device(_port, _name, _server),
			findFirst(0) { };
	~Dev1(void) { };

	void processMessage(unsigned int msgType, const std::string &msg);
};

class Dev2 : public Device {
public:
	/**
	 * Constructor for a Dev2 class with the same parameters as the
	 * base class.
	 * @_port the port used to register on the server
	 * @_name the name of the device
	 * @_server a reference to the server
	 */
	Dev2(unsigned int _port, std::string _name, Server &_server) :
			Device(_port, _name, _server) { };
	~Dev2(void) { };

	void processMessage(unsigned int msgType, const std::string &msg);
};
class Dev3 : public Device {
	bool verbose;
public:
	/**
	 * Constructor for a Dev3 class with the same parameters as the
	 * base class.
	 * @_port the port used to register on the server
	 * @_name the name of the device
	 * @_server a reference to the server
	 */
	Dev3(unsigned int _port, std::string _name, Server &_server) :
			Device(_port, _name, _server),
			verbose(false) { };
	~Dev3(void) { };

	void processMessage(unsigned int msgType, const std::string &msg);
};

#endif /* _DEVICE_H_ */
