//////////////////////////////////////////////////////////////////////
////                                                              ////
//// registerInterface.v                                          ////
////                                                              ////
//// This file is part of the i2cSlave opencores effort.
//// <http://www.opencores.org/cores//>                           ////
////                                                              ////
//// Module Description:                                          ////
//// You will need to modify this file to implement your 
//// interface.
//// Add your control and status bytes/bits to module inputs and outputs,
//// and also to the I2C read and write process blocks  
////                                                              ////
//// To Do:                                                       ////
//// 
////                                                              ////
//// Author(s):                                                   ////
//// - Steve Fielding, sfielding@base2designs.com                 ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
////                                                              ////
//// Copyright (C) 2008 Steve Fielding and OPENCORES.ORG          ////
////                                                              ////
//// This source file may be used and distributed without         ////
//// restriction provided that this copyright statement is not    ////
//// removed from the file and that any derivative work contains  ////
//// the original copyright notice and the associated disclaimer. ////
////                                                              ////
//// This source file is free software; you can redistribute it   ////
//// and/or modify it under the terms of the GNU Lesser General   ////
//// Public License as published by the Free Software Foundation; ////
//// either version 2.1 of the License, or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful, but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE. See the GNU Lesser General Public License for more  ////
//// details.                                                     ////
////                                                              ////
//// You should have received a copy of the GNU Lesser General    ////
//// Public License along with this source; if not, download it   ////
//// from <http://www.opencores.org/lgpl.shtml>                   ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
//
`include "i2cSlave_define.v"


module registerInterface (
			  clk,
			  rst,
			  addr,
			  dataIn,
			  writeEn,
			  dataOut,
			  myReg0,
			  myReg1,
			  myReg2,
			  myReg3,
			  myReg4,
			  myReg5,
			  myReg6,
			  myReg7
			  );
   input clk;
   input rst;
   input [7:0] addr;
   input [7:0] dataIn;
   input       writeEn;
   output [7:0] dataOut;
   output [7:0] myReg0;
   output [7:0] myReg1;
   output [7:0] myReg2;
   output [7:0] myReg3;
   output [7:0] myReg4;
   output [7:0] myReg5;
   output [7:0] myReg6;
   output [7:0] myReg7;
   
   reg [7:0] 	dataOut;
   reg [7:0] 	myReg0;
   reg [7:0] 	myReg1;
   reg [7:0] 	myReg2;
   reg [7:0] 	myReg3;
   reg [7:0] 	myReg4; 
   reg [7:0] 	myReg5; 
   reg [7:0] 	myReg6; 
   reg [7:0] 	myReg7; 
   
   // --- I2C Read
   always @(posedge clk) begin
   if (rst == 1'b1) begin
   	dataOut <= 8'h0;
   end else begin
      case (addr)
	8'd00: dataOut <= myReg0;  
	8'd01: dataOut <= myReg1;  
	8'd02: dataOut <= myReg2;  
	8'd03: dataOut <= myReg3;  
	8'd04: dataOut <= myReg4;  
	8'd05: dataOut <= myReg5;  
	8'd06: dataOut <= myReg6;  
	8'd07: dataOut <= myReg7;  
	default: dataOut <= 8'h00;
      endcase
      end
   end
   
   // --- I2C Write
   always @(posedge clk) begin
   if (rst) begin
	    myReg0  <= 8'h0;  
	    myReg1  <= 8'h0;  
	    myReg2  <= 8'h0;  
	    myReg3  <= 8'h0;  
	    myReg4  <= 8'h0;  
	    myReg5  <= 8'h0;  
	    myReg6  <= 8'h0;  
	    myReg7  <= 8'h0;  
   	
   end else begin
      if (writeEn == 1'b1) begin
	 case (addr)
	   8'd00: myReg0  <= dataIn;  
	   8'd01: myReg1  <= dataIn;  
	   8'd02: myReg2  <= dataIn;  
	   8'd03: myReg3  <= dataIn;  
	   8'd04: myReg4  <= dataIn;  
	   8'd05: myReg5  <= dataIn;  
	   8'd06: myReg6  <= dataIn;  
	   8'd07: myReg7  <= dataIn;  
	 endcase
      end
      end
   end
   
endmodule


 
