#ifndef MUX_H_INCLUDED
#define MUX_H_INCLUDED

#include "mips.h"

SC_MODULE(MUX) {
	sc_in<  sc_bv<DWORD> >	in0;	// First input
	sc_in<  sc_bv<DWORD> > 	in1;	// Second input
	sc_in<  sc_bv<1> >	sel;	// Selection bit
	sc_out< sc_bv<DWORD> >	out;	// Output
	sc_in <bool>	    clk;

	void mux_thread(void);

	SC_CTOR(MUX) {
		SC_THREAD(mux_thread);
		sensitive << in0;
		sensitive << in1;
		sensitive << sel;
		sensitive << clk;
	}
};

SC_MODULE(MUX2_AWORDREG) {
	sc_in<  sc_bv<AWORDREG> >	in0;	// First input
	sc_in<  sc_bv<AWORDREG> >	in1;	// Second input
	sc_in<  sc_bv<1> >		sel;	// Selection bit
	sc_out< sc_bv<AWORDREG> >	out;	// Output
	sc_in <bool>	    clk;

	void mux2_thread(void);

	SC_CTOR(MUX2_AWORDREG) {
		SC_THREAD(mux2_thread);
		sensitive << in0;
		sensitive << in1;
		sensitive << sel;
		sensitive<<clk;
	}
};

SC_MODULE(MUX4) {
	sc_in<  sc_bv<DWORD> >		in0;	// First input
	sc_in<  sc_bv<DWORD> >		in1;	// Second input
	sc_in<  sc_bv<DWORD> >		in2;	// Third input
	sc_in<  sc_bv<DWORD> > 		in3;	// Fourth input
	sc_in<  sc_bv<2> >		sel;	// Selection bit
	sc_out< sc_bv<DWORD> >		out;	// Output
	sc_in <bool>	    clk;

	void mux4_thread(void);

	SC_CTOR(MUX4) {
		SC_THREAD(mux4_thread);
		sensitive << in0;
		sensitive << in1;
		sensitive << in2;
		sensitive << in3;
		sensitive << sel;
		sensitive<<clk;
	}
};

#endif
