`timescale 1ns/1ns

module counter_tb;

reg irst = 0;
reg iclk = 0;
wire [3:0] value;

initial begin
    irst = 1;
    #10 irst = 0;
    #1000 $stop;
    //#100 $finish;
end

always
    #5 iclk = !iclk;

counter c1(
    .rst(irst),
    .clk(iclk),
    .out(value));

initial
    $monitor("At time %t, value = 0x%h", $time, value);

initial begin
    $dumpfile("counter_test.vcd");
    $dumpvars(0, c1);
end

endmodule
