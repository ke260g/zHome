module fft(
    input wire rst,
    input wire clk,
    input wire InEn,
    input wire [7:0] InR, // 8-bit parallel input for 64-number
    input wire [7:0] InI, // 32 number serial input, LSB first
    output reg [7:0] OutR,
    output reg [7:0] OutI,
    output reg OutEn);

parameter step = 6'd16; // step = num/4, num is 64
parameter num_1d4 = 6'd16;
parameter num_2d4 = 6'd32;
parameter num_3d4 = 6'd48;
reg [5:0] n; // counter, n < step, value 16 - 0
reg [5:0] r; // counter, r < step, value 16 - 0
reg [3:0] cnt_i; // cnt_i: step counter of operation process

// 0: calculate input*add/sub*R and label_*
// 1: calculate R/I x R/I_*
// 2: calculate result
reg signed [15:0] input0add2R; // sum of two RE0[*]
reg signed [15:0] input1add3R; // diff of two RE0[*]
reg signed [15:0] input0sub2R; // sum of two RE0[*]
reg signed [15:0] input1sub3R; // diff of two RE0[*]

reg signed [15:0] label_0; // value: 63 - 0
reg signed [15:0] label_1; // value: 63 - 0
reg signed [15:0] label_2; // value: 63 - 0
reg signed [15:0] label_3; // value: 63 - 0

reg signed [20:0] RxR_0; // indexR[label_0] * (input0add2R + input1add3R);
reg signed [20:0] IxR_0; // indexI[label_0] * (input0add2R + input1add3R);
reg signed [20:0] RxR_1; //   indexR[label_1] * input0sub2R;
reg signed [20:0] IxI_1; // - indexI[label_1] * input1sub3R;
reg signed [20:0] RxI_1; // - indexR[label_1] * input1sub3R;
reg signed [20:0] IxR_1; //   indexI[label_1] * input0sub2R;
reg signed [20:0] RxR_2; // indexR[label_2] * (input0add2R - input1add3R);
reg signed [20:0] IxR_2; // indexI[label_2] * (input0add2R - input1add3R);
reg signed [20:0] RxR_3; // indexR[label_3] * input0sub2R;
reg signed [20:0] IxI_3; // indexI[label_3] * input1sub3R;
reg signed [20:0] RxI_3; // indexR[label_3] * input1sub3R;
reg signed [20:0] IxR_3; // indexI[label_3] * input0sub2R;
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

        input0add2R <= 1'b0; // sum of two RE0[*]
        input1add3R <= 1'b0; // diff of two RE0[*]
        input0sub2R <= 1'b0; // sum of two RE0[*]
        input1sub3R <= 1'b0; // diff of two RE0[*]

        label_0 <= 1'b0; // value: 63 - 0
        label_1 <= 1'b0; // value: 63 - 0
        label_2 <= 1'b0; // value: 63 - 0
        label_3 <= 1'b0; // value: 63 - 0

        RxR_0 <= 1'b0; // indexR[label_0] * (input0add2R + input1add3R);
        IxR_0 <= 1'b0; // indexI[label_0] * (input0add2R + input1add3R);
        RxR_1 <= 1'b0; //   indexR[label_1] * input0sub2R;
        IxI_1 <= 1'b0; // - indexI[label_1] * input1sub3R;
        RxI_1 <= 1'b0; // - indexR[label_1] * input1sub3R;
        IxR_1 <= 1'b0; //   indexI[label_1] * input0sub2R;
        RxR_2 <= 1'b0; // indexR[label_2] * (input0add2R - input1add3R);
        IxR_2 <= 1'b0; // indexI[label_2] * (input0add2R - input1add3R);
        RxR_3 <= 1'b0; // indexR[label_3] * input0sub2R;
        IxI_3 <= 1'b0; // indexI[label_3] * input1sub3R;
        RxI_3 <= 1'b0; // indexR[label_3] * input1sub3R;
        IxR_3 <= 1'b0; // indexI[label_3] * input0sub2R;

        InEn_r <= InEn;
        if(!InEn_r && InEn)
            state <= state_read;
    end else if(InEn && state == state_read) begin
        /* readin 64-num */
        if(c < NUMP) begin
            c <= c + 1'b1;
            RE0[c] <= InR;
            IM0[c] <= InI;

            RE1[c] <= 1'b0;
            IM1[c] <= 1'b0;
        end else begin// c == NUMP
            c <= 1'b0; // reset
            state <= state_cal;// jump to calculation
        end
    end else if(state == state_cal) begin
        /* calculation */
        if(r < step) begin
            if(n < step) begin/* darkness */
                case(cnt_i)
                    0: begin// process 0
                        input0add2R <= RE0[n] + RE0[n + num_2d4];
                        input1add3R <= RE0[n + num_1d4] + RE0[n + num_3d4];
                        input0sub2R <= RE0[n] - RE0[n + num_2d4];
                        input1sub3R <= RE0[n + num_1d4] - RE0[n + num_3d4];

                        label_0 <= (4 * n * r) % NUMP;
                        label_1 <= (4 * n * r + 1 * n) % NUMP;
                        label_2 <= (4 * n * r + 2 * n) % NUMP;
                        label_3 <= (4 * n * r + 3 * n) % NUMP;

                        cnt_i <= cnt_i + 1'b1;
                    end
                    1: begin// process 1
                        RxR_0 <= factorRE[label_0[5:0]] * (input0add2R + input1add3R);
                        IxR_0 <= factorIM[label_0[5:0]] * (input0add2R + input1add3R);

                        RxR_1 <= factorRE[label_1[5:0]] * input0sub2R;
                        IxI_1 <= -(factorIM[label_1[5:0]] * input1sub3R);
                        RxI_1 <= -(factorRE[label_1[5:0]] * input1sub3R);
                        IxR_1 <= factorIM[label_1[5:0]] * input0sub2R;

                        RxR_2 <= factorRE[label_2[5:0]] * (input0add2R - input1add3R);
                        IxR_2 <= factorIM[label_2[5:0]] * (input0add2R - input1add3R);

                        RxR_3 <= factorRE[label_3[5:0]] * input0sub2R;
                        IxI_3 <= factorIM[label_3[5:0]] * input1sub3R;
                        RxI_3 <= factorRE[label_3[5:0]] * input1sub3R;
                        IxR_3 <= factorIM[label_3[5:0]] * input0sub2R;

                        cnt_i <= cnt_i + 1'b1;
                    end
                    2: begin// process 2
                        RE1[4*r + 0] <= RE1[4*r + 0] + RxR_0;
                        IM1[4*r + 0] <= IM1[4*r + 0] + IxR_0;

                        RE1[4*r + 1] <= RE1[4*r + 1] + (RxR_1 - IxI_1);
                        IM1[4*r + 1] <= IM1[4*r + 1] + (RxI_1 + IxR_1);

                        RE1[4*r + 2] <= RE1[4*r + 2] + RxR_2;
                        IM1[4*r + 2] <= IM1[4*r + 2] + IxR_2;

                        RE1[4*r + 3] <= RE1[4*r + 3] + (RxR_3 - IxI_3);
                        IM1[4*r + 3] <= IM1[4*r + 3] + (RxI_3 + IxR_3);
                        // last process, reset-back to begin
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
