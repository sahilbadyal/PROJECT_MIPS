#ifndef CTRL_H_INCLUDED
#define CTRL_H_INCLUDED

#include "mips.h"

SC_MODULE(CTRL) {
	//external ports
	sc_in<  sc_bv<6> >	Opcode;	// Instruction bits [31-26]
	sc_in<bool> 		clk;
	
	sc_out< sc_bv<1> >	RegDst;
	sc_out< sc_bv<1> >	IorD;
	sc_out< sc_bv<1> >	MemRead;
	sc_out< sc_bv<1> >	MemtoReg;
	sc_out< sc_bv<1> >	IRWrite;
	sc_out< sc_bv<1> >	PCWrite;
	sc_out< sc_bv<1> >	PCWriteCond;
	sc_out< sc_bv<1> >	MemWrite;
	sc_out< sc_bv<1> >	ALUSrcA;
	sc_out< sc_bv<1> >	RegWrite;

	sc_out< sc_bv<2> >	ALUOp;
	sc_out< sc_bv<2> >	ALUSrcB;
	sc_out< sc_bv<2> >	PCSource;

	sc_signal< sc_bv<4> >	state;

	//State register
	
	sc_uint<4>	State;

	void ctrl_thread(void);

	// Constructor
	SC_CTOR(CTRL) {
		SC_THREAD(ctrl_thread);
		sensitive << clk.pos();	
		//sensitive << Opcode;	
	}
};

#endif
