#include "device.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

bool Device::handleCommonMessage(unsigned int msgType, const std::string &msg)
{
	unsigned int dest_port;
	std::stringstream ss;
	std::string resp_msg;

	switch(msgType) {
	case 0: /* print to console */
		std::cout << "[" << name << "]: " << msg << std::endl;
		break;
	case 1: /*identify inquire */
		std::istringstream(msg) >> dest_port;
		ss << port << ":" << name; 
		resp_msg = ss.str();
		/* send response to inquirer */
		server.send(dest_port, 2, resp_msg);
		break;
	default:
		/* message is not a common type */
		return false;
	}

	return true;
}

void Dev1::processMessage(unsigned int msgType, const std::string &msg)
{
	std::ostringstream oss;
	std::stringstream ss;
	std::string portstr, idmsg;

	if( !handleCommonMessage(msgType, msg) ) {
		switch(msgType) {
		case 2:
			if(findFirst) {
				/* note first device to respond */
				std::istringstream(msg) >> firstDevicePort;
				findFirst = false;
				/* construct our identity message */
				ss << port << ":" << name; 
				idmsg = ss.str();
				/* print this particular device */
				server.send(firstDevicePort, 0, idmsg);
				/* printer should also print itself */
				server.send(firstDevicePort, 0, msg);
			} else {
				server.send(firstDevicePort, 0, msg);
			}
			break;
		case 3:
			findFirst = true;
			oss << port;
			portstr = oss.str();
			server.broadcast(port, 1, portstr); 
			break;
		default:
			/* msgType > 3 ; unknown type */
			break;
		}
	}
}

void Dev2::processMessage(unsigned int msgType, const std::string &msg)
{
	if( !handleCommonMessage(msgType, msg) ) {
		switch(msgType) {
		case 2: /* inquire reply */
			break;
		case 3:
			server.broadcast(port, 3, "");
			break;
		default:
			/* msgType > 3 ; unknown type */						
			break;
		}
	}
}

void Dev3::processMessage(unsigned int msgType, const std::string &msg)
{
	if(verbose)
		std::cout << "[" << name << " (verbose)]: " << msg << std::endl;
	
	if( !handleCommonMessage(msgType, msg) ) {
		switch(msgType) {
		case 2: /* inquire reply */
			break;
		case 3:
			verbose = true;
			break;
		case 4:
			verbose = false;
			break;
		default:
			/* msgType > 4 ; unknown type */			
			break;
		}
	}
}
