///////////////////////////////////////////////////////////////////////////////
// Filename:    mux21.v
// Author:      Jacob Abel
// Date:        5 October 2018
// Version:     1
// Description: This file contains a 2-to-1 mux.

module mux21(
    input e, s0, s1,
    output Y
);
    assign Y = (e) ? s1 : s0;
endmodule

