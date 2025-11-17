module sub_module1(
    input  wire [6:0] in1,
    input  wire [6:0] in2,
    input  wire [6:0] in3,
    input  wire [6:0] in4,
    input  wire [6:0] in5,
    input  wire [6:0] in6,
    input  wire [6:0] in7,

    input  wire [7:0] in8,
    input  wire [7:0] in9,
    input  wire [7:0] in10,
    input  wire [7:0] in11,
    input  wire [7:0] in12,
    input  wire [7:0] in13,
    input  wire [7:0] in14,
    input  wire [7:0] in15,

    input  wire [8:0] in16,
    input  wire [8:0] in17,
    input  wire [8:0] in18,
    input  wire [8:0] in19,
    input  wire [8:0] in20,
    input  wire [8:0] in21,
    input  wire [8:0] in22,
    input  wire [8:0] in23,
    input  wire [8:0] in24,

    output wire [4:0] out1,
    output wire [4:0] out2,
    output wire [4:0] out3,
    output wire [4:0] out4,
    output wire [4:0] out5,

    output wire [5:0] out6,
    output wire [5:0] out7,
    output wire [5:0] out8,
    output wire [5:0] out9,
    output wire [5:0] out10,
    output wire [5:0] out11,

    output wire [6:0] out12,
    output wire [6:0] out13,
    output wire [6:0] out14,
    output wire [6:0] out15,
    output wire [6:0] out16,
    output wire [6:0] out17,
    output wire [6:0] out18
);

    wire cond1 = in1[6];
    wire cond2 = in8[7];
    wire cond3 = in16[8];

    wire [9:0] tempA = {3'b010, in2} + {2'b11, in11};
    wire [9:0] tempB = (in24 & 10'h3FF) + (in15 << 1);
    wire [9:0] tempC = {in7, 3'b100} + {2'b00, in9};
    wire [9:0] tempD = {2'b01, in10} ^ {3'b000, in5};
    wire [9:0] tempE = (in6 << 2) + in19[7:0];
    wire [9:0] tempF = in12 + in13 + in14;
    wire [9:0] tempG = {in3, 3'b001} * 3;
    wire [9:0] tempH = (in17[7:0] + in18[7:0]) ^ in20[7:0];
    wire [9:0] tempI = in21[7:0] + (in22[7:0] * 2) + in23[7:0];

    wire [4:0] out1_if1 = in1[4:0] + 5'd3;
    wire [4:0] out1_if2 = (in8[4:0] + in9[4:0]) + 5'd2;
    wire [4:0] out1_if3 = (in16[4:0] ^ in17[4:0]) + 5'd1;
    wire [4:0] out1_else = 5'd0;
    assign out1 = cond1 ? out1_if1 :
                  cond2 ? out1_if2 :
                  cond3 ? out1_if3 :
                  out1_else;

    wire [4:0] out2_if1 = (in2[4:0] << 1) + 5'd5;
    wire [4:0] out2_if2 = (in9[4:0] ^ in10[4:0]) + 5'd7;
    wire [4:0] out2_if3 = in18[4:0] + 5'd3;
    wire [4:0] out2_else = 5'd1;
    assign out2 = cond2 ? out2_if2 :
                  cond3 ? out2_if3 :
                  cond1 ? out2_if1 :
                  out2_else;

    wire [4:0] out3_if1 = (in3[4:0] + 2*in4[4:0]) + 5'd2;
    wire [4:0] out3_if2 = (in11[4:0] + in12[4:0]) ^ 5'd8;
    wire [4:0] out3_if3 = (in19[4:0] - in20[4:0]) + 5'd4;
    wire [4:0] out3_else = 5'd0;
    assign out3 = cond3 ? out3_if3 :
                  cond2 ? out3_if2 :
                  cond1 ? out3_if1 :
                  out3_else;

    wire [4:0] out4_if1 = (in5[4:0] + in6[4:0]) + 5'd9;
    wire [4:0] out4_if2 = (in13[4:0] + in14[4:0]) + 5'd11;
    wire [4:0] out4_if3 = (in21[4:0] ^ in22[4:0]) + 5'd1;
    wire [4:0] out4_else = 5'd3;
    assign out4 = cond1 ? out4_if1 :
                  cond3 ? out4_if3 :
                  cond2 ? out4_if2 :
                  out4_else;

    wire [4:0] out5_if1 = (tempC[4:0] + tempD[4:0]) ^ 5'd6;
    wire [4:0] out5_if2 = in7[4:0] + (2*in1[4:0]) + 5'd5;
    wire [4:0] out5_if3 = (in23[4:0] + in24[4:0]) + 5'd2;
    wire [4:0] out5_else = 5'd31;
    assign out5 = cond2 ? out5_if2 :
                  cond1 ? out5_if1 :
                  cond3 ? out5_if3 :
                  out5_else;

    wire [5:0] out6_if1 = (tempE[5:0] + 6'd9) ^ 6'd3;
    wire [5:0] out6_if2 = (tempF[5:0] + in8[5:0]) + 6'd5;
    wire [5:0] out6_if3 = in16[5:0] + (in17[5:0] * 2);
    wire [5:0] out6_else = 6'd0;
    assign out6 = cond1 ? out6_if1 :
                  cond2 ? out6_if2 :
                  cond3 ? out6_if3 :
                  out6_else;

    wire [5:0] out7_if1 = (in2[5:0] + in3[5:0]) + 6'd12;
    wire [5:0] out7_if2 = (in9[5:0] ^ in15[5:0]) + 6'd1;
    wire [5:0] out7_if3 = (in18[5:0] + in19[5:0]) - 6'd2;
    wire [5:0] out7_else = 6'd4;
    assign out7 = cond2 ? out7_if2 :
                  cond1 ? out7_if1 :
                  cond3 ? out7_if3 :
                  out7_else;

    wire [5:0] out8_if1 = (in4[5:0] << 1) + (in5[5:0] * 3);
    wire [5:0] out8_if2 = in20[5:0] + in21[5:0] + 6'd6;
    wire [5:0] out8_if3 = tempG[5:0] ^ 6'd15;
    wire [5:0] out8_else = 6'd0;
    assign out8 = cond1 ? out8_if1 :
                  cond3 ? out8_if3 :
                  cond2 ? out8_if2 :
                  out8_else;

    wire [5:0] out9_if1 = (in6[5:0] + in7[5:0]) + 6'd2;
    wire [5:0] out9_if2 = (tempH[5:0] + in8[5:0]) - 6'd3;
    wire [5:0] out9_if3 = (in22[5:0] << 1) + in24[5:0];
    wire [5:0] out9_else = 6'd1;
    assign out9 = cond2 ? out9_if2 :
                  cond1 ? out9_if1 :
                  cond3 ? out9_if3 :
                  out9_else;

    wire [5:0] out10_if1 = (in1[5:0] ^ in2[5:0]) + 6'd5;
    wire [5:0] out10_if2 = (tempB[5:0] + tempD[5:0]) + 6'd7;
    wire [5:0] out10_if3 = (in23[5:0] + in24[5:0]) * 2;
    wire [5:0] out10_else = 6'd31;
    assign out10 = cond3 ? out10_if3 :
                   cond2 ? out10_if2 :
                   cond1 ? out10_if1 :
                   out10_else;

    wire [5:0] out11_if1 = (in3[5:0] + in4[5:0]) ^ 6'd12;
    wire [5:0] out11_if2 = (tempC[5:0] + tempE[5:0]) - 6'd1;
    wire [5:0] out11_if3 = (tempI[5:0] + in15[5:0]) + 6'd2;
    wire [5:0] out11_else = 6'd0;
    assign out11 = cond1 ? out11_if1 :
                   cond3 ? out11_if3 :
                   cond2 ? out11_if2 :
                   out11_else;

    wire [6:0] out12_if1 = (in5 + in6) + 7'd5;
    wire [6:0] out12_if2 = {in9[6:0]} + (in10[6:0] << 1);
    wire [6:0] out12_if3 = (in17[6:0] - in18[6:0]) + 7'd3;
    wire [6:0] out12_else = 7'd0;
    assign out12 = cond1 ? out12_if1 :
                   cond2 ? out12_if2 :
                   cond3 ? out12_if3 :
                   out12_else;

    wire [6:0] out13_if1 = (tempA[6:0] + tempB[6:0]) ^ 7'd15;
    wire [6:0] out13_if2 = (in11[6:0] + in12[6:0]) + (in13[6:0] * 2);
    wire [6:0] out13_if3 = in20[6:0] + in21[6:0];
    wire [6:0] out13_else = 7'd1;
    assign out13 = cond2 ? out13_if2 :
                   cond1 ? out13_if1 :
                   cond3 ? out13_if3 :
                   out13_else;

    wire [6:0] out14_if1 = in1 + (3*in2);
    wire [6:0] out14_if2 = (in14[6:0] + in15[6:0]) + tempF[6:0];
    wire [6:0] out14_if3 = (in22[6:0] ^ in23[6:0]) + 7'd4;
    wire [6:0] out14_else = 7'd2;
    assign out14 = cond1 ? out14_if1 :
                   cond3 ? out14_if3 :
                   cond2 ? out14_if2 :
                   out14_else;

    wire [6:0] out15_if1 = (in3 + in7) - 7'd3;
    wire [6:0] out15_if2 = (tempD[6:0] + tempE[6:0]) ^ 7'd9;
    wire [6:0] out15_if3 = (in16[6:0] + in17[6:0]) + in24[6:0];
    wire [6:0] out15_else = 7'd0;
    assign out15 = cond2 ? out15_if2 :
                   cond1 ? out15_if1 :
                   cond3 ? out15_if3 :
                   out15_else;

    wire [6:0] out16_if1 = (in4 + 2*in5) + 7'd3;
    wire [6:0] out16_if2 = (tempH[6:0] + in9[6:0]) - 7'd1;
    wire [6:0] out16_if3 = in18[6:0] + (in21[6:0] << 1);
    wire [6:0] out16_else = 7'd64;
    assign out16 = cond1 ? out16_if1 :
                   cond2 ? out16_if2 :
                   cond3 ? out16_if3 :
                   out16_else;

    wire [6:0] out17_if1 = (in6 + in7) + tempA[6:0];
    wire [6:0] out17_if2 = (in10[6:0] ^ in15[6:0]) + tempB[6:0];
    wire [6:0] out17_if3 = (in19[6:0] & in20[6:0]) + 7'd5;
    wire [6:0] out17_else = 7'd0;
    assign out17 = cond2 ? out17_if2 :
                   cond1 ? out17_if1 :
                   cond3 ? out17_if3 :
                   out17_else;

    wire [6:0] out18_if1 = tempC[6:0] + tempF[6:0];
    wire [6:0] out18_if2 = (tempG[6:0] ^ tempI[6:0]) + 7'd6;
    wire [6:0] out18_if3 = (in22[6:0] + in23[6:0]) + in24[6:0];
    wire [6:0] out18_else = 7'd127;
    assign out18 = cond3 ? out18_if3 :
                   cond1 ? out18_if1 :
                   cond2 ? out18_if2 :
                   out18_else;

endmodule

module sub_module2(
    input  wire in1,
    input  wire in2,
    input  wire in3,
    input  wire in4,
    input  wire in5,
    input  wire in6,
    input  wire in7,
    input  wire in8,
    input  wire in9,
    input  wire in10,
    input  wire in11,
    input  wire in12,
    input  wire in13,
    input  wire in14,
    input  wire in15,
    input  wire in16,
    input  wire in17,
    input  wire in18,
    input  wire in19,
    input  wire in20,
    input  wire in21,
    input  wire in22,
    input  wire in23,
    input  wire in24,
    input  wire in25,
    output wire out1,
    output wire out2,
    output wire out3,
    output wire out4,
    output wire out5,
    output wire out6,
    output wire out7,
    output wire out8,
    output wire out9,
    output wire out10,
    output wire out11,
    output wire out12,
    output wire out13,
    output wire out14,
    output wire out15,
    output wire out16,
    output wire out17,
    output wire out18,
    output wire out19,
    output wire out20
);

    wire partial1  = in1 & ~in2;
    wire partial2  = (in3 ^ in4) & in5;
    wire partial3  = (in6 & in7) ^ (in8 & ~in9);
    wire partial4  = in10 ? (partial1 ^ partial2) : (partial2 & partial3);
    wire partial5  = in11 & in12;
    wire partial6  = partial5 ^ (in13 & in14);
    wire partial7  = in15 ? partial6 : (in16 & partial3);
    wire partial8  = (in17 ^ in18) & partial4;
    wire partial9  = (in19 & in20) ^ partial7;
    wire partial10 = in21 & in22 & in23 & in24 & in25;

    wire condA = in1 & in25;
    wire condB = in5 ^ in15;
    wire condC = in10 & in20;

    wire out1_ifA   = partial1 ^ partial2;
    wire out1_ifB   = partial3 & partial4;
    wire out1_ifC   = partial5 | partial6;
    wire out1_else  = partial7 ^ partial10;
    assign out1 = condA ? out1_ifA :
                  condB ? out1_ifB :
                  condC ? out1_ifC :
                  out1_else;

    wire out2_ifA   = partial2 ^ partial8;
    wire out2_ifB   = partial1 & partial6;
    wire out2_ifC   = (partial3 ^ partial9);
    wire out2_else  = partial10;
    assign out2 = condC ? out2_ifC :
                  condB ? out2_ifB :
                  condA ? out2_ifA :
                  out2_else;

    wire out3_ifA   = (partial4 & partial7) ^ partial3;
    wire out3_ifB   = partial5 & partial8;
    wire out3_ifC   = partial1 ^ partial9;
    wire out3_else  = partial2 | partial10;
    assign out3 = condA ? out3_ifA :
                  condB ? out3_ifB :
                  condC ? out3_ifC :
                  out3_else;

    wire out4_ifA   = partial8 ? ~partial6 : partial3;
    wire out4_ifB   = partial9 & partial2;
    wire out4_ifC   = partial1 | partial10;
    wire out4_else  = partial4 ^ partial5;
    assign out4 = condB ? out4_ifB :
                  condC ? out4_ifC :
                  condA ? out4_ifA :
                  out4_else;

    wire out5_ifA   = partial6 ? partial1 : partial9;
    wire out5_ifB   = partial5 & (partial3 ^ partial8);
    wire out5_ifC   = partial2 ? partial10 : partial4;
    wire out5_else  = partial7 & partial1;
    assign out5 = condC ? out5_ifC :
                  condA ? out5_ifA :
                  condB ? out5_ifB :
                  out5_else;

    wire out6_ifA   = (partial1 & partial2) ^ (partial8 | partial9);
    wire out6_ifB   = (partial3 & partial10) ^ partial4;
    wire out6_ifC   = partial7 ^ (partial5 & partial6);
    wire out6_else  = partial6 | partial9;
    assign out6 = condA ? out6_ifA :
                  condB ? out6_ifB :
                  condC ? out6_ifC :
                  out6_else;

    wire out7_ifA   = (partial5 ^ partial3) & partial7;
    wire out7_ifB   = (partial9 & partial8) ^ partial1;
    wire out7_ifC   = partial10 & (partial4 | partial6);
    wire out7_else  = ~partial2;
    assign out7 = condB ? out7_ifB :
                  condA ? out7_ifA :
                  condC ? out7_ifC :
                  out7_else;

    wire out8_ifA   = partial2 ? partial9 : partial6;
    wire out8_ifB   = (partial3 & partial5) | partial4;
    wire out8_ifC   = partial8 ^ partial10;
    wire out8_else  = partial7;
    assign out8 = condC ? out8_ifC :
                  condB ? out8_ifB :
                  condA ? out8_ifA :
                  out8_else;

    wire out9_ifA   = partial4 ? ~partial3 : partial1;
    wire out9_ifB   = (partial9 & partial10) | partial2;
    wire out9_ifC   = (partial5 ^ partial8) & partial7;
    wire out9_else  = partial6;
    assign out9 = condA ? out9_ifA :
                  condC ? out9_ifC :
                  condB ? out9_ifB :
                  out9_else;

    wire out10_ifA  = partial2 ^ (partial3 & partial10);
    wire out10_ifB  = partial1 & (partial4 ^ partial8);
    wire out10_ifC  = partial9 | partial5;
    wire out10_else = partial7 ^ partial6;
    assign out10 = condB ? out10_ifB :
                   condA ? out10_ifA :
                   condC ? out10_ifC :
                   out10_else;

    wire out11_ifA  = partial5 ? partial10 : (partial1 ^ partial3);
    wire out11_ifB  = partial2 & partial8;
    wire out11_ifC  = (partial9 ^ partial7) | partial4;
    wire out11_else = partial6 & partial1;
    assign out11 = condC ? out11_ifC :
                   condB ? out11_ifB :
                   condA ? out11_ifA :
                   out11_else;

    wire out12_ifA  = partial6 ^ partial9;
    wire out12_ifB  = (partial4 & partial5) ^ partial2;
    wire out12_ifC  = partial8 | partial10;
    wire out12_else = partial7 ? ~partial3 : partial1;
    assign out12 = condA ? out12_ifA :
                   condC ? out12_ifC :
                   condB ? out12_ifB :
                   out12_else;

    wire out13_ifA  = partial3 & (partial2 ^ partial7);
    wire out13_ifB  = partial6 | partial10;
    wire out13_ifC  = (partial4 & partial9) ^ partial1;
    wire out13_else = partial8;
    assign out13 = condB ? out13_ifB :
                   condA ? out13_ifA :
                   condC ? out13_ifC :
                   out13_else;

    wire out14_ifA  = (partial2 ~^ partial4) & partial8;
    wire out14_ifB  = partial10 ? partial1 : partial9;
    wire out14_ifC  = partial3 & partial6;
    wire out14_else = ~partial5;
    assign out14 = condC ? out14_ifC :
                   condB ? out14_ifB :
                   condA ? out14_ifA :
                   out14_else;

    wire out15_ifA  = partial7 ^ partial8;
    wire out15_ifB  = partial9 ? (partial10 & partial2) : partial1;
    wire out15_ifC  = partial3 | (partial4 ^ partial6);
    wire out15_else = partial5;
    assign out15 = condA ? out15_ifA :
                   condB ? out15_ifB :
                   condC ? out15_ifC :
                   out15_else;

    wire out16_ifA  = partial2 & partial3;
    wire out16_ifB  = partial4 ^ partial10;
    wire out16_ifC  = partial7 & (partial1 ~^ partial9);
    wire out16_else = partial6 | partial8;
    assign out16 = condB ? out16_ifB :
                   condA ? out16_ifA :
                   condC ? out16_ifC :
                   out16_else;

    wire out17_ifA  = (partial5 & partial9) ^ partial10;
    wire out17_ifB  = partial8 ? (partial1 & partial3) : partial2;
    wire out17_ifC  = partial6 ^ partial7;
    wire out17_else = partial4;
    assign out17 = condC ? out17_ifC :
                   condB ? out17_ifB :
                   condA ? out17_ifA :
                   out17_else;

    wire out18_ifA  = partial2 ? ~partial10 : partial6;
    wire out18_ifB  = (partial4 & partial7) | (partial1 ^ partial9);
    wire out18_ifC  = partial5 ^ partial8;
    wire out18_else = partial3;
    assign out18 = condA ? out18_ifA :
                   condB ? out18_ifB :
                   condC ? out18_ifC :
                   out18_else;

    wire out19_ifA  = partial1 ? (partial6 | partial10) : partial3;
    wire out19_ifB  = partial2 ~^ (partial4 & partial5);
    wire out19_ifC  = partial7 & partial9;
    wire out19_else = partial8;
    assign out19 = condB ? out19_ifB :
                   condC ? out19_ifC :
                   condA ? out19_ifA :
                   out19_else;

    wire out20_ifA  = (partial2 & partial8) ^ (partial9 & partial10);
    wire out20_ifB  = (partial3 & partial4) | partial1;
    wire out20_ifC  = ~partial6;
    wire out20_else = partial5 ? partial7 : partial5;
    assign out20 = condC ? out20_ifC :
                   condB ? out20_ifB :
                   condA ? out20_ifA :
                   out20_else;

endmodule

module sub_module3(
    input  wire [1:0] in1,
    input  wire [1:0] in2,
    input  wire [1:0] in3,
    input  wire [1:0] in4,
    input  wire [1:0] in5,
    input  wire [1:0] in6,
    input  wire [1:0] in7,
    input  wire [1:0] in8,
    input  wire [1:0] in9,
    input  wire [1:0] in10,
    input  wire [1:0] in11,
    input  wire [1:0] in12,
    input  wire [1:0] in13,
    input  wire [1:0] in14,
    input  wire [1:0] in15,
    input  wire [1:0] in16,
    input  wire [1:0] in17,
    input  wire [1:0] in18,
    input  wire [1:0] in19,
    input  wire [1:0] in20,
    output wire [3:0] out1,
    output wire [3:0] out2,
    output wire [3:0] out3,
    output wire [3:0] out4,
    output wire [3:0] out5,
    output wire [3:0] out6,
    output wire [3:0] out7,
    output wire [3:0] out8,
    output wire [3:0] out9,
    output wire [3:0] out10,
    output wire [3:0] out11,
    output wire [3:0] out12,
    output wire [3:0] out13,
    output wire [3:0] out14,
    output wire [3:0] out15
);

    wire condA = in1[1] & in2[0];
    wire condB = in3[1] ^ in4[1];
    wire condC = in5[1] | in6[0];

    wire [3:0] partial1 = {in7, in8};
    wire [3:0] partial2 = {in9, in10};
    wire [3:0] partial3 = {in11, in12};
    wire [3:0] partial4 = {in13, in14};
    wire [3:0] partial5 = {in15, in16};
    wire [3:0] partial6 = {in17, in18};
    wire [3:0] partial7 = {in19, in20};

    wire [4:0] sum12 = partial1 + partial2;
    wire [4:0] sum34 = partial3 + partial4;
    wire [4:0] sum56 = partial5 + partial6;
    wire [4:0] sum17 = partial1 + partial7;
    wire [4:0] xor56 = {1'b0, (partial5 ^ partial6)};

    wire [3:0] out1_if1 = sum12[3:0] + {2'b00, in1};
    wire [3:0] out1_if2 = sum34[3:0] ^ {2'b01, in2};
    wire [3:0] out1_if3 = partial1[3:0] + partial7[3:0];
    wire [3:0] out1_else = 4'd9;
    assign out1 = condA ? out1_if1 :
                  condB ? out1_if2 :
                  condC ? out1_if3 :
                  out1_else;

    wire [3:0] out2_if1 = (partial5 ^ partial7);
    wire [3:0] out2_if2 = sum56[3:0] - {2'b10, in3};
    wire [3:0] out2_if3 = partial2 & partial4;
    wire [3:0] out2_else = sum17[4:1];
    assign out2 = condC ? out2_if3 :
                  condA ? out2_if1 :
                  condB ? out2_if2 :
                  out2_else;

    wire [3:0] out3_if1 = (partial3 | partial6) ^ {in4, in5};
    wire [3:0] out3_if2 = sum12[3:0] + sum56[3:0];
    wire [3:0] out3_if3 = (partial1 & partial2) + {1'b0, in6};
    wire [3:0] out3_else = (partial4 - partial7);
    assign out3 = condA ? out3_if1 :
                  condB ? out3_if2 :
                  condC ? out3_if3 :
                  out3_else;

    wire [3:0] out4_if1 = (partial2 + partial3) ^ {in7, in8};
    wire [3:0] out4_if2 = partial5 + 4'd7;
    wire [3:0] out4_if3 = partial7 - {2'b00, in9};
    wire [3:0] out4_else = (sum34[3:0] ^ sum56[3:0]);
    assign out4 = condB ? out4_if2 :
                  condA ? out4_if1 :
                  condC ? out4_if3 :
                  out4_else;

    wire [3:0] out5_if1 = (sum17[3:0] ^ sum12[3:0]) + {1'b0, in10};
    wire [3:0] out5_if2 = partial4 & 4'd12;
    wire [3:0] out5_if3 = partial1 ^ partial6;
    wire [3:0] out5_else = {in11[1], in12[0], in11[0], in12[1]};
    assign out5 = condC ? out5_if3 :
                  condA ? out5_if1 :
                  condB ? out5_if2 :
                  out5_else;

    wire [3:0] out6_if1 = (partial3 + partial7) - {2'b00, in13};
    wire [3:0] out6_if2 = {in14[1], in15[1], in14[0], in15[0]} + 4'd1;
    wire [3:0] out6_if3 = sum34[3:0] + sum17[4:1];
    wire [3:0] out6_else = partial2;
    assign out6 = condA ? out6_if1 :
                  condC ? out6_if3 :
                  condB ? out6_if2 :
                  out6_else;

    wire [3:0] out7_if1 = (partial4 << 1) + partial5;
    wire [3:0] out7_if2 = partial7 & sum12[3:0];
    wire [3:0] out7_if3 = sum56[4:1] ^ {in16, in17};
    wire [3:0] out7_else = 4'd2;
    assign out7 = condC ? out7_if3 :
                  condA ? out7_if1 :
                  condB ? out7_if2 :
                  out7_else;

    wire [3:0] out8_if1 = (partial3 ^ partial6) - 4'd3;
    wire [3:0] out8_if2 = (partial1 + partial2) + 4'd5;
    wire [3:0] out8_if3 = (sum34[4:1] - partial7);
    wire [3:0] out8_else = {in18[1], in18[0], in19[1], in19[0]};
    assign out8 = condB ? out8_if2 :
                  condC ? out8_if3 :
                  condA ? out8_if1 :
                  out8_else;

    wire [3:0] out9_if1 = (partial4 + partial7) ^ {in1};
    wire [3:0] out9_if2 = partial2 ~^ {in2, in3};
    wire [3:0] out9_if3 = (xor56[3:0] + {in4});
    wire [3:0] out9_else = partial5;
    assign out9 = condA ? out9_if1 :
                  condB ? out9_if2 :
                  condC ? out9_if3 :
                  out9_else;

    wire [3:0] out10_if1 = partial1 - {in5, in6};
    wire [3:0] out10_if2 = (partial3 & partial7) + 4'd6;
    wire [3:0] out10_if3 = sum12[3:0] ^ sum56[3:0];
    wire [3:0] out10_else = 4'd0;
    assign out10 = condC ? out10_if3 :
                   condA ? out10_if1 :
                   condB ? out10_if2 :
                   out10_else;

    wire [3:0] out11_if1 = (partial5 + partial7) ^ {in8};
    wire [3:0] out11_if2 = (partial6 & partial1) + 4'd2;
    wire [3:0] out11_if3 = sum17[3:0] - 4'd1;
    wire [3:0] out11_else = partial2 + partial4;
    assign out11 = condA ? out11_if1 :
                   condB ? out11_if2 :
                   condC ? out11_if3 :
                   out11_else;

    wire [3:0] out12_if1 = (sum34[3:0] + sum56[3:0]) ^ {in9};
    wire [3:0] out12_if2 = partial3 | partial4;
    wire [3:0] out12_if3 = (partial2 - partial6) + 4'd1;
    wire [3:0] out12_else = 4'd15;
    assign out12 = condB ? out12_if2 :
                   condC ? out12_if3 :
                   condA ? out12_if1 :
                   out12_else;

    wire [3:0] out13_if1 = partial1 & (partial5 ^ partial2);
    wire [3:0] out13_if2 = (sum17[3:0] + sum34[3:0]) - 4'd5;
    wire [3:0] out13_if3 = partial6 ~^ partial7;
    wire [3:0] out13_else = 4'd8;
    assign out13 = condC ? out13_if3 :
                   condA ? out13_if1 :
                   condB ? out13_if2 :
                   out13_else;

    wire [3:0] out14_if1 = (partial4 + partial1) + {in10};
    wire [3:0] out14_if2 = (partial7 ^ partial3) + 4'd3;
    wire [3:0] out14_if3 = xor56[3:0];
    wire [3:0] out14_else = 4'd1;
    assign out14 = condA ? out14_if1 :
                   condC ? out14_if3 :
                   condB ? out14_if2 :
                   out14_else;

    wire [3:0] out15_if1 = (partial2 + partial7) ^ {in11};
    wire [3:0] out15_if2 = (sum56[3:0] - sum17[4:1]) + 4'd7;
    wire [3:0] out15_if3 = partial4 & (partial5 + partial6);
    wire [3:0] out15_else = 4'd4;
    assign out15 = condB ? out15_if2 :
                   condA ? out15_if1 :
                   condC ? out15_if3 :
                   out15_else;

endmodule
