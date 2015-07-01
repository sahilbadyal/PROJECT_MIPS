#include "appender.h"

void
APPENDER ::
appender_thread(void)
{
		sc_bv<28>    t_jin;
		sc_bv<DWORD> t_pin;
		sc_bv<DWORD> t_jout;
		
		while(true)
		{
				#ifdef VERBOSE
				cerr << "APPENDER_THREAD" << endl;
				#endif

				t_jin = jin.read();
				t_pin = pin.read();

				t_jout = t_jin;

				for(int i= 28; i < 32 ; i++)
				{
						t_jout[i]=t_pin[i];
				}
				
				jout.write(t_jout);
				
				wait();
		}
		
}
