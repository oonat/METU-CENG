`timescale 1ns / 1ps

module testbench_buttonfsm;

    // Inputs
    reg clk;
    reg button;


    // Outputs
    wire stateful_button;

    // Instantiate the Unit Under Test (UUT)
    buttonFsm uut (
        .clk(clk), 
        .button(button), 
        .stateful_button(stateful_button)
    );
    
    // At 5, 15, 25, .. clk will change 1->0 
    // At 10, 20, 30, .. clk will change 0->1
    initial clk = 1;
    always #10 clk = ~clk;


    initial begin

    $dumpfile("test.vcd");
    $dumpvars(0,testbench_buttonfsm);
       
        
        
        // Add stimulus here
        button = 0;
        #3;
        button = 1;
        #3; 
        button = 0;
        #3;
        button = 1;
        #3; 
        button = 0;
        #3;
		  button = 1;
        #3; 
        button = 0;
        #1;
		  button = 1;
		  #52;
		  button = 0;
		  #3;
		  button = 1;
		  #3;
		  button = 0;
		  #3;
		  button = 1;
		  #3;
		  button = 0;
		  #3;
		  button = 1;
		  #2;
		  button = 0;
		  #15;
		  button = 1;
		  #3;
		  button = 0;
		  #3;
		  button = 1;
		  #3;
		  button = 0;
		  #3;
		  button = 1;
		  #2;
		  button = 0;
		  #2;
		  button = 1;
		  #52;
		  button = 0;
		  #3;
		  button = 1;
		  #3;
		  button = 0;
		  #3;
		  button = 1;
		  #3;
		  button = 0;
		  #30;

		  
        $finish;
        
    end
  
      
endmodule


