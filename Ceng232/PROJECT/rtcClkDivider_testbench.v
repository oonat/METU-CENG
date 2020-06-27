`timescale 1ns / 1ps

module rtcClkDivider_testbench;
 

	reg sys_clk;

	wire clk_500Hz;
	wire clk_5s;



 // Test the clock divider in Verilog
 rtcClkDivider uut (
  .sys_clk(sys_clk), 
  .clk_500Hz(clk_500Hz),
  .clk_5s(clk_5s)
 );

 initial begin
  

  sys_clk = 1;
  
      
        forever #10 sys_clk = ~sys_clk;
 end
      
endmodule

