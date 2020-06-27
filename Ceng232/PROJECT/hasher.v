module hasher (
	input clk,    // Clock
	input [15:0] cur_time,
	input [15:0] student_id,
	output [15:0] cur_hash	
);

reg [31:0]  prev_hash;
reg [15:0]  current_hash;

initial begin
prev_hash = 32'b0;
current_hash = 16'b0;
end


always@(posedge clk) begin

prev_hash = current_hash;
prev_hash = ((cur_time ^ student_id) - prev_hash);
prev_hash = (prev_hash)*(prev_hash);
prev_hash = ((prev_hash >> 8) & 16'hFFFF);
current_hash = prev_hash;

end

assign cur_hash = current_hash;


endmodule

