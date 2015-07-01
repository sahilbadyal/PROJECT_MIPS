#ifndef SHIFTJ_H_INCLUDED
#define SHIFTJ_H_INCLUDED

#include "mips.h"

SC_MODULE(SHIFTJLEFT) {
	sc_in< sc_bv<26> >	in;
	sc_out< sc_bv<28> >	out;

	void shiftjleft_thread(void);

	SC_CTOR(SHIFTJLEFT) {
		SC_THREAD(shiftjleft_thread);
		sensitive << in;
	}
};

#endif
