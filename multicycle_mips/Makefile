SRCS 		=  alu.cpp aluctrl.cpp thefour.cpp and.cpp or.cpp ctrl.cpp main.cpp \
		mux.cpp ram.cpp register.cpp registerfile.cpp  \
		shift.cpp signextend.cpp decoder.cpp appender.cpp 

OBJS 		= $(SRCS:%.cpp=%.o)
DEPS		= $(SRCS:%.cpp=%.d)

SYSTEMC 	= /usr/local/systemc230

CXX		= g++
CXXFLAGS	= -Wall -ansi -g -O0 -Di386 
INCLUDES 	= -I $(SYSTEMC)/include

LD		= $(CXX)
LDFLAGS 	= $(CXXFLAGS)

LIBS		= -L$(SYSTEMC)/lib-linux64 -lsystemc -Wl,-rpath,/usr/local/systemc230/lib-linux64

PROGRAM 	= mips

default:	$(PROGRAM)

$(PROGRAM):	$(OBJS) $(DEPS)
		$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o ./$@
		
test:		$(PROGRAM)
		./$<
		
clean:; 	rm -rf $(PROGRAM) *.o core* *.d *.vcd *.dump

# Cancel implicit rule
%.o:		%.cpp

%.o:		%.cpp %.d
		$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.d: 		%.cpp
		@ echo Making dependencies for $<
		@ g++ -MM $(INCLUDES) $< | sed 's#: # $*.d : #1' > $@

# Include dependency files .d
ifneq ("$(wildcard *.d)","")
  include $(wildcard *.d)
endif
