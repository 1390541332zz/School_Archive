////////////////////////////////////////////////////////////////////////////////////////////////////
// Filename:    rock_paper_scissors.v
// Author:      Jacob Abel
// Date:        19 September 2018
// Version:     1
// Description: This module judges the results of a rock paper scissors game.

module rock_paper_scissors(
   input  [1:0]  player_a,
   input  [1:0]  player_b,
   output        player_a_wins,
   output        player_b_wins,
   output        tie_game
 );
   
   wire  a0_not, b0_not;
   wire  a_rock, b_rock;
   wire  a_paper, b_paper;
   wire  a_scissors, b_scissors;
   wire  a_rs, a_sp, a_pr;
   wire  b_rs, b_sp, b_pr;
   wire  t_pp, t_rr, t_ss;

   and RA(a_rock, player_a[0], player_a[1]);
   and RB(b_rock, player_b[0], player_b[1]);

   not AN0(a0_not, player_a[0]);
   not BN0(b0_not, player_b[0]);

   and PA(a_paper, a0_not, player_a[1]);
   and PB(b_paper, b0_not, player_b[1]);

   nor SA(a_scissors, player_a[0], player_a[1]);
   nor SB(b_scissors, player_b[0], player_b[1]);

   and ARS(a_rs, a_rock,     b_scissors);
   and ASP(a_sp, a_scissors, b_paper);
   and APR(a_pr, a_paper,    b_rock);

   and BRS(b_rs, b_rock,     a_scissors);
   and BSP(b_sp, b_scissors, a_paper);
   and BPR(b_pr, b_paper,    a_rock);
 
   and TPP(t_pp, a_paper,    b_paper);
   and TRR(t_rr, a_rock,     b_rock);
   and TSS(t_ss, a_scissors, b_scissors);

   or AW(player_a_wins, a_rs, a_sp, a_pr);
   or BW(player_b_wins, b_rs, b_sp, b_pr);
   or TG(tie_game, t_pp, t_rr, t_ss);

endmodule
