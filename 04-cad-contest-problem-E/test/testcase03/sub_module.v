module sub_module1(
    input  wire [2:0] in1,
    input  wire [2:0] in2,
    input  wire [2:0] in3,
    output wire [2:0] out1,
    output wire [2:0] out2
);
    wire cond1 = (in3[2] > in2[1]); 
    wire cond2 = in1[2];          

    wire [2:0] out1_if1 = {in3[2], in2[0], in1[1]} 
                        + {in3[1], in3[2], in2[3]};   
    wire [2:0] out2_if1 = {in2[1], in1[2], in3[1]} 
                        * {in1[2], in3[1], in2[2]};

    wire [2:0] out1_if2 = {in3[2], in2[0], in1[1]} 
                        + {in3[1], in3[2], in2[3]}   
                        + 2*in1 + 3*in2 + 3;
    wire [2:0] out2_if2 = ({in2[1], in1[2], in3[1]} 
                          * {in1[2], in3[1], in2[2]}) 
                        + 3*in1 + 1*in2 + 2;

    wire [2:0] out1_else = 2*in2 + in3 - 3*in1;
    wire [2:0] out2_else = 3; 

    assign out1 = cond1 ? out1_if1 : 
                  cond2 ? out1_if2 : 
                          out1_else;

    assign out2 = cond1 ? out2_if1 :
                  cond2 ? out2_if2 :
                          out2_else;

endmodule

module sub_module2(
    input  wire [2:0] in1,
    input  wire [2:0] in2,
    input  wire [2:0] in3,
    input  wire [2:0] in4,
    input  wire [2:0] in5,
    input  wire [2:0] in6,
    input  wire [2:0] in7,
    input  wire [2:0] in8,
    input  wire [2:0] in9,
    input  wire [2:0] in10,
    input  wire [2:0] in11,
    input  wire [2:0] in12,
    output wire [2:0] out1,
    output wire [2:0] out2,
    output wire [2:0] out3,
    output wire [2:0] out4,
    output wire [2:0] out5,
    output wire [2:0] out6
);

    wire cond1 = (in1 + in2) > (in3 * in4[1:0]);
    wire cond2 = (in5[2] ^ in6[2]);
    wire cond3 = (in7[1:0] == in8[1:0]);
    wire cond4 = (in9[2] & in10[0]);
    wire cond5 = (in11[2] | in12[2]);
    wire [2:0] out1_if1 = ( (in1 + in2) ^ (in3 - in4) ) + 3; 
    wire [2:0] out1_if2 = {in5[1], in6[0], in7[2]} + (2*in8); 
    wire [2:0] out1_if3 = (in9 * in10[1:0]) ^ (in11 + in12); 
    wire [2:0] out1_if4 = (in1 & in2 & in3) + {in4[1:0], in5[2]};
    wire [2:0] out1_if5 = (in6 << 1) + (in7[2:0] & in8[2:0]) + 4;
    wire [2:0] out1_else= 3'b101;

    assign out1 = cond1 ? out1_if1 :
                  cond2 ? out1_if2 :
                  cond3 ? out1_if3 :
                  cond4 ? out1_if4 :
                  cond5 ? out1_if5 :
                         out1_else;

    wire [2:0] out2_if1 = (in2 + in4) ^ (in1 * in3[1:0]);
    wire [2:0] out2_if2 = (in5 - in6) + (in7 ^ in8) + 2;
    wire [2:0] out2_if3 = (in9[1:0] << 1) + in10[2:0] + in11;
    wire [2:0] out2_if4 = {in12[0], in9[0], in8[0]} * {in3[1], in6[2], in1[0]};
    wire [2:0] out2_if5 = (in2 + in4 + in6 + in8) ^ (in10 + in12);
    wire [2:0] out2_else= 3'b011;

    assign out2 = cond1 ? out2_if1 :
                  cond2 ? out2_if2 :
                  cond3 ? out2_if3 :
                  cond4 ? out2_if4 :
                  cond5 ? out2_if5 :
                         out2_else;

    wire [2:0] out3_if1 = ( (in1[1:0] + in2[1:0]) ^ in3 ) + (in4 << 1);
    wire [2:0] out3_if2 = { (in5[2] & in6[1]), (in7[2] ^ in8[2]) };
    wire [2:0] out3_if3 = ( (in9 + in10) >> 1 ) + (in11 * in12[1:0]);
    wire [2:0] out3_if4 = (in1 & in2 & in3 & in4) ? (in5 + in6) : (in7 + in8);
    wire [2:0] out3_if5 = (in9 ^ in10) + (in11 >> 1) + (in12 << 1);
    wire [2:0] out3_else= 3'b110;

    assign out3 = cond1 ? out3_if1 :
                  cond2 ? out3_if2 :
                  cond3 ? out3_if3 :
                  cond4 ? out3_if4 :
                  cond5 ? out3_if5 :
                         out3_else;
    wire [2:0] out4_if1 = { in1[0], in2[2:1] } + (in3[2:0] * in4[1:0]);
    wire [2:0] out4_if2 = (in5[2:0] & in6[2:0]) ^ (in7[2:0] | in8[2:0]);
    wire [2:0] out4_if3 = {in9[2], in10[1:0]} - {in11[0], in12[2:1]};
    wire [2:0] out4_if4 = (in9 + in10) ^ (in11 + in12);
    wire [2:0] out4_if5 = ( (in1 + in2) & (in3 + in4) ) + 3;
    wire [2:0] out4_else= 3'b100;

    assign out4 = cond1 ? out4_if1 :
                  cond2 ? out4_if2 :
                  cond3 ? out4_if3 :
                  cond4 ? out4_if4 :
                  cond5 ? out4_if5 :
                         out4_else;

    wire [2:0] out5_if1 = (in1 << 1) + (in2 >> 1) + (in3 * in4[1:0]);
    wire [2:0] out5_if2 = {in5[1:0] + in6[1:0]} ^ {in7[2], in8[2:1]};
    wire [2:0] out5_if3 = (in9 * in10) ^ (in11 & in12);
    wire [2:0] out5_if4 = (in3 + in7 + in11) - (in4 + in8 + in12);
    wire [2:0] out5_if5 = ( (in1 + in5) * (in2[1:0] + in6[1:0]) ) ^ (in10 - in9);
    wire [2:0] out5_else= 3'b001;

    assign out5 = cond1 ? out5_if1 :
                  cond2 ? out5_if2 :
                  cond3 ? out5_if3 :
                  cond4 ? out5_if4 :
                  cond5 ? out5_if5 :
                         out5_else;

    wire [2:0] out6_if1 = ( (in1 + in2 + in3) ^ (in4 + in5 + in6) );
    wire [2:0] out6_if2 = (in7 << 1) ^ (in8 << 2) ^ in9;
    wire [2:0] out6_if3 = (in10 - in11) + (in12 >> 1);
    wire [2:0] out6_if4 = ( {in1[0], in2[0], in3[2]} & {in4[2], in5[0], in6[1]} );
    wire [2:0] out6_if5 = (in7 ^ in8 ^ in9 ^ in10 ^ in11 ^ in12);
    wire [2:0] out6_else= 3'b010;

    assign out6 = cond1 ? out6_if1 :
                  cond2 ? out6_if2 :
                  cond3 ? out6_if3 :
                  cond4 ? out6_if4 :
                  cond5 ? out6_if5 :
                         out6_else;
endmodule

module sub_module3(
    input  wire [8:0] in1,
    input  wire [8:0] in2,
    input  wire [8:0] in3,
    input  wire [8:0] in4,
    input  wire [6:0] in5,
    input  wire [6:0] in6,
    input  wire [6:0] in7,
    input  wire [6:0] in8,
    input  wire [6:0] in9,
    input  wire [1:0] in10,
    input  wire [1:0] in11,
    output wire out1,
    output wire out2,
    output wire [3:0] out3,
    output wire [3:0] out4,
    output wire [3:0] out5,
    output wire [3:0] out6,
    output wire [3:0] out7,
    output wire [3:0] out8,
    output wire [3:0] out9,
    output wire [3:0] out10,
    output wire [3:0] out11
);
    wire cond1 = ((in1 + (in2<<1)) > (in3 - in4));
    wire cond2 = ((in5[6:3] ^ in6[2:0]) == in9[4:0]);
    wire cond3 = ((in10[1] & in11[0]) ^ (in7[3] | in8[2]));
    wire cond4 = ((in1[8:4] + in4[3:0]) > (in2[7:2] + in3[4:0]));
    wire cond5 = (in8 == in9);
    assign out1 = cond1 ? (in1[0] ^ in5[0]) : cond2 ? (in10[0] & ~in11[1]) : cond3 ? (in2[1] | in6[0]) : cond4 ? (in4[0] & in7[2]) : (in3[0] ^ in9[6]);
    assign out2 = cond5 ? (in8[3] ^ in9[6]) : ((in1[2] & in2[3]) ^ (in3[1] | in4[5]));

    wire [3:0] o3_if1 = (((in1[4:0]*3)+(in2[7:3]-(in4[2:0]<<1)))^(in5[3:0]+in10[1:0]));
    wire [3:0] o3_if2 = (((in6<<1)+(in7[4:0]^in8[6:2]))+(in9[5:2]+in11[1:0]));
    wire [3:0] o3_if3 = (((in1[3:0]^(in3[4:1]))+(in2[4:0]+in6[2:0]))^in10[1:0]);
    wire [3:0] o3_if4 = (((in4[5:2]+in7[6:0])-(in8[1:0]^in9[4:1]))+(in11<<1));
    wire [3:0] o3_else = (((in2[2:0]*in5[4:1])+(in6[5:3]+in1[8:6]))^(in3[2:0]+in4[1:0]));
    assign out3 = cond1 ? o3_if1 : cond2 ? o3_if2 : cond3 ? o3_if3 : cond4 ? o3_if4 : o3_else;

    wire [3:0] o4_if1 = (((in2[5:1]+in6[4:0])^(in7[3:0]*2))+(in8[6:2]-in5[2:0]));
    wire [3:0] o4_if2 = ((in1[4:1]+in3[8:5])^(in9[3:0]+in11[1:0]));
    wire [3:0] o4_if3 = (((in4[3:0]<<2)+(in1[6:2]&in2[8:4]))-(in7[6:3]+in8[2:0]));
    wire [3:0] o4_if4 = (((in5<<1)+in6[2:0])^(in10+in11))^in9[6:3];
    wire [3:0] o4_else = (((in3[4:1]-in4[8:5])+(in1[1:0]^in2[2:1]))+(in7[2:0]&in8[2:0]));
    assign out4 = cond1 ? o4_if1 : cond2 ? o4_if2 : cond3 ? o4_if3 : cond4 ? o4_if4 : o4_else;

    wire [3:0] o5_if1 = (((in1[3:0]^in2[4:1])+(in10^in11))+(in5[6:3]*in3[3:0]));
    wire [3:0] o5_if2 = ((in6[5:1]+(in7[6:2]<<1))^(in4[4:0]+in9[4:0]));
    wire [3:0] o5_if3 = (((in8[5:0]-in5[3:0])+(in2[8:5]-in3[4:1]))^in6[4:1]);
    wire [3:0] o5_if4 = ((in1[2:0]+in7[2:0])^(in8[1:0]*in9[6:3]));
    wire [3:0] o5_else = (((in10+in11)<<1)+(in3[1:0]+in4[2:0]));
    assign out5 = cond1 ? o5_if1 : cond2 ? o5_if2 : cond3 ? o5_if3 : cond4 ? o5_if4 : o5_else;

    wire [3:0] o6_if1 = (((in6[6:3]^in7[3:0])+(in1[2:0]*2))^(in2[8:5]-in3[4:1]));
    wire [3:0] o6_if2 = ((in8[2:0]+in9[3:1])^(in4[5:1]+in5[5:2]));
    wire [3:0] o6_if3 = (((in10[1:0]+in11[1:0])<<1)^(in1[4:1]+in2[4:1]));
    wire [3:0] o6_if4 = ((in6[2:0]+in7[2:0])+(in8[6:4]*in9[3:0]));
    wire [3:0] o6_else = ((in3[3:0]^in4[3:0])+(in5[6:3]&in6[3:1]));
    assign out6 = cond1 ? o6_if1 : cond2 ? o6_if2 : cond3 ? o6_if3 : cond4 ? o6_if4 : o6_else;

    wire [3:0] o7_if1 = (((in1*3)+(in2[4:0]<<2))-(in3[3:0]|in4[3:0]));
    wire [3:0] o7_if2 = (((in5[2:0]+in6[6:3])^(in7[3:0]|in8[6:3]))-(in10+in11));
    wire [3:0] o7_if3 = (((in9[6:3]&in4[8:5])-(in1[4:1]+in2[4:1]))^(in3[0]^in5[0]));
    wire [3:0] o7_if4 = (((in6[3:1]+in7[2:0])<<(in11[1]))+(in8[2:0]-in9[3:1]));
    wire [3:0] o7_else = (((in1[7:4] ^ in2[6:3]) + in3[4:1])^(in5[6:0]));
    assign out7 = cond1 ? o7_if1 : cond2 ? o7_if2 : cond3 ? o7_if3 : cond4 ? o7_if4 : o7_else;

    wire [3:0] o8_if1 = ((((in4>>2)+(in5[6:2]))^(in9[4:1]*2))+(in6[3:0]+in7[2:0]));
    wire [3:0] o8_if2 = (((in1[2:0]<<1)+(in2[3:1]<<1))^(in3[8:5]+in10[1:0]));
    wire [3:0] o8_if3 = (((in8[5:3]*3)-(in11[1:0]))^(in4[2:0]+in5[2:0]));
    wire [3:0] o8_if4 = ((((in1[8:4]^in2[7:3])-(in3[4:0]))+(in7[4:1])));
    wire [3:0] o8_else = (((in9[3:0]+in6[2:0])^(in10+in11))+(in8[2:0]));
    assign out8 = cond1 ? o8_if1 : cond2 ? o8_if2 : cond3 ? o8_if3 : cond4 ? o8_if4 : o8_else;

    wire [3:0] o9_if1 = (((in1[4:0]+in2[8:4])^(in3[3:1]|in4[3:1]))-(in5[6:3]+in10));
    wire [3:0] o9_if2 = (((in6[5:1]*in7[3:0])+(in8[6:2]<<1))^(in9[5:2]));
    wire [3:0] o9_if3 = (((in1[3:0]&in2[3:0])+(in3[8:5]^in5[4:1]))+in11);
    wire [3:0] o9_if4 = (((in4[5:0]+in6[6:1])^(in7[3:0]*3))+(in8[3:0]&in9[3:0]));
    wire [3:0] o9_else = (((in1[8:5]-in2[7:4])+(in5[2:0]<<1))^(in3[3:0]));
    assign out9 = cond1 ? o9_if1 : cond2 ? o9_if2 : cond3 ? o9_if3 : cond4 ? o9_if4 : o9_else;

    wire [3:0] o10_if1 = ((in4[2:0]^in5[3:1])+(in6[3:0]<<2));
    wire [3:0] o10_if2 = (((in7[6:0]-in8[5:0])^(in9[4:0]+in10[1:0]))-(in11));
    wire [3:0] o10_if3 = (((in1[4:1]*in2[4:1])+(in3[0]+in5[0]))-(in6[2:0]+in7[2:0]));
    wire [3:0] o10_if4 = (((in8[3:0]|in9[3:0])^(in4[8:5]<<1))+(in1[3:0]+in2[3:0]));
    wire [3:0] o10_else = (((in3[8:5]^in6[3:0])+(in7[3:0]*in9[6:3]))-(in1[7:4]+in2[6:3]));
    assign out10 = cond1 ? o10_if1 : cond2 ? o10_if2 : cond3 ? o10_if3 : cond4 ? o10_if4 : o10_else;

    wire [3:0] o11_if1 = (((in4[9:6]+in5[6:3])^(in6[1:0]*in10))+(in8[2:0]&in7[2:0]));
    wire [3:0] o11_if2 = ((((in9[6:0]<<1)+(in1[3:0]^in2[3:0]))^(in3[4:1]+in11)));
    wire [3:0] o11_if3 = (((in4[8:4]&in5[5:1])+(in6[5:1]<<1))-(in7[4:1]+in8[5:2]));
    wire [3:0] o11_if4 = ((in9[3:0]+(in1[2:0]*3))^(in2[4:0]+in3[8:5]));
    wire [3:0] o11_else = (((in10[1:0]+in11[1:0])+(in6[3:0]|in5[3:0]))^(in7[3:0]<<1));
    assign out11 = cond1 ? o11_if1 : cond2 ? o11_if2 : cond3 ? o11_if3 : cond4 ? o11_if4 : o11_else;
endmodule
