#ifndef _SERVER_H_
#define _SERVER_H_
#include "device.h"

#include <string>
#include <map>

class Device;

class Server {

	/**
	 * A map which contains pairs of ports and associated devices.
	 */
	std::map<unsigned int,Device*> devices;

public:
	Server(void) { }
	~Server(void) { }

	/**
	 * Registers a device to receive messages sent to a specific port.
	 * @dev the device to be registered
	 * @port the port under which the device is registered
	 */
	void registerDevice(Device &dev, unsigned int port);

	/**
	 * Sends a message of a certain type to the device residing at the
	 * given port.
	 * @port the destination port of the message
	 * @msgType the type of the message to be sent
	 * @msg the contents of the message
	 */
	void send(unsigned int port, unsigned int msgType,
			const std::string &msg);
	
	/**
	 *Sends a message of a certain type to all the devices except for the
	 * one residing at the given port.
	 * @port the excluded port
	 * @msgType the type of the massage to be sent
	 * @msg the contents of the message
	 */
	void broadcast(unsigned int excludePort, unsigned int msgType,
			const std::string &msg);
};

#endif /* _SERVER_H_ */
