#ifndef SHIFT_H_INCLUDED
#define SHIFT_H_INCLUDED

#include "mips.h"

SC_MODULE(SHIFTRIGHT) {
	sc_in< sc_bv<DWORD> >	in;
	sc_out< sc_bv<DWORD> >	out;

	void shiftright_thread(void);

	SC_CTOR(SHIFTRIGHT) {
		SC_THREAD(shiftright_thread);
		sensitive << in;
	}
};

SC_MODULE(SHIFTLEFT) {
	sc_in< sc_bv<DWORD> >	in;
	sc_out< sc_bv<DWORD> >	out;
	sc_in <bool>	    clk;

	void shiftleft_thread(void);

	SC_CTOR(SHIFTLEFT) {
		SC_THREAD(shiftleft_thread);
		sensitive << in;
		sensitive<<clk.pos();
	}
};

SC_MODULE(SHIFTJLEFT) {
	sc_in< sc_bv<26> >	in;
	sc_out< sc_bv<28> >	out;
	sc_in <bool>	    clk;

	void shiftjleft_thread(void);

	SC_CTOR(SHIFTJLEFT) {
		SC_THREAD(shiftjleft_thread);
		sensitive << in;
		sensitive<<clk.pos();
	}
};

#endif
