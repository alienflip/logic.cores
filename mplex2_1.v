`ifndef MPLEX2_1_MODULE
`define MPLEX2_1_MODULE

module mplex2_1 (
    input sel,
    input i_0,
    input i_1,
    output out
);
    reg i_0_reg, i_1_reg;
    assign i_0 = i_0_reg;
    assign i_1 = i_1_reg;

    assign out = (sel == 0) ? (i_0) : (i_1);

    initial begin
        i_0_reg <= 0;
        i_1_reg <= 1;
    end

endmodule

`endif