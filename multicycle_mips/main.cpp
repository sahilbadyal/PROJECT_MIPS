#include "or.h"
#include "aluctrl.h"
#include "alu.h"
#include "and.h"
#include "ctrl.h"
#include "decoder.h"
#include "mux.h"
#include "ram.h"
#include "registerfile.h"
#include "register.h"
#include "shift.h"
#include "signextend.h"
#include "appender.h"
#include "thefour.h"

int
sc_main(int argc, char* argv[])
{
	sc_report_handler::
	set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

	char stbuf[256];

	// SIGNALS

	// Data signals
	sc_signal< sc_bv<DWORD> >		bus_mux1;
	sc_signal< sc_bv<DWORD> >		bus_mux2;
	sc_signal< sc_bv<DWORD> >		bus_mux3;
	sc_signal< sc_bv<DWORD> >		bus_mux4_1;
	sc_signal< sc_bv<DWORD> >		bus_mux4_2;
	sc_signal< sc_bv<AWORDREG> >		bus_mux4;

	sc_signal< sc_bv<6> >			bus_decoder_instr_31_26;
	sc_signal< sc_bv<AWORDREG> >		bus_decoder_instr_25_21;
	sc_signal< sc_bv<AWORDREG> >		bus_decoder_instr_20_16;
	sc_signal< sc_bv<AWORDREG> >		bus_decoder_instr_15_11;
	sc_signal< sc_bv<SIGNEXTENDBIT> >	bus_decoder_instr_15_0;
	sc_signal< sc_bv<6> >			bus_decoder_instr_5_0;
	sc_signal< sc_bv<26> >			bus_decoder_instr_25_0;


	sc_signal< sc_bv<DWORD> >		bus_pc_from;
	
	sc_signal< sc_bv<DWORD> >		bus_mem_from;
	
	//sc_signal< sc_bv<DWORD> >		bus_ir_from;

	sc_signal< sc_bv<DWORD> >		bus_shiftleft_from;

	sc_signal< sc_bv<DWORD> >		bus_signextend_from;
	
	sc_signal< sc_bv<DWORD> >		bus_a_reg_from;
	
	sc_signal< sc_bv<DWORD> >		bus_memdr_from;

	sc_signal< sc_bv<28> >			bus_shiftjleft_from;
	
	sc_signal< sc_bv<DWORD> >		bus_b_reg_from;

	sc_signal< sc_bv<DWORD> >		bus_appender_from;		
	
	sc_signal< sc_bv<DWORD> >		bus_alu_result;
	sc_signal< sc_bv<1> >			bus_alu_zero;
	sc_signal< sc_bv<DWORD> >		bus_aluout;
	sc_signal< sc_bv<1> >			bus_and1;
	sc_signal< sc_bv<1> >			bus_or;

	sc_signal< sc_bv<3> > 			bus_aluctrl;
	
	sc_signal< sc_bv<DWORD> > 		bus_4;
	sc_signal< sc_bv<DWORD> >		bus_reg_read1;

	sc_signal< sc_bv<DWORD> >		bus_reg_read2;

	// Control signals
	sc_signal< sc_bv<1> >		bus_ctrl_regdst;
	sc_signal< sc_bv<1> >		bus_ctrl_alusrc_a;
	sc_signal< sc_bv<1> >		bus_ctrl_memread;
	sc_signal< sc_bv<1> >		bus_ctrl_memtoreg;
	sc_signal< sc_bv<1> >		bus_ctrl_iord;
	sc_signal< sc_bv<1> >		bus_ctrl_memwrite;
	sc_signal< sc_bv<1> >		bus_ctrl_regwrite;
	sc_signal< sc_bv<1> >		bus_ctrl_irwrite;
	sc_signal< sc_bv<1> >		bus_ctrl_pcwrite;
	sc_signal< sc_bv<1> >		bus_ctrl_pcwritecond;

	sc_signal< sc_bv<2> >		bus_ctrl_aluop;
	sc_signal< sc_bv<2> >		bus_ctrl_pcsource;
	sc_signal< sc_bv<2> >		bus_ctrl_alusrc_b;


	// MODULES

	IrREGISTER	pc("pc");
	
	//IrREGISTER	ir("ir");
	
	REGISTER	A("A");
	REGISTER	B("B");
	
	REGISTER	alu_out("alu_out");
	REGISTER	memdr("memdr");
	

	AND		and1("and1");
	OR 		or1("or1");

	RAM		mem("memory");		//  memory

	REGFILE		registers("registers");		// Registerfile

	ALU		alu("alu");
	ALUCTRL		aluctrl("aluctrl");

	SIGNEXTEND	signextend("signextend");

	SHIFTLEFT	shiftleft("shiftleft");
	
	SHIFTJLEFT 	shiftjleft("shiftjleft");

	CTRL		ctrl("ctrl");

	THE_FOUR	four("four");

	DECODER		decoder("decoder");
	
	APPENDER	appender("appender");

	MUX		mux1("mux1");
	MUX		mux2("mux2");
	MUX		mux3("mux3");
	MUX2_AWORDREG	mux4("mux4");
	MUX4	mux4_1("mux4_1");
	MUX4  	mux4_2("mux4_2");

	sc_clock	clk("clock", 20);		// Clock

	// CONNECTIONS

	// Program counter
	pc.in(bus_mux4_1);
	pc.out(bus_pc_from);
	pc.w(bus_or);
	pc.clk(clk);

	
	// Mux 1 (add1 or add2)
	mux1.in0(bus_pc_from);
	mux1.in1(bus_aluout);
	mux1.sel(bus_ctrl_iord);
	mux1.out(bus_mux1);
	mux1.clk(clk);
	

	// THE FOUR
	four.clk(clk);
	four.out(bus_4);

	// Shift left 2
	shiftleft.in(bus_signextend_from);
	shiftleft.out(bus_shiftleft_from);
	shiftleft.clk(clk);

	// Sign extend
	signextend.in(bus_decoder_instr_15_0);
	signextend.out(bus_signextend_from);
	signextend.clk(clk);
	
	/*//Instruction register
	ir.in(bus_mem_from);
	ir.w(bus_ctrl_irwrite);
	ir.out(bus_ir_from);
	ir.clk(clk);*/

	// A register
	A.in(bus_reg_read1);
	A.out(bus_a_reg_from);
	A.clk(clk);

	// B register 
	B.in(bus_reg_read2);
	B.out(bus_b_reg_from);
	B.clk(clk);

	//ALU out reg
	alu_out.in(bus_alu_result);
	alu_out.out(bus_aluout);
	alu_out.clk(clk);

	//MEMDR
	memdr.in(bus_mem_from);	
	memdr.out(bus_memdr_from);
	memdr.clk(clk);

	// Decoder (Select correct part of instruction for registerfile)
	decoder.instr(bus_mem_from);
	decoder.instr_31_26(bus_decoder_instr_31_26);
	decoder.instr_25_21(bus_decoder_instr_25_21);
	decoder.instr_20_16(bus_decoder_instr_20_16);
	decoder.instr_15_11(bus_decoder_instr_15_11);
	decoder.instr_15_0(bus_decoder_instr_15_0);
	decoder.instr_5_0(bus_decoder_instr_5_0);
	decoder.instr_25_0(bus_decoder_instr_25_0);
	decoder.w(bus_ctrl_irwrite);

	// Mux 4 (Select address for write to registerfile)
	mux4.in0(bus_decoder_instr_20_16);
	mux4.in1(bus_decoder_instr_15_11);
	mux4.sel(bus_ctrl_regdst);
	mux4.out(bus_mux4);
	mux4.clk(clk);

	// ALU
	alu.a(bus_mux3);
	alu.b(bus_mux4_2);
	alu.r(bus_alu_result);
	alu.z(bus_alu_zero);
	alu.ctrl(bus_aluctrl);
	alu.clk(clk);

	// Mux 2 (alu out or mem data reg)
	mux2.in0(bus_aluout);
	mux2.in1(bus_memdr_from);
	mux2.sel(bus_ctrl_memtoreg);
	mux2.out(bus_mux2);
	mux2.clk(clk);

	// ALU ctrl
	aluctrl.ALUop(bus_ctrl_aluop);
	aluctrl.functionCode(bus_decoder_instr_5_0);
	aluctrl.ALUctrl(bus_aluctrl);
	aluctrl.clk(clk);

	// Mux 3 (A reg or pc)
	mux3.in0(bus_pc_from);
	mux3.in1(bus_a_reg_from);
	mux3.sel(bus_ctrl_alusrc_a);
	mux3.out(bus_mux3);
	mux3.clk(clk);

	//MUX 4_1 (jump or aluout or aluresult)
	mux4_1.in0(bus_alu_result);
	mux4_1.in1(bus_aluout);
	mux4_1.in2(bus_appender_from);
	mux4_1.in3(bus_4);
	mux4_1.sel(bus_ctrl_pcsource);
	mux4_1.out(bus_mux4_1);
	mux4_1.clk(clk);

	//Mux 4_2(B reg or 4 or signextend or shiftleft 2)
	mux4_2.in0(bus_b_reg_from);
	mux4_2.in1(bus_4);
	mux4_2.in2(bus_signextend_from);
	mux4_2.in3(bus_shiftleft_from);
	mux4_2.sel(bus_ctrl_alusrc_b);
	mux4_2.out(bus_mux4_2);
	mux4_2.clk(clk);

	// AND
	and1.a(bus_alu_zero);
	and1.b(bus_ctrl_pcwritecond);
	and1.r(bus_and1);
	and1.clk(clk);

	//OR
	or1.a(bus_and1);
	or1.b(bus_ctrl_pcwrite);
	or1.r(bus_or);
	or1.clk(clk);

	//shift jump left
	shiftjleft.in(bus_decoder_instr_25_0);
	shiftjleft.out(bus_shiftjleft_from);
	shiftjleft.clk(clk);

	// APPENDER 
	appender.jin(bus_shiftjleft_from);
	appender.pin(bus_pc_from);
	appender.jout(bus_appender_from);
	appender.clk(clk);

	// Registerfile
	registers.r_addr_reg1(bus_decoder_instr_25_21);
	registers.r_addr_reg2(bus_decoder_instr_20_16);
	registers.w_addr_reg(bus_mux4);
	registers.r_data_reg1(bus_reg_read1);
	registers.r_data_reg2(bus_reg_read2);
	registers.w_data_reg(bus_mux2);
	registers.w(bus_ctrl_regwrite);
	registers.clk(clk);

	// Data memory
	mem.a_read(bus_mux1);
	mem.d_read(bus_mem_from);					
	mem.d_write(bus_b_reg_from);
	mem.w(bus_ctrl_memwrite);
	mem.r(bus_ctrl_memread);
	mem.clk(clk);


	// Controller
	ctrl.Opcode(bus_decoder_instr_31_26);
	ctrl.RegDst(bus_ctrl_regdst);
	ctrl.ALUSrcA(bus_ctrl_alusrc_a);
	ctrl.MemRead(bus_ctrl_memread);
	ctrl.MemtoReg(bus_ctrl_memtoreg);
	ctrl.ALUOp(bus_ctrl_aluop);
	ctrl.MemWrite(bus_ctrl_memwrite);
	ctrl.ALUSrcB(bus_ctrl_alusrc_b);
	ctrl.RegWrite(bus_ctrl_regwrite);
	ctrl.IorD(bus_ctrl_iord);
	ctrl.PCSource(bus_ctrl_pcsource);
	ctrl.PCWriteCond(bus_ctrl_pcwritecond);
	ctrl.PCWrite(bus_ctrl_pcwrite);
	ctrl.IRWrite(bus_ctrl_irwrite);
	ctrl.clk(clk);	
	

	// INITIALIZATION
 
	mem.ram_init("mips.ram");

	// TRACING

	sc_trace_file* tf;
	tf = sc_create_vcd_trace_file("mul_mips");

	// Signals
	sc_trace(tf, clk,			"clock");
	sc_trace(tf, bus_memdr_from,		"bus_memdr_from");
	//sc_trace(tf, bus_ir_from,		"bus_ir_from");
	sc_trace(tf, bus_mux1,			"bus_mux1");
	sc_trace(tf, bus_mux2,			"bus_mux2");
	sc_trace(tf, bus_mux3,			"bus_mux3");
	sc_trace(tf, bus_mux4,			"bus_mux4");
	sc_trace(tf, bus_mux4_1,		"bus_mux4_1");
	sc_trace(tf, bus_mux4_2,		"bus_mux4_2");
	sc_trace(tf, bus_pc_from,		"bus_pc_from");
	sc_trace(tf, bus_shiftleft_from,	"bus_shiftleft_from");
	sc_trace(tf, bus_shiftjleft_from,	"bus_shiftjleft_from");
	sc_trace(tf, bus_signextend_from,	"bus_signextend_from");
	sc_trace(tf, bus_mem_from,		"bus_mem_from");
	sc_trace(tf, bus_alu_result,		"bus_alu_result");
	sc_trace(tf, bus_alu_zero,		"bus_alu_zero");
	sc_trace(tf, ctrl.state,		"state");
	sc_trace(tf, bus_reg_read1,		"bus_reg_read1");
	sc_trace(tf, bus_reg_read2,		"bus_reg_read2");
	sc_trace(tf, bus_ctrl_regdst,		"bus_ctrl_regdst");
	sc_trace(tf, bus_ctrl_iord,		"bus_ctrl_iord");
	sc_trace(tf, bus_ctrl_memread,		"bus_ctrl_memread");
	sc_trace(tf, bus_ctrl_memtoreg,		"bus_ctrl_memtoreg");
	sc_trace(tf, bus_ctrl_irwrite,		"bus_ctrl_irwrite");
	sc_trace(tf, bus_ctrl_pcsource,		"bus_ctrl_pcsource");
	sc_trace(tf, bus_ctrl_pcwrite,		"bus_ctrl_pcwrite");
	sc_trace(tf, bus_ctrl_pcwritecond,	"bus_ctrl_pcwritecond");
	sc_trace(tf, bus_ctrl_alusrc_b,		"bus_ctrl_alusrc_b");
	sc_trace(tf, bus_ctrl_aluop,		"bus_ctrl_aluop");
	sc_trace(tf, bus_aluout,		"bus_aluout");
	sc_trace(tf, bus_a_reg_from,		"bus_a_reg_from");
	sc_trace(tf, bus_b_reg_from,		"bus_b_reg_from");
	sc_trace(tf, bus_ctrl_memwrite,		"bus_ctrl_memwrite");
	sc_trace(tf, bus_ctrl_alusrc_a,		"bus_ctrl_alusrc_a");
	sc_trace(tf, bus_ctrl_regwrite,		"bus_ctrl_regwrite");
	sc_trace(tf, bus_aluctrl,		"bus_aluctrl");
	sc_trace(tf, bus_and1,			"bus_and1");
	sc_trace(tf, bus_or,			"bus_or");
	sc_trace(tf, bus_decoder_instr_31_26,	"bus_decoder_instr_31_26");
	sc_trace(tf, bus_decoder_instr_25_21,	"bus_decoder_instr_25_21");
	sc_trace(tf, bus_decoder_instr_20_16,	"bus_decoder_instr_20_16");
	sc_trace(tf, bus_decoder_instr_15_11,	"bus_decoder_instr_15_11");
	sc_trace(tf, bus_decoder_instr_15_0,	"bus_decoder_instr_15_0");
	sc_trace(tf, bus_decoder_instr_5_0,	"bus_decoder_instr_5_0");
	sc_trace(tf, bus_decoder_instr_25_0,	"bus_decoder_instr_25_0");


	for (int i = 0; i < REGSIZE; i++) {
		sprintf(stbuf, "registers.reg(%d)", i);
		sc_trace(tf, registers.rfile[i], stbuf);
	}

	for (int i = 0; i < RAMSIZE; i++) {
		sprintf(stbuf, "memory.mem(%d)", i);
		sc_trace(tf, mem.ramfile[i], stbuf);
	}


	// SIMULATION

	int sim_time = 500;
	if (argc == 2)
		sim_time = atoi(argv[1]);

	sc_start(sim_time, SC_NS);

	sc_close_vcd_trace_file(tf);
	mem.ram_dump("mips_ram.dump");

	return 0;
}
