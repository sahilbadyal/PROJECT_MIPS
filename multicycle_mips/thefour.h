#ifndef THE_FOUR_H_INCLUDED
#define THE_FOUR_H_INCLUDED

#include "mips.h"

SC_MODULE(THE_FOUR) {
	sc_in<bool>	clk;
	sc_out< sc_bv<DWORD> > out;	// Result

	void four_thread(void);

	// Constructor
	SC_CTOR(THE_FOUR) {
		SC_THREAD(four_thread);
		sensitive<<clk.pos();
	}
};

#endif
