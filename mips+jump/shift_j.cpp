#include"shift_j.h"

void
SHIFTJLEFT::
shiftjleft_thread(void)
{
	sc_bv<26> a;
	sc_bv<28> b;

	while (true) {
		#ifdef VERBOSE
		cerr << "SHIFT" << endl;
		#endif

		a = in.read();
		
		b = a;
		b = b << SHIFTBIT;
		
		out.write(b);

		#ifdef VERBOSE
		cerr << "Shifter: " << a;
		cerr << " -> ";
		cerr << b << endl;
		#endif

		wait();
	}
}
