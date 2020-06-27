module top (
	input sysclk,    // 1 MHz
	input button_in,
	input [15:0] student_id,
	output[3:0] D5_out,	
	output[3:0] D4_out,	
	output[3:0] D3_out,	
	output[3:0] D2_out,	
	output[3:0] D1_out		
);

wire button_clk, key_clk;
wire [15:0] new_hash;
wire [15:0] current_time;
wire display_button;

rtcClkDivider clk_divider(sysclk, button_clk, key_clk);

timekeeper time_gen(key_clk, current_time);

hasher key_gen(key_clk, current_time, student_id, new_hash);

buttonFsm fsm(button_clk, button_in, display_button);

b16toBCD screen(new_hash, display_button, D5_out, D4_out, D3_out, D2_out, D1_out);


endmodule