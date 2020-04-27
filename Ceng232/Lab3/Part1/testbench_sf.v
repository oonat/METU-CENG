`timescale 1ns / 1ps
module test_sf;

	// Inputs
	reg S;
	reg F;
	reg clk;

	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	sf uut (
		.S(S), 
		.F(F), 
		.clk(clk),
		.Q(Q)
	);
    
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
	always #5 clk = ~clk;

	initial begin
        // set monitor to inputs and outputs
		$monitor("Time=%t | S=%b F=%b| Q=%b", $time, S, F, Q);
        
		// Initialize Inputs
		S = 0;
		F = 0;

		// Wait 5 ns for global reset to finish
		#5;
        
		// Add stimulus here
        
		S= 0; F= 1;
		#10; // Wait for clock edge
		if (Q != 1) $display("Value of Q after S= 0 F= 1 is wrong");
		else $display("Successful");
		S= 1; F= 1;
		#10; // Wait for clock edge
		if (Q != 0) $display("Value of Q after S= 1 F= 1 is wrong");
		else $display("Successful");
		S= 0; F= 1;
		#10; // Wait for clock edge
		if (Q != 1) $display("Value of Q after S= 0 F= 1 is wrong");
		else $display("Successful");
		S= 1; F= 0;
		#10; // Wait for clock edge
		if (Q != 1) $display("Value of Q after S= 1 F= 0 is wrong");
		else $display("Successful");
		S= 0; F= 0;
		#10; // Wait for clock edge
		if (Q != 0) $display("Value of Q after S= 0 F= 1 is wrong");
		else $display("Successful");
		S= 1; F= 1;
		#10; // Wait for clock edge
		if (Q != 1) $display("Value of Q after S= 1 F= 1 is wrong");
		else $display("Successful");
		$finish;
        
	end
      
endmodule
