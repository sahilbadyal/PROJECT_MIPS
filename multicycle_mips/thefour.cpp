#include "thefour.h"

void
THE_FOUR::
four_thread(void)
{
	sc_uint<DWORD> r_t;

	while(true) {
		#ifdef VERBOSE
		cerr << "FOUR" << endl;
		#endif

		r_t=4;

		// Set result on output
		out.write(r_t);

		// Wait for new event
		wait();
	}
}
