module b16toBCD (
	input [15:0] to_display,
	input enable,
	output [3:0] D5,	
	output [3:0] D4,	
	output [3:0] D3,	
	output [3:0] D2,	
	output [3:0] D1	
);

integer i;
reg [3:0] arr [0:4];
reg [15:0] num;

initial begin
	arr[0] = 4'b1111;
	arr[1] = 4'b1111;
	arr[2] = 4'b1111;
	arr[3] = 4'b1111;
	arr[4] = 4'b1111;
end

always@(enable or to_display) begin
	if(enable == 0) begin
		arr[0] = 4'b1111;
		arr[1] = 4'b1111;
		arr[2] = 4'b1111;
		arr[3] = 4'b1111;
		arr[4] = 4'b1111;
	end
	else begin
		num = to_display;

		for(i = 0; i < 5; i = i + 1) begin
			arr[i] = num % 10;
			num = num/10;
		end
	end			
end

assign D5 = arr[4];
assign D4 = arr[3];
assign D3 = arr[2];
assign D2 = arr[1];
assign D1 = arr[0];


endmodule