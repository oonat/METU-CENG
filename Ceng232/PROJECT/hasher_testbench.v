`timescale 1ns / 1ps

module testbench_hasher;

    // Inputs
    reg clk;
    reg [15:0] cur_time;
    reg [15:0] student_id;


    // Outputs
    wire [15:0] cur_hash;

    // Instantiate the Unit Under Test (UUT)
    hasher uut (
        .clk(clk), 
        .cur_time(cur_time), 
        .student_id(student_id),
        .cur_hash(cur_hash)
    );
    
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
    always #5 clk = ~clk;
    always #5 cur_time = cur_time + 16'd5;

    integer i;

    initial begin
       
        
        // Initialize Inputs
        cur_time = 16'd0;

        // Wait 5 ns for global reset to finish
        #5;
        
        // Add stimulus here
        
        for(i = 0; i<12; i=i+1) begin
        $display("new_hash: %b, time: %b", cur_hash, cur_time);
        #10; // Wait for clock edge
        end


        $finish;
        
    end
  
      
endmodule


