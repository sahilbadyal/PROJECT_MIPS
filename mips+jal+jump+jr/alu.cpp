#include "alu.h"
 
void
ALU::
alu_thread(void)
{
	sc_bv<DWORD>    result;
	sc_bv<1>        zero;
	sc_uint<DWORD>  s;
	sc_uint<DWORD>  t;
	sc_uint<3>      ctrl_t;

	while (true) {
		#ifdef VERBOSE
		cerr << "ALU" << endl;
		#endif

		// Read the inputs
		s = a.read();
		t = b.read();
		ctrl_t = ctrl.read();
		

		// Calculate result using selected operation
		switch (ctrl_t) {
			case ALU_AND:// And
				result = s & t;
				break;
			case ALU_OR:// Or
				result = s | t;
				break;
			case ALU_ADD:// Add
				result = s + t;
				break;
			case ALU_SUB:// Subtract
				result = s - t;
				break;
			case ALU_SLT:// Set-on-less-than
				if (s < t)
					result = 1;
				else
					result = 0;
				break;
			case ALU_JR : // Jump return
				result = s;
				cout<<"I m FINE "<<endl;
				break;
		}

		// Calculate the zero output
		if (result == 0)
			zero = 1;
		else
			zero = 0;

		// Write results to output
		r.write(result);
		z.write(zero);

		// Wait for next event
		wait();
	}
}
