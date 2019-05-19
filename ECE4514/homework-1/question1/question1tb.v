`timescale 1ns/1ns

module question1tb;

	wire p1a, p1b, p1c, p1d, p1e, p1f;
	wire p2a, p2b, p2c, p2d;
	wire p1y, p2y;
    reg  [3:0] cnt;

	question1 dut(p1a, p1b, p1c, p1d, p1e, p1f,
                  p1y,
                  p2a, p2b, p2c, p2d,
                  p2y );

	assign p1a = cnt[2];
    assign p1b = cnt[1];
    assign p1c = cnt[0];
    assign p1d = cnt[3];
    assign p1e = cnt[2];
    assign p1f = cnt[1];

    assign p2a = cnt[3];
    assign p2b = cnt[2];
    assign p2c = cnt[1];
    assign p2d = cnt[0];

    wire [0:15] exp_p1y = 16'b0000000100000011;
    wire [0:15] exp_p2y = 16'b0001000100011111;

    initial begin
    cnt = 0;
    repeat (16)
      begin
        #100 // needed to enable simulator to compute dut
        if (p1y !== exp_p1y[cnt]) 
          $display("ERROR - P1Y wrong for CNT %d: saw %d but expected %d", cnt, p1y, exp_p1y[cnt]);
        if (p2y !== exp_p2y[cnt]) 
          $display("ERROR - P2Y wrong for CNT %d: saw %d but expected %d", cnt, p2y, exp_p2y[cnt]);
        cnt = cnt + 1;
      end
    $display("DONE");
    $finish;
    end

endmodule