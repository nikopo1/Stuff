#include "server.h"

int main(void)
{
	Server server;
	Dev1 dev1(1250222, "dev1", server);
	Dev2 dev2(3800, "dev2", server);
	Dev3 dev3(1, "dev1", server);

	server.registerDevice(dev3, 1);
	server.registerDevice(dev2, 3800);
	server.registerDevice(dev1, 1250222);

	server.send(3800, 3, "");

	return 0;
}
