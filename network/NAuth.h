#ifndef ORGANIZER_NAUTH_H
#define ORGANIZER_NAUTH_H

#include <storage/Storage.h>
#include "Network.h"


class NAuth {
	Storage *storage;
	SSecure *secure;
	Network netw;

public:
	NAuth();

	void newRegister();
};


#endif //ORGANIZER_NAUTH_H
