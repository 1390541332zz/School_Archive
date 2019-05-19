module multstyle(
				input 		          		CLOCK_50,
		input 		     [3:0]		KEY,
	output		     [9:0]		LEDR,
	input 		     [9:0]		SW,
	inout 		    [35:0]		GPIO
);

	reg  [15:0] a, next_a;
	reg  [15:0] b, next_b;
   wire [31:0] result;	
	
	wire clk, reset, start;
   
	assign reset = ~KEY[0];
	assign clk = CLOCK_50;	
	assign start = KEY[1];
	
	mymult1 DUT(.clk(clk), 
	            .reset(reset), 
					.a(a), 
					.b(b), 
					.start(start), 
					.result(result), 
					.done(done));
	
	always @(posedge clk)
	begin
		a      <= (reset) ? 32'h0 : next_a;
		b      <= (reset) ? 32'h0 : next_b;
	end

	always @(*)
	begin
		next_a = a + 16'h1;		
		next_b = ~a;
	end
		
	assign LEDR[9:0] = {^result[31:9], result[8:0]};
	
endmodule

// mult1
// area: 130 ALM 64 registers
// minimum slack: 11.948ns (a[9] to r[30])
// latency: 1 cycle

// mult2
// area: 159 ALM 64 registers 
// minimum slack:  9.953ns (a[8] to r[31])
// latency: 1 cycle

// mult3
// area: 67 ALM 147 registers
// minimum slack: 15.937ns (shftb[11] to tmp[9])
// latency: 4 .. 19 cycles

// mult4
// area: 81 ALM  147 registers
// minimum slack: 14.039 ns (tmpa[10] to tmp[24])
// latency: 4 .. 11 cycles