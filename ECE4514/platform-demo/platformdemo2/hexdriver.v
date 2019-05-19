module hexdriver(
		input wire clk,
		input wire reset,
		input wire address,
		input wire write,
		input wire [31:0] writedata,

		output wire [6:0] HEX0,
		output wire [6:0] HEX1,
		output wire [6:0] HEX2,
		output wire [6:0] HEX3,
		output wire [6:0] HEX4,
		output wire [6:0] HEX5
	);

	reg [23:0] hexval, hexvalnext;
	reg mode, modenext;

	reg [23:0] cnt, cntnext;

	seg7decoder H0(hexval[ 3: 0], HEX0);
	seg7decoder H1(hexval[ 7: 4], HEX1);
	seg7decoder H2(hexval[11: 8], HEX2);
	seg7decoder H3(hexval[15:12], HEX3);
	seg7decoder H4(hexval[19:16], HEX4);
	seg7decoder H5(hexval[23:20], HEX5);

	always @(posedge clk)
	if (reset == 1'h1)
	begin
	    cnt    <= 24'h0;
		hexval <= 24'h0;		
		mode   <= 1'h0;
	end
	else begin
	    cnt    <= cntnext;
		hexval <= hexvalnext;		
		mode   <= modenext;
	end

	wire write_hexval;
	wire write_mode;

	assign write_hexval = (write & (address == 1'h0));
	assign write_mode   = (write & (address == 1'h1));

    always @(*)
      begin
      hexvalnext = hexval;
      modenext   = mode;
      cntnext    = cnt + 24'h1;

      if (write_mode)
      	modenext = writedata[0];

      if (write_hexval)
        hexvalnext = writedata[23:0];
      else if (mode & (cnt == 24'h0))
        hexvalnext = hexval + 24'h1;

      end

endmodule