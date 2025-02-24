`ifndef H_ADDER_MODULE
`define H_ADDER_MODULE

module h_adder (
    input data_0,
    input data_1,
    output carry_out,
    output out
);

    assign out = data_0 ^ data_1;
    assign carry_out = data_0 && data_1;

endmodule

`endif 