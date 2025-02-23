module testbench_tb;

    // test config
    parameter DURATION  = 100;

    parameter DELAY_1 = 1;
    parameter DELAY_2 = 2;
    parameter DELAY_3 = 3;
    parameter DELAY_4 = 4;

    initial begin
        $dumpfile("testbench_tb.vcd");    
        $dumpvars(0, testbench_tb);       
        #(DURATION);                  
        $finish;                       
    end

    // mplex2_1 test
    reg sel_0;
    wire i_0, i_1, out;

    initial begin
        #(DELAY_4)
        sel_0 = 1'b0;
        #1; $display("out = %b", out);
        sel_0 = 1'b1;
        #1; $display("out = %b", out);
    end

    mplex2_1 mplex2_1_module(
        .sel(sel_0),
        .i_0(i_0),
        .i_1(i_1),
        .out(out)
    );

    // counter test
    reg clk_0;
    wire [4:0] leds;

    initial begin
        clk_0 = 0;
    end

    always begin
        #(DELAY_1)
        clk_0 = ~clk_0;
        $display("led config = %b", leds);
    end

    counter counter_module(
        .clk(clk_0),
        .leds(leds)
    );

    // 4-bit LUT test
    reg  [3:0]   lut_inputs;
    reg  [15:0]  lut_config;
    wire [3:0]   lut_out;

    initial begin
        // programming LUT for ZERO function
        lut_config <= 0;
        // logic execution 
        #(DELAY_4)
        lut_inputs <= 0;
        $display("lut output = %b", out); // in SV: assert out == 0
        
        // programming LUT for '^^^' function
        #(DELAY_4)
        lut_config <= 16'h0001;
        // logic execution
        #(DELAY_4)
        lut_inputs <= 4'b1111;
        $display("lut output = %b", out); // in SV: assert out == 1
    end

    lut4_1 lut4_1_module (
        .lut_config(lut_config),
        .inputs(lut_inputs),
        .out(lut_out)
    );

endmodule