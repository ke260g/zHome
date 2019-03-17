`timescale 10ns/1ns
module usb_test(
    input fpga_gclk,                       //FPGA Clock Input 50Mhz
    input reset_n,                         //FPGA Reset input
    output reg [1:0] usb_fifoaddr,         //CY68013 FIFO Address
    output reg usb_slcs,                   //CY68013 Chipset select
    output reg usb_sloe,                   //CY68013 Data output enable
    output reg usb_slrd,                   //CY68013 READ indication
    output reg usb_slwr,                   //CY68013 Write indication
    inout [15:0] usb_fd,                   //CY68013 Data
    input usb_flaga,                       //CY68013 EP2 FIFO empty indication; 1:not empty; 0: empty
    input usb_flagb,                       //CY68013 EP4 FIFO empty indication; 1:not empty; 0: empty
    input usb_flagc                        //CY68013 EP6 FIFO full indication; 1:not full; 0: full
    output [3:0] led;
);

reg[15:0] data_reg;

reg bus_busy;
reg access_req;
reg usb_fd_en;            //控制USB Data的方向

reg [4:0] usb_state;
reg [4:0] i;

parameter IDLE=5'd0;
parameter EP2_RD_CMD=5'd1;
parameter EP2_RD_DATA=5'd2;
parameter EP2_RD_OVER=5'd3;
parameter EP6_WR_CMD=5'd4;
parameter EP6_WR_OVER=5'd5;

assign led[0] = usb_flaga;
assign led[1] = usb_flagb;
assign led[2] = usb_flagc;
assign led[3] = 0;
endmodule
