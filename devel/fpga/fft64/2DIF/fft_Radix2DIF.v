module fft(
    input wire rst,
    input wire clk,
    input wire InEn, // trigger by a single posetive edge
    input wire [7:0] InR, // 8-bit parallel input for 64-number
    input wire [7:0] InI, // 8-bit parallel input for 64-number
    output reg [7:0] OutR, // 8-bit parallel output for 64-number
    output reg [7:0] OutI, // 8-bit parallel output for 64-number
    output reg OutEn // indicate with a single posetive edge
);

parameter step = 6'd32; // step = num/2, num is 64
reg [6:0] n; // counter, n < step, value 64 - 0
reg [6:0] r; // counter, r < step, value 64 - 0
reg [4:0] cnt_i; // cnt_i: step counter of operation process
// 0: calculate input0add1R, input0sub1R, label_0, label_1
// 1: calculate RxR_0, RxI_0, outputR[2*r] += rr_0; outputI[2*r] += ri_0;
// 2: calculate RxR_1, RxI_1, outputR[2*r+1] += rr_1; outputI[2*r+1] += ri_1;
reg signed [10:0] label_0; // value: 63 - 0
reg signed [10:0] label_1; // value: 63 - 0

reg signed [8:0] input0add1R; // RE[x] + RE[y]
reg signed [8:0] input0sub1R; // RE[x] - RE[y]

reg signed [20:0] RxR0; // = input0add1R * factorRE[label_0[5:0]];
reg signed [20:0] RxI0; // = input0add1R * factorIM[label_0[5:0]];
reg signed [20:0] RxR1; // = input0sub1R * factorRE[label_1[5:0]];
reg signed [20:0] RxI1; // = input0sub1R * factorRE[label_1[5:0]];

/**********************/

// quantize precision is 8-bit >>>>>>>>
reg [6:0] c; // value: 63 - 0, readin 64-number
parameter NUMP = 7'd64;
reg signed [7:0] RE0 [63:0];
reg signed [7:0] IM0 [63:0];
reg signed [20:0] RE1 [63:0];
reg signed [20:0] IM1 [63:0];

reg signed [7:0] factorRE[63:0]; // real part of factors
reg signed [7:0] factorIM[63:0]; // imaginary part of factors
/***********************************/

reg [1:0] state;
parameter state_idle = 2'd0; // idle
parameter state_read = 2'd1; // read input
parameter state_cal = 2'd2; // calculation
parameter state_write = 2'd3; // write output
/****************/
reg InEn_r;

// read the serial input
always @ (posedge clk or posedge rst) begin
    if(rst) begin /* reset */
        OutEn <= 1'b0;
        OutR <= 1'b0;
        OutI <= 1'b0;
        c <= 1'b0;
        state <= state_idle;
    end else if(state == state_idle) begin
        OutEn <= 1'b0;
        OutR <= 1'b0;
        OutI <= 1'b0;

        c <= 1'b0;
        n <= 1'b0;
        r <= 1'b0;
        cnt_i <= 1'b0;

        InEn_r <= InEn;
        if(!InEn_r && InEn)
            state <= state_read;

        label_0 <= 1'b0; // value: 63 - 0
        label_1 <= 1'b0; // value: 63 - 0
        input0add1R <= 1'b0; // RE[x] + RE[y]
        input0sub1R <= 1'b0; // RE[x] - RE[y]
        RxR0 <= 1'b0; // = input0add1R * factorRE[label_0[5:0]];
        RxI0 <= 1'b0; // = input0add1R * factorIM[label_0[5:0]];
        RxR1 <= 1'b0; // = input0sub1R * factorRE[label_1[5:0]];
        RxI1 <= 1'b0; // = input0sub1R * factorRE[label_1[5:0]];
    end else if(state == state_read) begin
        /* readin 64-num */
        if(c < NUMP) begin
            c <= c + 1'b1;
            RE0[c] <= InR;
            IM0[c] <= InI;

            RE1[c] <= 1'b0;
            IM1[c] <= 1'b0;
        end else begin
            c <= 1'b0; // reset
            state <= state_cal;// jump to calculation
        end
    end else if(state == state_cal) begin
        /* calculation */
        if(r < step) begin
            if(n < step) begin
                /* darkness */
                case(cnt_i)
                    0: begin// process 0
                        // step is NUMP/2
                        input0add1R <= RE0[n] + RE0[n + step];
                        input0sub1R <= RE0[n] - RE0[n + step];
                        label_0 <= (2 * n * r) % NUMP;
                        label_1 <= (2 * n * r + n) % NUMP;
                        cnt_i <= cnt_i + 1'b1;
                    end
                    1: begin// process 1
                        RxR0 <= input0add1R * factorRE[label_0[5:0]];
                        RxI0 <= input0add1R * factorIM[label_0[5:0]];
                        RxR1 <= input0sub1R * factorRE[label_1[5:0]];
                        RxI1 <= input0sub1R * factorIM[label_1[5:0]];
                        cnt_i <= cnt_i + 1'b1;
                    end
                    2: begin// process 2
                        RE1[2*r] <= RE1[2*r] + RxR0;
                        IM1[2*r] <= IM1[2*r] + RxI0;
                        RE1[2*r + 1] <= RE1[2*r + 1] + RxR1;
                        IM1[2*r + 1] <= IM1[2*r + 1] + RxI1;
                       // last process,
                       cnt_i <= 1'b0; // reset self-level process counter
                       n <= n + 1'b1; // increment parent-level loop counter
                   end
               endcase
           end else begin// n == step
               n <= 1'b0; // reset self-level loop counter
               r <= r + 1'b1; // increment parent-level loop counter
           end
       end else begin// r == step
           r <= 1'b0;
           state <= state_write;
       end
   end else if(state == state_write) begin
       if(!OutEn)
           OutEn <= 1'b1;
       else if(c < NUMP) begin
           OutR <= RE1[c]/16384; // 2**14
           OutI <= IM1[c]/16384; // 2**14
           c <= c + 1'b1;
       end else begin// c == NUMP
           c <= 1'b0; // reset
           state <= state_idle;
       end
   end else begin /* error occurs or finish, reset */
       OutEn <= 1'b0;
       OutR <= 1'b0;
       OutI <= 1'b0;
       c <= 1'b0;
       state <= state_idle;
   end
end

initial begin // initials the constant factors
    factorRE[0] <= 8'd127;  factorIM[0] <= 8'd0;
    factorRE[1] <= 8'd126;  factorIM[1] <= -8'd12;
    factorRE[2] <= 8'd124;  factorIM[2] <= -8'd24;
    factorRE[3] <= 8'd121;  factorIM[3] <= -8'd36;
    factorRE[4] <= 8'd117;  factorIM[4] <= -8'd48;
    factorRE[5] <= 8'd112;  factorIM[5] <= -8'd59;
    factorRE[6] <= 8'd105;  factorIM[6] <= -8'd70;
    factorRE[7] <= 8'd98;  factorIM[7] <= -8'd80;
    factorRE[8] <= 8'd89;  factorIM[8] <= -8'd89;
    factorRE[9] <= 8'd80;  factorIM[9] <= -8'd98;
    factorRE[10] <= 8'd70;  factorIM[10] <= -8'd105;
    factorRE[11] <= 8'd59;  factorIM[11] <= -8'd112;
    factorRE[12] <= 8'd48;  factorIM[12] <= -8'd117;
    factorRE[13] <= 8'd36;  factorIM[13] <= -8'd121;
    factorRE[14] <= 8'd24;  factorIM[14] <= -8'd124;
    factorRE[15] <= 8'd12;  factorIM[15] <= -8'd126;
    factorRE[16] <= 8'd0;  factorIM[16] <= -8'd127;
    factorRE[17] <= -8'd12;  factorIM[17] <= -8'd126;
    factorRE[18] <= -8'd24;  factorIM[18] <= -8'd124;
    factorRE[19] <= -8'd36;  factorIM[19] <= -8'd121;
    factorRE[20] <= -8'd48;  factorIM[20] <= -8'd117;
    factorRE[21] <= -8'd59;  factorIM[21] <= -8'd112;
    factorRE[22] <= -8'd70;  factorIM[22] <= -8'd105;
    factorRE[23] <= -8'd80;  factorIM[23] <= -8'd98;
    factorRE[24] <= -8'd89;  factorIM[24] <= -8'd89;
    factorRE[25] <= -8'd98;  factorIM[25] <= -8'd80;
    factorRE[26] <= -8'd105;  factorIM[26] <= -8'd70;
    factorRE[27] <= -8'd112;  factorIM[27] <= -8'd59;
    factorRE[28] <= -8'd117;  factorIM[28] <= -8'd48;
    factorRE[29] <= -8'd121;  factorIM[29] <= -8'd36;
    factorRE[30] <= -8'd124;  factorIM[30] <= -8'd24;
    factorRE[31] <= -8'd126;  factorIM[31] <= -8'd12;
    factorRE[32] <= -8'd127;  factorIM[32] <= 8'd0;
    factorRE[33] <= -8'd126;  factorIM[33] <= 8'd12;
    factorRE[34] <= -8'd124;  factorIM[34] <= 8'd24;
    factorRE[35] <= -8'd121;  factorIM[35] <= 8'd36;
    factorRE[36] <= -8'd117;  factorIM[36] <= 8'd48;
    factorRE[37] <= -8'd112;  factorIM[37] <= 8'd59;
    factorRE[38] <= -8'd105;  factorIM[38] <= 8'd70;
    factorRE[39] <= -8'd98;  factorIM[39] <= 8'd80;
    factorRE[40] <= -8'd89;  factorIM[40] <= 8'd89;
    factorRE[41] <= -8'd80;  factorIM[41] <= 8'd98;
    factorRE[42] <= -8'd70;  factorIM[42] <= 8'd105;
    factorRE[43] <= -8'd59;  factorIM[43] <= 8'd112;
    factorRE[44] <= -8'd48;  factorIM[44] <= 8'd117;
    factorRE[45] <= -8'd36;  factorIM[45] <= 8'd121;
    factorRE[46] <= -8'd24;  factorIM[46] <= 8'd124;
    factorRE[47] <= -8'd12;  factorIM[47] <= 8'd126;
    factorRE[48] <= 8'd0;  factorIM[48] <= 8'd127;
    factorRE[49] <= 8'd12;  factorIM[49] <= 8'd126;
    factorRE[50] <= 8'd24;  factorIM[50] <= 8'd124;
    factorRE[51] <= 8'd36;  factorIM[51] <= 8'd121;
    factorRE[52] <= 8'd48;  factorIM[52] <= 8'd117;
    factorRE[53] <= 8'd59;  factorIM[53] <= 8'd112;
    factorRE[54] <= 8'd70;  factorIM[54] <= 8'd105;
    factorRE[55] <= 8'd80;  factorIM[55] <= 8'd98;
    factorRE[56] <= 8'd89;  factorIM[56] <= 8'd89;
    factorRE[57] <= 8'd98;  factorIM[57] <= 8'd80;
    factorRE[58] <= 8'd105;  factorIM[58] <= 8'd70;
    factorRE[59] <= 8'd112;  factorIM[59] <= 8'd59;
    factorRE[60] <= 8'd117;  factorIM[60] <= 8'd48;
    factorRE[61] <= 8'd121;  factorIM[61] <= 8'd36;
    factorRE[62] <= 8'd124;  factorIM[62] <= 8'd24;
    factorRE[63] <= 8'd126;  factorIM[63] <= 8'd12;
end
endmodule
