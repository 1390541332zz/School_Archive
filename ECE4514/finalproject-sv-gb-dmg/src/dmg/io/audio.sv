/*---------------------------------------------------------------------------*
 * Module: Gameboy DMG Audio Subsystem                                       *
 * Purpose: Controls the audio output for the Gameboy DMG, Outputs at 48KHz  *
 * Last Edit: 2019-04-30                                                     *
 * Maintainer: Jacob Abel                                                    *
 *---------------------------------------------------------------------------*/

module audio(
/*---------------------------------------------------------------------------*/
/*                                Variables                                  */
/*---------------------------------------------------------------------------*/
    st_data.source l_out,
    st_data.source r_out
);

parameter sample_freq = 48000;

/*---------------------------------------------------------------------------*/
/*                                Assertions                                 */
/*---------------------------------------------------------------------------*/

assert property (
    $size(l_out.data) == $size(r_out.data) 
);

/*---------------------------------------------------------------------------*/
/*                               Computation                                 */
/*---------------------------------------------------------------------------*/

//always_comb begin
//    ctr_  = ctr + 1;
//    
//end
//
//always_ff if (!enable || !l_out.reset) begin 
//    l_out.data  <=  'b0;
//    l_out.valid <= 1'b0;
//    r_out.data  <=  'b0;
//    r_out.valid <= 1'b0;
//    ctr         <=  'b0;
//    active      <= 1'b0;
//end else if (ctr < CTR_MAX) begin
//    l_out.data  <= l_out.data;
//    l_out.valid <= 1'b0;
//    r_out.data  <=  'b0;
//    r_out.valid <= 1'b0;
//    ctr         <=  'b0;
//    active      <= 1'b0;
//end else if (ctr < CTR_MAX) begin
//    l_out.data  <= l_dmg.data;
//    l_out.valid <= 1'b0;
//    r_out.data  <=  'b0;
//    r_out.valid <= 1'b0;
//    ctr         <=  'b0;
//    active      <= 1'b0;
//end

endmodule : audio
