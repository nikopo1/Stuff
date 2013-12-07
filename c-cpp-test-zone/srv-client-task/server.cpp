#include "server.h"

void Server::registerDevice(Device &dev, unsigned int port)
{
	devices[port] = &dev;
}

void Server::send(unsigned int port, unsigned int msgType,
		const std::string &msg)
{
	if(devices.find(port) != devices.end())
		devices[port]->processMessage(msgType, msg);
}

void Server::broadcast(unsigned int excludePort, unsigned int msgType,
		const std::string &msg)
{
	std::map<unsigned int, Device*>::iterator it;
	for(it = devices.begin(); it != devices.end(); ++it)
		if(it->first != excludePort)
			it->second->processMessage(msgType, msg);
}
