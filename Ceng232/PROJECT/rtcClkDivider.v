module rtcClkDivider (
	input sys_clk,    // 1 MHz
	output clk_500Hz, // 500 Hz
	output clk_5s  // 0.2 Hz
);

parameter KEYCHANGE_PERIOD = 5;  // DO NOT CHANGE THE NAME OF THIS PARAMETER 
// AND MAKE SURE TO USE THIS PARAMETER INSTEAD OF HARDCODING OTHER VALUES

reg [10:0] counter_stat;
reg [399:0] counter_dyn;


initial begin
counter_stat = 11'd0;
counter_dyn = 400'd0;
end

always@(posedge sys_clk) begin

	if(counter_stat < 11'd1999) begin
		counter_stat = counter_stat + 11'd1;
	end
	else begin
		counter_stat = 11'd0;
	end

	if(counter_dyn < (KEYCHANGE_PERIOD*1000000 - 1)) begin
		counter_dyn = counter_dyn + 400'd1;
	end
	else begin
		counter_dyn = 400'd0;
	end
	
end


assign clk_500Hz = (counter_stat < 11'd1000)?1'b0:1'b1;
assign clk_5s = (counter_dyn < (KEYCHANGE_PERIOD*500000))?1'b0:1'b1;


endmodule