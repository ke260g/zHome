`timescale 1 ns/ 1 ps
module tb();
// test vector input registers
reg InEn;
reg clk;
reg reset;
// wires
wire OutEn;

reg [7:0] InR;
reg [7:0] InI;

wire [7:0] OutR;
wire [7:0] OutI;
reg signed [7:0] OutRr; // for output signed
reg signed [7:0] OutIr; // for output signed
integer OutRi; // for output signed
integer OutIi; // for output signed

fft i1 (
    .rst(reset),
    .clk(clk),
    .InEn(InEn),
    .InR(InR), // 8-bit parallel input for 64-number
    .InI(InI), // 32 number serial input, LSB first
    .OutR(OutR),
    .OutI(OutI),
    .OutEn(OutEn));

parameter NUMP = 7'd64;
reg [6:0] i; // input counter 0~64(NUMP)
reg signed [7:0] memInt[63:0];

reg loopEn;
reg OutEn_r;
integer file_out; // output file discriptor
initial begin
    $display("Running testbench");

    // in/out files handler
    $readmemh("dataInput.txt", memInt);
    file_out = $fopen("dataOutput.txt", "w");
    if(!file_out) begin
        $display("failed to open output file, exit\n");
        $finish;
    end

    // reset
    reset = 1'b0; #10 reset = 1'b1; #10 reset = 1'b0;

    // input trigger
    #10 clk = 1'b0; InEn = 1'b0; #10 clk = 1'b1;
    #10 clk = 1'b0; InEn = 1'b1; #10 clk = 1'b1;

    // input 64 reality number, all imagination is zero
    for(i = 0; i < NUMP; i = i+1) begin
        #10 clk = 1'b0;
        InR = memInt[i]; InI = 1'b0;

        /* convert the unsigned number to signed one */
        OutRr = InR; OutRi = OutRr;
        $display("input >> [%2d] %d", i, OutRi);
        #10 clk = 1'b1;
    end

    #10 clk = 1'b0; #10 clk = 1'b1; // input end

    // wait finish
    loopEn = 1'b1;
    while(loopEn) begin
        if(!OutEn_r && OutEn)
            loopEn = 1'b0;
        OutEn_r = OutEn;
        #10 clk = 1'b0;
        #10 clk = 1'b1;
    end

    InEn = 1'b0;

    $display("--- begin to output ---");
    // output to console and file
    for(i = 0; i < NUMP; i = i+1) begin
        /* convert the unsigned number to signed one */
        OutRr = OutR; OutRi = OutRr;
        OutIr = OutI; OutIi = OutIr;

        $display("[%2d] >> Reality: %7d Imaginary: %7d", i, OutRi, OutIi);
        $fdisplay(file_out, "%02d %7d %7d", i, OutRi, OutIi);
        #10 clk = 1'b0;
        #10 clk = 1'b1;
    end
end // initial
endmodule
