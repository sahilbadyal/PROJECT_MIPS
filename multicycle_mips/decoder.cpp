#include "decoder.h"

void
DECODER::
decoder_thread(void)
{
	sc_uint<DWORD>		t_instr;
	sc_uint<AWORDREG>	t_instr_25_21;
	sc_uint<AWORDREG>	t_instr_20_16;
	sc_uint<AWORDREG>	t_instr_15_11;
	sc_uint<6>		t_instr_31_26;
	sc_uint<6>		t_instr_5_0;
	sc_uint<SIGNEXTENDBIT>	t_instr_15_0;
	sc_uint<26>		t_instr_25_0;

	while (true) {

		
		if(w.read()==1){
		// Read input
		t_instr = instr.read();
		// Decode instruction
		t_instr_31_26 = t_instr.range(31,26);
		t_instr_25_21 = t_instr.range(25,21);
		t_instr_20_16 = t_instr.range(20,16);
		t_instr_15_11 = t_instr.range(15,11);
		t_instr_15_0 = t_instr.range(15,0);
		t_instr_5_0 = t_instr.range(5,0);
		t_instr_25_0 = t_instr.range(25,0);

		// Produce output
		instr_31_26.write(t_instr_31_26);
		instr_25_21.write(t_instr_25_21);
		instr_20_16.write(t_instr_20_16);
		instr_15_11.write(t_instr_15_11);
		instr_15_0.write(t_instr_15_0);
		instr_5_0.write(t_instr_5_0);
		instr_25_0.write(t_instr_25_0);
		}
		wait();
	}
}
