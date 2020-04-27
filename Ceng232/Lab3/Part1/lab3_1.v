`timescale 1ns / 1ps

module sf(
    input S,
    input F,
    input clk,
    output reg Q
    );
    
    initial begin
        Q = 0;
    end
	
    // write your code here
    always@(posedge clk)
    begin
        case ({S,F})
          2'b00  : Q <= 0;
          2'b01  : Q <= 1;
          2'b10  : Q <= Q;
          2'b11  : Q <= ~Q;
        endcase
    end
	 
endmodule


module ic1500(
    input B, 
    input A, 
    input X, 
	 input clk,
	 output D0,
	 output D1,
	 output Q,
    output Z
    );
    // write your code here	

   assign D1 = (A&(~B)&(~X)) | ((~A)&B&(~X));

   assign D0 = (A&(~B)) | X;

   sf sf_ff(D1,D0,clk,Q);

   assign Z = Q&X;	 
	
endmodule