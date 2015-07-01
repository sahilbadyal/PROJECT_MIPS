#ifndef REGISTER_H_INCLUDED 
#define REGISTER_H_INCLUDED

#include "mips.h"

SC_MODULE(IrREGISTER) {
	sc_in<  sc_bv<DWORD> >	in;	// Data input
	sc_in<  sc_bv<1> >	w;	// Write control signal
	sc_out< sc_bv<DWORD> >	out;	// Data output
	sc_in<  bool >		clk;	// Clock

	void ir_reg_thread(void);

	sc_uint<DWORD> data;

	SC_CTOR(IrREGISTER) {
		SC_THREAD(ir_reg_thread);
		sensitive << clk.pos();
		sensitive << w;
	}
};

SC_MODULE(REGISTER) {
	sc_in<  sc_bv<DWORD> >	in;	// Data input
	sc_out< sc_bv<DWORD> >	out;	// Data output
	sc_in<  bool >		clk;	// Clock

	void reg_thread(void);

	sc_bv<DWORD> data;

	SC_CTOR(REGISTER) {
		SC_THREAD(reg_thread);
		//sensitive << in;
		sensitive << clk.pos();
	}
};



#endif
