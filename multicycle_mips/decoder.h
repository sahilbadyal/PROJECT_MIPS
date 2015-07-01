#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "mips.h"

SC_MODULE(DECODER) {
	sc_in<  sc_bv<DWORD> >	instr;
	sc_in<  sc_bv<1> >      w;
	sc_out< sc_bv<6> >	instr_31_26;
	sc_out< sc_bv<5> >	instr_25_21;    
	sc_out< sc_bv<5> >	instr_20_16;    
	sc_out< sc_bv<5> >	instr_15_11;    
	sc_out< sc_bv<16> >	instr_15_0;
	sc_out< sc_bv<6> >	instr_5_0;
	sc_out< sc_bv<26> >	instr_25_0;

	void decoder_thread(void);

	SC_CTOR(DECODER) {
		SC_THREAD(decoder_thread);
		sensitive << instr;
		sensitive << w;
	}
};

#endif
