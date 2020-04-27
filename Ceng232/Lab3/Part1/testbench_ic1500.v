`timescale 1ns / 1ps

module testbench_ic1500;

	// Inputs
	reg B;
	reg A;
	reg X;
	reg clk;

	// Outputs
	wire D0;
	wire D1;
	wire Q;
	wire Z;

	// Instantiate the Unit Under Test (UUT)
	ic1500 uut (
		.B(B), 
		.A(A), 
		.X(X),
		.clk(clk),
		.D0(D0), 
		.D1(D1), 
		.Q(Q),
		.Z(Z)
	);
	
	// At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
	always #5 clk = ~clk;

	initial begin
        // set monitor to inputs and outputs
		$monitor("Time=%t | D0=%b D1=%b Q=%b Z=%b", $time, D0, D1, Q, Z);
        
		// Initialize Inputs
		B = 0;
		A = 0;
		X = 0;

		// Wait 5 ns for global reset to finish
		#5;
        
		// Add stimulus here
        
		B = 0; A = 0; X = 0;
		#10; // Wait for clock edge
		if (D0 == 0 && D1 == 0 && Q == 0 && Z == 0) $display("Successful");
		else $display("Value of B = 0 A = 0 X = 0  is wrong");
		B = 0; A = 0; X = 1;
		#10; // Wait for clock edge
		if (D0 == 1 && D1 == 0 && Q == 1 && Z == 1) $display("Successful");
		else $display("Value of B = 0 A = 0 X = 1  is wrong");
		B = 0; A = 1; X = 0;
		#10; // Wait for clock edge
		if (D0 == 1 && D1 == 1 && Q == 0 && Z == 0) $display("Successful");
		else $display("Value of B = 0 A = 1 X = 0  is wrong");
		B = 0; A = 1; X = 1;
		#10; // Wait for clock edge
		if (D0 == 1 && D1 == 0 && Q == 1 && Z == 1) $display("Successful");
		else $display("Value of B = 0 A = 1 X = 1  is wrong");
		B = 1; A = 0; X = 0;
		#10; // Wait for clock edge
		if (D0 == 0 && D1 == 1 && Q == 1 && Z == 0) $display("Successful");
		else $display("Value of B = 1 A = 0 X = 0  is wrong");
		B = 1; A = 0; X = 1;
		#10; // Wait for clock edge
		if (D0 == 1 && D1 == 0 && Q == 1 && Z == 1) $display("Successful");
		else $display("Value of B = 1 A = 0 X = 1  is wrong");
		B = 1; A = 1; X = 0;
		#10; // Wait for clock edge
		if (D0 == 0 && D1 == 0 && Q == 0 && Z == 0) $display("Successful");
		else $display("Value of B = 1 A = 1 X = 0  is wrong");
		B = 1; A = 1; X = 1;
		#10; // Wait for clock edge
		if (D0 == 1 && D1 == 0 && Q == 1 && Z == 1) $display("Successful");
		else $display("Value of B = 1 A = 1 X = 1  is wrong");
		$finish;
        
	end
  
      
endmodule


