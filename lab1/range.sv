module range
  #(parameter
    RAM_WORDS = 16,            // Number of counts to store in RAM
    RAM_ADDR_BITS = 4)         // Number of RAM address bits
   (input logic         clk,    // Clock
    input logic 	go,     // Read start and start testing
    input logic [31:0] 	start,  // Number to start from or count to read
    output logic 	done,   // True once memory is filled
    output logic [15:0] count); // Iteration count once finished

  logic 		cgo;    // "go" for the Collatz iterator
  logic                cdone;  // "done" from the Collatz iterator
  logic [31:0] 	n;      // number to start the Collatz iterator

  // verilator lint_off PINCONNECTEMPTY

  // Instantiate the Collatz iterator
  collatz c1(.clk(clk),
             .go(cgo),
             .n(n),
             .done(cdone),
             .dout());

  logic [RAM_ADDR_BITS - 1:0] 	 num;         // The RAM address to write

  // -----------------------------
  // Control logic for range
  // -----------------------------

  logic [15:0] steps;

  logic 			 we;                    // Write din to addr
  logic [15:0] 		 din;                   // Data to write
  logic [15:0] 		 mem[RAM_WORDS - 1:0];  // The RAM itself
  logic [RAM_ADDR_BITS - 1:0] 	 addr;
  // Address to read/write

  typedef enum logic [2:0] {S_IDLE, S_RUN, S_WRITE, S_NEXT, S_DONE} state_t;
  state_t state = S_IDLE;


  always_ff @(posedge clk)
  begin
    // defaults every cycle
    cgo <= 1'b0;
    we  <= 1'b0;

    case (state)

      // -------- IDLE --------
      S_IDLE:
      begin
        done    <= 1'b0;
        steps   <= 16'd0;

        if (go)
        begin
          num     <= '0;
          n       <= start;
          steps   <= 16'd0;
          cgo     <= 1'b1;      // launch collatz (1-cycle pulse)
          state   <= S_RUN;
        end
      end

      // -------- RUN --------
      // count cycles while collatz is not done
      S_RUN:
      begin
        if (!cdone)
        begin
          steps <= steps + 16'd1;
        end
        else
        begin
          din   <= steps;       // latch result to write
          state <= S_WRITE;
        end
      end

      // -------- WRITE --------
      // IMPORTANT: write using CURRENT num; DO NOT change num/n here
      S_WRITE:
      begin
        we <= 1'b1;             // teacher RAM writes on this posedge

        if (num == RAM_ADDR_BITS'(RAM_WORDS - 1))
        begin
          state <= S_DONE;      // last entry written
        end
        else
        begin
          state <= S_NEXT;      // advance next cycle
        end
      end

      // -------- NEXT --------
      // advance address/value AFTER the write has happened
      S_NEXT:
      begin
        num   <= num + 1'b1;
        n     <= n + 32'd1;
        steps <= 16'd0;
        cgo   <= 1'b1;          // launch next collatz
        state <= S_RUN;
        cdone <= 1'b0;          // clear done for next run
      end

      // -------- DONE --------
      S_DONE:
      begin
        done    <= 1'b1;
        // stay here until next go (or you can go back to IDLE if you prefer)
        if (go)
        begin
          done    <= 1'b0;
          num     <= '0;
          n       <= start;
          steps   <= 16'd0;
          cgo     <= 1'b1;
          state   <= S_RUN;
        end
      end

      default:
        state <= S_IDLE;
    endcase
  end





  assign addr = we ? num : start[RAM_ADDR_BITS-1:0];

  always_ff @(posedge clk)
  begin
    if (we)
      mem[addr] <= din;
    count <= mem[addr];
  end

endmodule

