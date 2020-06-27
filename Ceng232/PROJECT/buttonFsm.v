module buttonFsm (
	input clk,
	input button,    
	output stateful_button
);

reg [1:0] cur_state;
reg output_sign;

initial begin
cur_state = 2'b00;
output_sign = 0;
end

always@(cur_state or button) begin
	case(cur_state)
		2'b00 : begin
					if(button == 1) begin
						output_sign = 1;
					end
					else begin
						output_sign = 0;
					end
				end
		2'b01 : begin
					output_sign = 1;
				end
		2'b10 : begin
					output_sign = 0;
				end
		2'b11 : begin
					if(button == 1) begin
						output_sign = 0;
					end
					else begin
						output_sign = 1;
					end
				end
	endcase
end

always@(posedge clk) begin
	case(cur_state)
		2'b00 : begin
					if(button == 1) begin
						cur_state = 2'b01;
					end
				end
		2'b01 : begin
					if(button == 1) begin
						cur_state = 2'b01;
					end
					else begin
						cur_state = 2'b11;
					end
				end
		2'b10 : begin
					if(button == 1) begin
						cur_state = 2'b10;
					end
					else begin
						cur_state = 2'b00;
					end
				end
		2'b11 : begin
					if(button == 1) begin
						cur_state = 2'b10;
					end
				end
	endcase
end

assign stateful_button = output_sign;

endmodule
