// CSEE 4840 Lab 1: Run and Display Collatz Conjecture Iteration Counts
//
// Spring 2023
//
// By: <your name here>
// Uni: <your uni here>

module lab1( input logic        CLOCK_50,  // 50 MHz Clock input

               input logic [3:0] 	KEY, // Pushbuttons; KEY[0] is rightmost

               input logic [9:0] 	SW, // Switches; SW[0] is rightmost

               // 7-segment LED displays; HEX0 is rightmost
               output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5,

               output logic [9:0] LEDR // LEDs above the switches; LED[0] on right
             );

  logic 			clk, go, done;
  logic [31:0] 		start;
  logic [15:0] 		count;

  logic [11:0] 		n;
  logic [7:0] offset;

  logic [31:0] base_start;
  logic [31:0] start_to_range;

  logic view;


  assign clk = CLOCK_50;

  assign base_start = {22'd0, SW}; // zero-extend the 10-bit switch input to 32 bits
  assign start_to_range = done ? {24'd0, offset} : base_start; // if done, use offset, otherwise use switch input


  range #(256, 8) // RAM_WORDS = 256, RAM_ADDR_BITS = 8)
        r (
          .clk(clk),
          .go(go),
          .start(start_to_range),
          .done(done),
          .count(count)
        ); // Connect everything with matching names

  // Replace this comment and the code below it with your own code;
  // The code below is merely to suppress Verilator lint warnings

  logic [21:0] slowed_clk;
  logic tick;

  always_ff @(posedge clk)
  begin
    slowed_clk <= slowed_clk + 1;
  end

  assign tick = (slowed_clk == 22'd0);

  always_ff @( posedge clk )
  begin: BUTTON_HANDLER
    if (!KEY[2])
    begin
      offset <= 8'd0;
    end
    else if (tick)
    begin
      if (!KEY[0])
        offset <= offset + 1;
      else if (!KEY[1])
        offset <= offset - 1;


    end
  end

  always_ff @( posedge clk )
  begin : GO_HANDLER
    if (!KEY[3])
      go <= 1'b1;
    else
      go <= 1'b0;
  end


  logic [11:0] displayed_n;

  assign displayed_n = base_start[11:0] + offset;

  assign LEDR = SW;

  hex7seg h0 ( .a(displayed_n/100), .y(HEX5) );
  hex7seg h1 ( .a((displayed_n/10) % 10), .y(HEX4) );
  hex7seg h2 ( .a(displayed_n % 10), .y(HEX3) );
  hex7seg h3 (.a(count[11:8]), .y(HEX2));
  hex7seg h4 (.a(count[7:4]),  .y(HEX1));
  hex7seg h5 (.a(count[3:0]),  .y(HEX0));
endmodule
