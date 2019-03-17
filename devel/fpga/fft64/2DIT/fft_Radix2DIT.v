module fft(
    input wire rst,
    input wire clk,
    input wire InEn,
    input wire [7:0] InR, // 8-bit parallel input for 64-number
    input wire [7:0] InI, // 32 number serial input, LSB first
    output reg [7:0] OutR,
    output reg [7:0] OutI,
    output reg OutEn);

// fft depth = log2(NUM) + 1; >>>>>>>>>>.
parameter DEPTH = 3'd7;
parameter indexMax = 7'd127;
reg [4:0] m; // DEPTH-counter, value: 0 - 6(DEPTH - 1)
reg [15:0] move; // (m-max + 1)-bit
reg [15:0] jmp; // (m-max + 2)-bit
reg [15:0] gap; // value: 32, 16, 8, 4, 2, 0

reg c_a; // step counter
reg c_b; // step conuter of operation process
reg [7:0] i; // value: 0 - 32
reg [7:0] j; // max value is less than []move
/**********************/

// quantize precision is 8-bit >>>>>>>>
reg [7:0] c; // value: 63 - 0, readin 64-number
parameter NUMP = 7'd64;
reg signed [63:0] RE0 [63:0];
reg signed [63:0] IM0 [63:0];

reg signed [63:0] RE1 [63:0];
reg signed [63:0] IM1 [63:0];

reg signed [63:0] fRxR; // factor-real-part * data-real-part
reg signed [63:0] fIxI; // factor-imaginary-part * data-imaginary-part
reg signed [63:0] fRxI; // factor-real-part * data-imaginary-part
reg signed [63:0] fIxR; // factor-imaginary-part * data-real-part

reg signed [63:0] factorRE[31:0]; // real part of factors
reg signed [63:0] factorIM[31:0]; // imaginary part of factors
/***********************************/

reg [1:0] state;
parameter state_idle = 2'd0; // idle
parameter state_read = 2'd1; // read input
parameter state_cal = 2'd2; // calculation
parameter state_write = 2'd3; // write output

reg InEn_r;
// read the serial input
always @ (posedge clk or posedge rst) begin
    if(rst) begin /* reset */
        OutEn <= 1'b0;
        c <= 1'b0;
        state <= state_idle;
    end else if(state == state_idle) begin
        OutEn <= 1'b0;
        OutR <= 1'b0;
        OutI <= 1'b0;

        c <= 1'b0;
        m <= 1'b0; // DEPTH-counter, value: 0 - 6(DEPTH - 1)
        move <= 1'b0; // (m-max + 1)-bit
        jmp <= 1'b0; // (m-max + 2)-bit
        gap <= 6'd32; // gap = NUMP/2

        c_a <= 1'b0; // step counter
        c_b <= 1'b0; // step conuter of operation process
        i <= 1'b0; // value: 0 - 32
        j <= 1'b0; // max value is less than []move

        fRxR <= 1'b0; // factor-real-part * data-real-part
        fIxI <= 1'b0; // factor-imaginary-part * data-imaginary-part
        fRxI <= 1'b0; // factor-real-part * data-imaginary-part
        fIxR <= 1'b0; // factor-imaginary-part * data-real-part

        InEn_r <= InEn;
        if(!InEn_r && InEn)
            state <= state_read;
    end else if(InEn && state == state_read) begin
        /* readin 64-num */
        if(c < NUMP) begin// last number
            c <= c + 1'b1; // reset

            RE0[{c[0], c[1], c[2], c[3], c[4], c[5]}][7:0] <= InR[7:0];
            if(InR[7]) begin// negative number
                RE0[{c[0], c[1], c[2], c[3], c[4], c[5]}][63:8] <= 56'hffffffffffffff;
            end else begin
                RE0[{c[0], c[1], c[2], c[3], c[4], c[5]}][63:7] <= 1'b0;
            end

            IM0[{c[0], c[1], c[2], c[3], c[4], c[5]}][7:0] <= InI[7:0];
            if(InI[7]) begin// negative number
                IM0[{c[0], c[1], c[2], c[3], c[4], c[5]}][63:8] <= 56'hffffffffffffff;
            end else begin
                IM0[{c[0], c[1], c[2], c[3], c[4], c[5]}][63:7] <= 1'b0;
            end

            RE1[c] <= 1'b0;
            IM1[c] <= 1'b0;
        end else begin
            c <= 1'b0;
            state <= state_cal;// jump to calculation
            //state <= state_write;// jump to calculation
        end
    end else if(state == state_cal) begin
        /* calculation */
        if(m < 3'd6) begin
            if(!c_a) begin// c_a process NO.1
                move <= (8'b1 << m);
                jmp <=  (8'b1 << (m + 1'b1));
                c_a <= 1'b1;
            end else begin// c_a process NO.2
                if(i < (NUMP >> (m + 1'b1))) begin
                    if(j < move) begin
                        if(!m[0]) begin// current m is odd
                            if(!c_b) begin// process NO.1
                                fRxR <= factorRE[j*gap] * RE0[jmp*i + j + move];
                                fIxI <= factorIM[j*gap] * IM0[jmp*i + j + move];
                                fRxI <= factorRE[j*gap] * IM0[jmp*i + j + move];
                                fIxR <= factorIM[j*gap] * RE0[jmp*i + j + move];
                                c_b <= 1'b1; // next step
                            end else begin// process NO.2
                                RE1[jmp*i + j] <= RE0[jmp*i + j]*indexMax + fRxR - fIxI;
                                IM1[jmp*i + j] <= IM0[jmp*i + j]*indexMax + fRxI + fIxR;
                                RE1[jmp*i + j + move] <= RE0[jmp*i + j]*indexMax -fRxR+fIxI;
                                IM1[jmp*i + j + move] <= IM0[jmp*i + j]*indexMax -fRxI-fIxR;
                                c_b <= 1'b0; // reset
                                j <= j + 1'b1; // increment uplevel loop counter
                            end// c_b
                        end else begin// current m is oven
                            if(!c_b) begin// process NO.1
                                fRxR <= factorRE[j*gap] * RE1[jmp*i + j + move];
                                fIxI <= factorIM[j*gap] * IM1[jmp*i + j + move];
                                fRxI <= factorRE[j*gap] * IM1[jmp*i + j + move];
                                fIxR <= factorIM[j*gap] * RE1[jmp*i + j + move];
                                c_b <= 1'b1; // next step
                            end else begin// process NO.2
                                RE0[jmp*i + j] <= RE1[jmp*i + j]*indexMax + fRxR - fIxI;
                                IM0[jmp*i + j] <= IM1[jmp*i + j]*indexMax + fRxI + fIxR;
                                RE0[jmp*i + j + move] <= RE1[jmp*i + j]*indexMax - fRxR+fIxI;
                                IM0[jmp*i + j + move] <= IM1[jmp*i + j]*indexMax - fRxI-fIxR;
                                c_b <= 1'b0; // reset
                                j <= j + 1'b1; // increment uplevel loop counter
                            end// c_b
                        end // m[0] odd/even
                    end else begin // j == move
                        j <= 1'b0; // reset self-level loop counter
                        i <= i + 1'b1; // increment uplevel loop counter
                    end
                end else begin // i == (NUMP >> (m + 1'b1))
                    c_a <= 1'b0; // reset step conuter of operation process
                    i <= 1'b0; // reset self level loop counter
                    m <= m + 1'b1; // increment uplevel loop counter
                    gap <= (gap >> 1'b1); // increment uplevel loop counter
                end
            end
        end else begin// (m < DEPTH - 1'b1)
            m <= 1'b0; // reset step conuter of operation process
            state <= state_write;
        end
    end else if(state == state_write) begin
        if(!OutEn)
            OutEn <= 1'b1;
        else if(c < NUMP) begin
            if(DEPTH[0]) begin // DEPTH is odd
                OutR <= RE0[c]/562949953421312; // 2**48
                OutI <= IM0[c]/562949953421312; // 2**48
                c <= c + 1'b1;
            end else begin// DEPTH is even
                OutR <= RE1[c]/562949953421312; // 2**48
                OutI <= IM1[c]/562949953421312; // 2**48
                c <= c + 1'b1;
            end
        end else begin // c == NUMP
            c <= 1'b0;
            OutEn <= 1'b0;
            state <= state_read; // reset
        end
    end//state_write
end

initial begin // initials the constant factors
    factorRE[0] <= 64'd127;  factorIM[0] <= 64'd0;
    factorRE[1] <= 64'd126;  factorIM[1] <= -64'd12;
    factorRE[2] <= 64'd124;  factorIM[2] <= -64'd24;
    factorRE[3] <= 64'd121;  factorIM[3] <= -64'd36;
    factorRE[4] <= 64'd117;  factorIM[4] <= -64'd48;
    factorRE[5] <= 64'd112;  factorIM[5] <= -64'd59;
    factorRE[6] <= 64'd105;  factorIM[6] <= -64'd70;
    factorRE[7] <= 64'd98;   factorIM[7] <= -64'd80;
    factorRE[8] <= 64'd89;   factorIM[8] <= -64'd89;
    factorRE[9] <= 64'd80;   factorIM[9] <= -64'd98;
    factorRE[10] <= 64'd70;  factorIM[10] <= -64'd105;
    factorRE[11] <= 64'd59;  factorIM[11] <= -64'd112;
    factorRE[12] <= 64'd48;  factorIM[12] <= -64'd117;
    factorRE[13] <= 64'd36;  factorIM[13] <= -64'd121;
    factorRE[14] <= 64'd24;  factorIM[14] <= -64'd124;
    factorRE[15] <= 64'd12;  factorIM[15] <= -64'd126;
    factorRE[16] <= 64'd0;   factorIM[16] <= -64'd127;
    factorRE[17] <= -64'd12;  factorIM[17] <= -64'd126;
    factorRE[18] <= -64'd24;  factorIM[18] <= -64'd124;
    factorRE[19] <= -64'd36;  factorIM[19] <= -64'd121;
    factorRE[20] <= -64'd48;  factorIM[20] <= -64'd117;
    factorRE[21] <= -64'd59;  factorIM[21] <= -64'd112;
    factorRE[22] <= -64'd70;  factorIM[22] <= -64'd105;
    factorRE[23] <= -64'd80;  factorIM[23] <= -64'd98;
    factorRE[24] <= -64'd89;  factorIM[24] <= -64'd89;
    factorRE[25] <= -64'd98;  factorIM[25] <= -64'd80;
    factorRE[26] <= -64'd105;  factorIM[26] <= -64'd70;
    factorRE[27] <= -64'd112;  factorIM[27] <= -64'd59;
    factorRE[28] <= -64'd117;  factorIM[28] <= -64'd48;
    factorRE[29] <= -64'd121;  factorIM[29] <= -64'd36;
    factorRE[30] <= -64'd124;  factorIM[30] <= -64'd24;
    factorRE[31] <= -64'd126;  factorIM[31] <= -64'd12;
end
endmodule
