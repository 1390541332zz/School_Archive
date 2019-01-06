////////////////////////////////////////////////////////////////////////////////
// Filename: ECE3544project3a.v
// Author:   Yu Guo
// Date:     13 October 2018
// Revision: 1
//
// This is the top-level module for ECE 3544 Project 3a.
// Do not modify the module declaration or ports in this file.
// When synthesizing to the DE1-SoC, this file should be used with the provided
// Quartus project so that the FPGA pin assignments are made correctly.
//
// YOU MUST MAKE THE PIN ASSIGNMENTS FOR THE INPUTS AND OUTPUTS OF THIS MODULE.
// FOLLOW THE INSTRUCTIONS IN THE DOCUMENT ON PIN PLACEMENT.
// CONSULT THE MANUAL FOR INFORMATION ON THE PIN LOCATIONS.

module ECE3544project3a(SW, LED, HEX0, HEX1, HEX2, HEX3, HEX4);
    input  [9:0] SW;
    output [9:0] LED;
    output [6:0] HEX0, HEX1, HEX2, HEX3, HEX4;
    wire lt, gt, eq;
    wire olt, ogt, oeq;
// This should allow you to see the values of the switches on the LEDs.
// YOU WILL NEED TO CHANGE THIS TO SATISFY THE SPECIFICATION REQUIREMENTS
   assign LED = SW;
   assign lt = 0;
   assign gt = 0;
   assign eq = 1;

// Your top-level module should conform to block diagram provided in the
// specification. It should contain:
// - The magnitude comparator system module.
//   - Two 4-bit inputs A and B. 1-bit enable and 1-bit clear. 3-bit output 
//     represent A bigger, equal or less than B. 
// - 7 segment display module. It will show the input and output results. 

    hc85 cmp(SW[7:4], SW[3:0], SW[8], lt, eq, gt, olt, oeq, ogt);

    proc7segdecoder hex0({3'b0, oeq}, HEX0);
    proc7segdecoder hex1({3'b0, olt}, HEX1);
    proc7segdecoder hex2({3'b0, ogt}, HEX2);
    proc7segdecoder hex3(SW[3:0], HEX3);
    proc7segdecoder hex4(SW[7:4], HEX4);

endmodule
