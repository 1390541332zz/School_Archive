////////////////////////////////////////////////////////////////////////////////
// Filename: project3bTop.v
// Author:   Jacob Abel
// Date:     09 November 2018
// Revision: 2
//
// This is the top-level module for ECE 3544 Project 3b.
// Do not modify the module declaration or ports in this file.
// When synthesizing to the DE1-SoC, this file should be used with the provided
// Quartus project so that the FPGA pin assignments are made correctly.
//
// YOU MUST MAKE THE PIN ASSIGNMENTS FOR THE INPUTS AND OUTPUTS OF THIS MODULE.
// FOLLOW THE INSTRUCTIONS IN THE DOCUMENT ON PIN PLACEMENT.
// CONSULT THE MANUAL FOR INFORMATION ON THE PIN LOCATIONS.

module project3bTop(CLOCK_50, SW, KEY, HEX3, HEX2, HEX1, HEX0);
   input        CLOCK_50;
   input  [6:0] SW;
   input  [1:0] KEY;
   output [6:0] HEX3, HEX2, HEX1, HEX0;

   wire        enable;
   wire [15:0] hexDigits;
    
// The dot notation represents a "named assignment".
// The dotted names are the ports of the instantiated modules.
// The names enclosed in parentheses are the corresponding ports of the top-level module.
// This helps to make clear associations between a module's ports and the ports of an instance.

   keypressed U1 (.clock(CLOCK_50),             // 50 MHz FPGA Clock
                  .reset(KEY[1]),               // KEY1 is the system reset.
                  .enable_in(KEY[0]),           // KEY0 provides the enable input
                  .enable_out(enable)           // Connect to the enable input port of the counter.
                 );
     fsm16bit U2 (.clock(CLOCK_50),             // 50 MHz FPGA Clock
                  .reset(KEY[1]),               // KEY1 is the system reset.
                  .enable(enable),              // The keypressed enable_out drives the FSM enable.
                  .check(SW[6]),                // Switch SW6 checks the Student ID Number.
                  .mode(SW[5]),                 // Switch SW5 determines the mode.
                  .direction(SW[4]),            // Switch SW4 determines the direction.
                  .value(SW[3:0]),              // Switch SW[3:0] determines the count value.
                  .outputValue(hexDigits)       // Connect the FSM output to the seven-segment displays.
                 );
                  
// INSTANTIATE FOUR INSTANCES OF YOUR SEVEN SEGMENT DISPLAY DRIVER.
// EACH ONE SHOULD ACCEPT A FOUR-BIT VALUE THAT CORRESPONDS TO ONE HEX DIGIT OF THE OUTPUT VALUE.
// THE OUTPUTS OF THE DISPLAY DRIVERS SHOULD CORRESPOND TO A SET OF DRIVERS FOR THE SEVEN SEGMENT DISPLAYS.
// FOLLOW THE "NAMED ASSIGNMENT" APPROACH USED IN keypressed AND fsm16bit.

    proc7segdecoder disp0(.hex_digit(hexDigits[3:0]),
                          .hex_display(HEX0)
                         );
    proc7segdecoder disp1(.hex_digit(hexDigits[7:4]),
                          .hex_display(HEX1)
                         );
    proc7segdecoder disp2(.hex_digit(hexDigits[11:8]),
                          .hex_display(HEX2)
                         );
    proc7segdecoder disp3(.hex_digit(hexDigits[15:12]),
                          .hex_display(HEX3)
                         );

endmodule
