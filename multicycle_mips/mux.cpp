#include "mux.h"

void
MUX::
mux_thread(void)
{
	sc_bv<DWORD> data;
	sc_uint<1>   select;

	while (true) {
		#ifdef VERBOSE
		cerr << "MUX" << endl;
		#endif
		select = sel.read();
		// Read correct input
		if(select == 0)
			data = in0.read();
		else
			data = in1.read();

		// Write output
		out.write(data);

		// wait for new event
		wait();
	}
}

void
MUX2_AWORDREG::
mux2_thread(void)
{
	sc_bv<AWORDREG> data;
	sc_uint<1>   select;

	while (true) {
		#ifdef VERBOSE
		cerr << "MUX" << endl;
		#endif
		select = sel.read();
		if(select == 0)
			data = in0.read();
		else
			data = in1.read();

		out.write(data);

		// wait for new event
		wait();
	}
}

void
MUX4::
mux4_thread(void)
{
	sc_bv<DWORD> data;
	sc_uint<2>   select;

	while (true) {
		#ifdef VERBOSE
		cerr << "MUX" << endl;
		#endif

		select=sel.read();
		switch(select)
		{
			case 0 : data=in0.read();
				break;
			case 1 : data=in1.read();
				break;
			case 2 : data=in2.read();
				break;
			case 3 : data=in3.read();
				break;
		}

		out.write(data);

		// wait for new event
		wait();
	}
}
