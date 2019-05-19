module monmul #(parameter K = 8,
                parameter M = 8'd239)
               (input  wire [K-1:0] x, y,
                input  wire         clk, reset, start,
                output wire [K-1:0] z,
                output wire         done);

  reg [K-1:0]  shft, shft_nxt;
  reg [K  :0]  acc, acc_nxt;
  reg [K+1:0]  m1, m2;
  reg [K  :0]  cnt, cnt_nxt;
      
  always @(posedge clk or posedge reset)
    begin
    if (reset) begin
       acc  <= 0;
       shft <= 0;
       cnt  <= 0;
    end
    else begin
       acc  <= acc_nxt;
       shft <= shft_nxt;
       cnt  <= cnt_nxt;
    end
  end
  
  always @(*)
    begin
    m1       = shft[0] ? acc + y : acc;
    m2       = m1[0]   ?   m1 +  M : m1;
    acc_nxt  = start   ? 0 : m2[K+1:1];
    shft_nxt = start   ? x : (shft >> 1);
    cnt_nxt  = {cnt[K-1:0],start};
    end

  assign done = cnt[K];
  assign z    = (acc > M) ? acc - M : acc;
        
endmodule
