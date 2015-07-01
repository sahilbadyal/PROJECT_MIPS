#ifndef APPENDER_H
#define APPENDER_H

#include "mips.h"

SC_MODULE(APPENDER)
{
		sc_in< sc_bv<28>    >           jin;
		sc_in< sc_bv<DWORD> >		pin;
		sc_out< sc_bv<DWORD> >		jout;
		sc_in <bool>	    clk;
		
		void appender_thread(void);
		
		// Constructor
	SC_CTOR(APPENDER) {
		SC_THREAD(appender_thread);
		sensitive << jin;
		sensitive << pin;
		sensitive<<clk.pos();
	}
};

#endif
