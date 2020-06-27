`timescale 1ns / 1ps
module test_b16toBCD;


    // Inputs
    reg [15:0] to_display;
    reg enable;

    // Outputs
    wire [3:0] D5;
    wire [3:0] D4;
    wire [3:0] D3;
    wire [3:0] D2;
    wire [3:0] D1;

    // Instantiate the Unit Under Test (UUT)
    b16toBCD uut (
        .to_display(to_display), 
        .enable(enable), 
        .D5(D5),
        .D4(D4),
        .D3(D3),
        .D2(D2),
        .D1(D1)
    );
    


    initial begin
        
        // Initialize Inputs
        to_display = 16'b0;
        enable = 1;

        // Wait 5 ns for global reset to finish
        #5;
        
        // Add stimulus here
        
        to_display = 16'd58039; enable = 1;
        #10; // Wait for clock edge
        $display("D5: %d D4: %d D3: %d D2: %d D1: %d", D5 ,D4, D3, D2, D1);
		  
		  to_display = 16'd58039; enable = 0;
        #10; // Wait for clock edge
        $display("D5: %d D4: %d D3: %d D2: %d D1: %d", D5 ,D4, D3, D2, D1);
		  
		  to_display = 16'd32; enable = 1;
        #10; // Wait for clock edge
        $display("D5: %d D4: %d D3: %d D2: %d D1: %d", D5 ,D4, D3, D2, D1);
       

        $finish;
        
    end
      
endmodule
