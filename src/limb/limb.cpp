#include "limb/wrap.h"

int main() {
	limb::APP_STATE retval = limb::APP_STATE::QUIT;
	do {
		retval = limb::runlimb(retval);
	} while (retval != limb::APP_STATE::QUIT);

	return 0;
}
