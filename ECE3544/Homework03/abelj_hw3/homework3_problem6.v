///////////////////////////////////////////////////////////////////////////////
// Filename:    homework3_problem6.v
// Author:      Jacob Abel
// Date:        5 October 2018
// Version:     1
// Description: This file contains the F() function for Problem 6 of HW3.

module homework3_problem6(
    input a, b, c, d,
    output f
);
    wire g, h;

    assign g = (  ({b, c, d} == 0) 
               || ({b, c, d} == 1)
               || ({b, c, d} == 2)
               || ({b, c, d} == 5)
               || ({b, c, d} == 7)
               );               

    assign h = (  ({b, c, d} == 2) 
               || ({b, c, d} == 3)
               || ({b, c, d} == 5)
               || ({b, c, d} == 7)
               );

    mux21 m(a, g, h, f);
endmodule
