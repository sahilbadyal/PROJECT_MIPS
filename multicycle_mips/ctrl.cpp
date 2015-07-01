#include "ctrl.h"

void
CTRL::
ctrl_thread(void)
{
	sc_uint<6> opcode;
	
	State = -1;

	while (true) {
		
		#ifdef VERBOSE
		cerr << "CTRL" << endl;
		#endif 
		MemRead.write(0);
		ALUSrcA.write(0);
		IorD.write(0);
		IRWrite.write(0);
		ALUSrcB.write(0x0);
		ALUOp.write(0x0);
		PCWrite.write(0);
		PCSource.write(0x0);
		PCWriteCond.write(0);
		MemWrite.write(0);
		MemtoReg.write(0);
		RegDst.write(0);
		RegWrite.write(0);
		// Read the input
		opcode = Opcode.read();
		state.write(State);

		switch(State)
		{
			case 0 : //first step
					MemRead.write(1);
					ALUSrcA.write(0);
					IorD.write(0);
					IRWrite.write(1);
					ALUSrcB.write(0x1);
					ALUOp.write(0x0);
					PCWrite.write(1);
					PCSource.write(0x0);
					State=1;
					break;
			case 1: //Second step
				ALUSrcA.write(0);
				ALUSrcB.write(0x3);
				ALUOp.write(0x0);
				PCWrite.write(0);
				IRWrite.write(0);

				switch (opcode) {
					case OP_RTYPE:	// R-format instruction
						State=6;
						break;
					case OP_LW:State=2;
						   break;	// lw instruction
					case OP_SW:	// sw instruction
						State=2;
						break;
					case OP_BEQ:	// beq instruction
						State=8;
						break;
					case OP_JMP:
						State=9;
						break;
					}
				break;

			case 2:
				ALUSrcA.write(1);
				ALUSrcB.write(0x2);
				ALUOp.write(0x0);
				switch (opcode) {
					case OP_LW:
						State=3;
						break;	// lw instruction
					case OP_SW:
						State=5;	// sw instruction
						break;
						}
					break;
			case 3:
				MemRead.write(1);
				IorD.write(1);
				State=4;
				break;
			case 4:
				RegDst.write(0);
				RegWrite.write(1);
				MemtoReg.write(1);
				State=0;
				break;
			case 5:
				MemWrite.write(1);
				IorD.write(1);
				State=0;
				break;
			case 6:
				ALUSrcA.write(1);
				ALUSrcB.write(0x0);
				ALUOp.write(0x2);
				State=7;
				break;
			case 7:
				RegDst.write(1);
				RegWrite.write(1);
				MemtoReg.write(1);
				State=0;
				break;
			case 8:
				ALUSrcA.write(1);
				ALUSrcB.write(0x0);
				ALUOp.write(0x1);
				PCWriteCond.write(1);
				PCSource.write(0x1);
				State=0;
				break;
			case 9:
				PCWrite.write(1);
				PCSource.write(0x2);
				State=0;
				break;
			default : State = 0;
				break;
		}
		
		wait();
		
	}
}
