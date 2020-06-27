`timescale 1ns / 1ps

module testbench_timekeeper;

    // Inputs
    reg clk;


    // Outputs
    wire [15:0] cur_time;

    // Instantiate the Unit Under Test (UUT)
    timekeeper uut (
        .clk(clk), 
        .cur_time(cur_time)
    );
    
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
    always #5 clk = ~clk;

    integer i;

    initial begin
       
        

        // Wait 5 ns for global reset to finish
        #5;
        
        // Add stimulus here
        
        for(i = 0; i<12; i=i+1) begin
        #10; // Wait for clock edge
        $display("timer: %d", cur_time);
        end


        $finish;
        
    end
  
      
endmodule


