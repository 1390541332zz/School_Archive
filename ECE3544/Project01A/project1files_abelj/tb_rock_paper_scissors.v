// Time Unit = 1 ns (#10 = 10 ns)
// Simulation Precision = 100 ps
`timescale 1ns/100ps 

////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    tb_rock_paper_scissors.v
// Author:      Jacob Abel
// Date:        19 September 2018
// Version:     1
// Description: This file contains a test bench for the rock paper scissors circuit.

module tb_rock_paper_scissors();
   reg   [1:0] player_a;
   reg   [1:0] player_b;
   wire        player_a_wins;
   wire        player_b_wins;
   wire        tie_game;
   
   reg   [1:0] count;

   rock_paper_scissors DUT(player_a, player_b, player_a_wins, player_b_wins, tie_game);

// Test input waveform - defined as an initial block (procedure)

   initial begin
      player_a = 2'b11;
      #60;
      player_a = 2'b10;
      #60;
      player_a = 2'b00;
      #60;
   end

   initial begin
      for(count = 0; count < 3; count = count + 1) begin
	    player_b = 2'b11;
        #20;
        player_b = 2'b10;
        #20;
        player_b = 2'b00;
        #20;
   	  end
   end
endmodule
