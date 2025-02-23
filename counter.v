`ifndef COUNTER_MODULE
`define COUNTER_MODULE

module counter (
    input clk,
    output [4:0] leds
);
    reg [4:0] leds_reg;
    assign leds = leds_reg;

    initial begin
        leds_reg <= 0;
    end

    always @ (posedge clk) begin
        leds_reg <= leds_reg + 1;
    end

endmodule

`endif