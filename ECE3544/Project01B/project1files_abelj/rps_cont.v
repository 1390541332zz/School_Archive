////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    rps_cont.v
// Author:      Jacob Abel
// Date:        26 September 2018
// Version:     1
// Description: This module judges the results of a rock paper scissors game.
//              This implementation is done in the Continuous Assignment Paradigm.

module rps_cont(
   input  [1:0]  player_a,
   input  [1:0]  player_b,
   output        player_a_wins,
   output        player_b_wins,
   output        tie_game
 );
   
   // Move State
   wire  [2:0] a, b; // Bits are Rock, Paper, and Scissor.
   
   assign a = {
       (player_a == 0'b00),
       (player_a == 0'b10), 
       (player_a == 0'b11) 
   };

   assign b = {
       (player_b == 0'b00),
       (player_b == 0'b10), 
       (player_b == 0'b11) 
   };
   
   assign player_a_wins = (a[0] && b[2]) || (a[1] && b[0]) || (a[2] && b[1]);
   assign player_b_wins = (b[0] && a[2]) || (b[1] && a[0]) || (b[2] && a[1]);
   assign tie_game      = (a[0] && b[0]) || (a[1] && b[1]) || (a[2] && b[2]);

endmodule
