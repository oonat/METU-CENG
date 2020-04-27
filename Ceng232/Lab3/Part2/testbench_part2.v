`timescale 1ns / 1ps

module lab3_2_testbench;
    // Inputs
	reg [3:0] command;
	reg CLK;
	reg mode;

	// Outputs
	wire [7:0] total_time1;
    wire [7:0] total_time0;
    wire [7:0] total_cost1;
    wire [7:0] total_cost0;
    wire [3:2] coord_x;
    wire [1:0] coord_y;
    wire warning;
    
    real result = 0;
	// Instantiate the Unit Under Test (UUT)
	lab3_2 uut (
		.command(command), 
		.CLK(CLK),
		.mode(mode), 
		.total_time1(total_time1), 
		.total_time0(total_time0),
		.total_cost1(total_cost1),
        .total_cost0(total_cost0),
        .coord_x(coord_x),
        .coord_y(coord_y),
        .warning(warning)
	);
    
    // At 5, 15, 25, .. CLK will change 1->0 
    // At 10, 20, 30, .. CLK will change 0->1
    initial CLK = 1;
	always #5 CLK = ~CLK;

	initial begin
	$dumpfile("lab3_2.vcd");
	//$dumpvars(0,testbench_part2);
    //Time=%t $time, 
	$monitor("Your answers: command=%b mode=%b | coords=%d,%d | total_cost=%d%d | total_time=%d%d | warning=%b", command, mode, coord_x, coord_y, total_cost1, total_cost0, total_time1, total_time0, warning);

		// Add stimulus here
		command = 7; mode = 0;
		#10; // my reset  
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
        

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 9) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

        command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 9) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 13; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 9) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 9; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 0; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 12; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 9) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 7) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 9) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 9) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 1; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 5; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 7; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 1) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 3) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 3) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 4) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 5) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 6) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 2) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 4) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 7) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 6) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 8) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 4; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 8) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 9) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 6; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		


		command = 3; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 1) result = result + 1;
		if (coord_y == 1) result = result + 1;
		if (total_cost1 == 1) result = result + 1;
		if (total_cost0 == 5) result = result + 1;
        if (total_time1 == 1) result = result + 1;
        if (total_time0 == 2) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 1;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 1) result = result + 1;
		

		command = 11; mode = 1;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 1) result = result + 1;
		

		command = 8; mode = 0;
		#10; // Wait for clock edge
		if (coord_x == 2) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 2) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 1) result = result + 1;
        if (warning == 0) result = result + 1;
		

		command = 2; mode = 1;
		#10; // Wait for clock edge
		if (coord_x == 0) result = result + 1;
		if (coord_y == 0) result = result + 1;
		if (total_cost1 == 0) result = result + 1;
		if (total_cost0 == 0) result = result + 1;
        if (total_time1 == 0) result = result + 1;
        if (total_time0 == 0) result = result + 1;
        if (warning == 1) result = result + 1;
		
        $display("result =%d",result);
		
		#30;
		$finish;
        
	end
endmodule