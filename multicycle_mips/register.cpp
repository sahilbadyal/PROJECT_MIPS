#include "register.h"

void
IrREGISTER::
ir_reg_thread(void)
{
	// Initialize register
	//bool temp;
	data = 0;
	while (true) {
		#ifdef VERBOSE
		cerr << "REGISTER" << endl;
		#endif

		
			// Write data to output
		wait();
		#ifdef VERBOSE
		cerr << "Reg (out): " << data << endl;
		//temp=w.read();
		#endif
		if(w.read()==1) {
			data = in.read();	// Write signal, 
						// read data from input
			#ifdef VERBOSE
			cerr << "Reg (write): " << data << endl;
			#endif
		}
		
		out.write(data);
	
	}
	
}

void
REGISTER::
reg_thread(void)
{
	// Initialize register
	data = 0;

	while (true) {
		#ifdef VERBOSE
		cerr << "REGISTER" << endl;
		#endif

		out.write(data);	// Write data to output

		#ifdef VERBOSE
		cerr << "Reg (out): " << data << endl;
		#endif

		wait();
		
		data = in.read();	// Write signal, 
						// read data from input

			#ifdef VERBOSE
			cerr << "Reg (write): " << data << endl;
			#endif
	}
}

