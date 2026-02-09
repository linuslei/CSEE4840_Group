module collatz( input logic         clk,   // Clock
                  input logic 	    go,    // Load value from n; start iterating
                  input logic  [31:0] n,     // Start value; only read when go = 1
                  output logic [31:0] dout,  // Iteration value: true after go = 1
                  output logic 	    done); // True when dout reaches 1

  logic run;

  always_ff @(posedge clk)
  begin
    if(go)
    begin
      dout <= n;
      done <= (n == 32'd1);
      run <= (n != 32'd1);
    end
    else if (run)
    begin
      logic [31:0] next_dout;

      if (dout[0] == 1'b0)
        next_dout = dout >> 1;
      else
        next_dout = 32'd3 * dout + 1;

      dout <= next_dout;

      if (next_dout == 32'd1)
      begin
        done <= 1'b1;
        run <= 1'b0;
      end
    end
  end

endmodule
