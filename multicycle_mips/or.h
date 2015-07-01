#ifndef OR_H_INCLUDED
#define OR_H_INCLUDED

#include "mips.h"

SC_MODULE(OR) {
	sc_in<  sc_bv<1> > a;	// First operand
	sc_in<  sc_bv<1> > b;	// Second operand
	sc_out< sc_bv<1> > r;	// Result
	sc_in <bool>	    clk;

	void or_thread(void);

	// Constructor
	SC_CTOR(OR) {
		SC_THREAD(or_thread);
		sensitive << a;
		sensitive << b;
		sensitive<<clk.pos();
	}
};

#endif
