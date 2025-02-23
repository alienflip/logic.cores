`ifndef LUT_MODULE
`define LUT_MODULE

module lut4_1
(
    input  [15:0]    lut_config,
    input  [3:0]     inputs,
    output [3:0]     out
);

    assign out = lut_config[inputs];

endmodule

`endif