`timescale 1ns / 1ps

module AddParity(
input [1:8] dataIn,
output reg [1:12] dataOut
);

//Write your code below
//
//

always@(*) begin
   dataOut[3] <= dataIn[1];
   dataOut[5:7] <= dataIn[2:4];
   dataOut[9:12] <= dataIn[5:8];

   dataOut[1] <= dataIn[1]^dataIn[2]^dataIn[4]^dataIn[5]^dataIn[7];
   dataOut[2] <= dataIn[1]^dataIn[3]^dataIn[4]^dataIn[6]^dataIn[7];
   dataOut[4] <= dataIn[2]^dataIn[3]^dataIn[4]^dataIn[8];
   dataOut[8] <= dataIn[5]^dataIn[6]^dataIn[7]^dataIn[8];
end

endmodule


module CheckParity(
input [1:12] dataIn,
output reg [1:8] dataOut
);

//Write your code below
//
//
wire c1,c2,c4,c8;

assign c1 = dataIn[1]^dataIn[3]^dataIn[5]^dataIn[7]^dataIn[9]^dataIn[11];
assign c2 = dataIn[2]^dataIn[3]^dataIn[6]^dataIn[7]^dataIn[10]^dataIn[11];
assign c4 = dataIn[4]^dataIn[5]^dataIn[6]^dataIn[7]^dataIn[12];
assign c8 = dataIn[8]^dataIn[9]^dataIn[10]^dataIn[11]^dataIn[12];

always@(*) begin
   case ({c8,c4,c2,c1})
      4'b0011  : dataOut <= {(~dataIn[3]),dataIn[5],dataIn[6],dataIn[7],dataIn[9],dataIn[10],dataIn[11],dataIn[12]};
      4'b0101  : dataOut <= {dataIn[3],(~dataIn[5]),dataIn[6],dataIn[7],dataIn[9],dataIn[10],dataIn[11],dataIn[12]};
      4'b0110  : dataOut <= {dataIn[3],dataIn[5],(~dataIn[6]),dataIn[7],dataIn[9],dataIn[10],dataIn[11],dataIn[12]}; 
		4'b0111  : dataOut <= {dataIn[3],dataIn[5],dataIn[6],(~dataIn[7]),dataIn[9],dataIn[10],dataIn[11],dataIn[12]};
		4'b1001  : dataOut <= {dataIn[3],dataIn[5],dataIn[6],dataIn[7],(~dataIn[9]),dataIn[10],dataIn[11],dataIn[12]};
		4'b1010  : dataOut <= {dataIn[3],dataIn[5],dataIn[6],dataIn[7],dataIn[9],(~dataIn[10]),dataIn[11],dataIn[12]};
		4'b1011  : dataOut <= {dataIn[3],dataIn[5],dataIn[6],dataIn[7],dataIn[9],dataIn[10],(~dataIn[11]),dataIn[12]};
		4'b1100  : dataOut <= {dataIn[3],dataIn[5],dataIn[6],dataIn[7],dataIn[9],dataIn[10],dataIn[11],(~dataIn[12])};
      default : dataOut <= {dataIn[3],dataIn[5],dataIn[6],dataIn[7],dataIn[9],dataIn[10],dataIn[11],dataIn[12]};
   endcase	
end


endmodule


module RAM(
input [7:0] dataIn, //0:read, 1:write
input clk,
input mode,
input [3:0] addr,
output reg [7:0] dataOut);

//Write your code below
//
//
reg [7:0] mem [0:15];

initial begin
mem[0] = 8'b0;
mem[1] = 8'b0;
mem[2] = 8'b0;
mem[3] = 8'b0;
mem[4] = 8'b0;
mem[5] = 8'b0;
mem[6] = 8'b0;
mem[7] = 8'b0;
mem[8] = 8'b0;
mem[9] = 8'b0;
mem[10] = 8'b0;
mem[11] = 8'b0;
mem[12] = 8'b0;
mem[13] = 8'b0;
mem[14] = 8'b0;
mem[15] = 8'b0;
end

always@(posedge clk)
begin

if(mode == 0) begin
   dataOut <= mem[addr];
end
else begin
   mem[addr] <= dataIn;
end

end

endmodule

module SEC_MEM(
input [1:12] dataIn,
input clk,
input mode, //0:read, 1:write
input [3:0] addr,
output  [1:12] dataOut);

//DO NOT EDIT THIS MODULE
wire  [7:0]  ramDataIn;
wire  [7:0]  ramDataOut;
CheckParity CP(dataIn,ramDataIn);
RAM RM(ramDataIn, clk, mode, addr, ramDataOut);
AddParity AP(ramDataOut,dataOut);

endmodule
