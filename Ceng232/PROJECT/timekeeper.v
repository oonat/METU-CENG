module timekeeper (
	input clk,    // Clock
	output[15:0] cur_time	
);

reg [15:0] time_reg;

initial begin
time_reg = 16'b0;
end

always@(posedge clk) begin
	if(time_reg == 16'hFFFF) begin
		time_reg = 16'b0;
	end
	else begin
		time_reg = time_reg + 16'd1;
	end
end

assign cur_time = time_reg;

endmodule