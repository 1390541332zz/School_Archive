/*---------------------------------------------------------------------------*
 * Library: Compile Time Functions for Templating                            *
 * Last Edit: 2019-04-02                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/
`ifndef CONST_FUNC_H
`define CONST_FUNC_H

function integer log2(input integer x); begin
    x = x - 1;
    for (log2 = 0; x > 0; log2 = log2 + 1) x = x >> 1;
end endfunction

`endif /* CONST_FUNC_H */
