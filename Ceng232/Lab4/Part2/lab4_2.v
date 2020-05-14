`timescale 1ns / 1ps
module PharmacyMem(
	input [4:0] studentID ,
    input clk,
    input [1:0] mode , // 0: list, 2: checkIn, 3: delete
    input [7:0] checkInTime,
    output reg [4:0] listOutput,
    output reg listBusy ,
    output reg ready
	);

//Write your code below
//
//	
reg [0:3] heap_size;
reg [0:3] hole;
reg [0:3] list_index;
reg [0:3] child;

reg [4:0] id_tmp;
reg [7:0] check_tmp;

reg [4:0] id_mem [0:10];
reg [7:0] checkin_mem [0:10];

integer i;

initial begin
    id_mem[0] <= 5'b0;
	id_mem[1] <= 5'b0;
	id_mem[2] <= 5'b0;
	id_mem[3] <= 5'b0;
	id_mem[4] <= 5'b0;
	id_mem[5] <= 5'b0;
	id_mem[6] <= 5'b0;
	id_mem[7] <= 5'b0;
	id_mem[8] <= 5'b0;
	id_mem[9] <= 5'b0;
	id_mem[10] <= 5'b0;
	checkin_mem[0] <= 8'b0;
	checkin_mem[1] <= 8'b0;
	checkin_mem[2] <= 8'b0;
	checkin_mem[3] <= 8'b0;
	checkin_mem[4] <= 8'b0;
	checkin_mem[5] <= 8'b0;
	checkin_mem[6] <= 8'b0;
	checkin_mem[7] <= 8'b0;
	checkin_mem[8] <= 8'b0;
	checkin_mem[9] <= 8'b0;
	checkin_mem[10] <= 8'b0;
	heap_size <= 4'b0;
	list_index <= 4'b0001;
	ready <= 1;
	listBusy <= 0;
end

always@(posedge clk) begin
   if(mode == 2'b10) begin
	   listBusy = 0;
	   list_index = 4'b0001;
	   ready = 1;

	   if(heap_size < 4'b1010) begin
	   		heap_size = heap_size + 1;
		    hole = heap_size;
		    for(i = 12; i > 0; i = i - 1) begin
		   		if(checkin_mem[hole/2] > checkInTime) begin
			     	checkin_mem[hole] = checkin_mem[hole/2];
				  	id_mem[hole] = id_mem[hole/2];
				  	hole = hole/2;
				end
			end
			checkin_mem[hole] = checkInTime;
			id_mem[hole] = studentID;
		end
   end
	
   else if(mode == 2'b11) begin
	   listBusy = 0;
	   list_index = 4'b0001;
	   ready = 1;

	   	if(heap_size > 4'b0) begin
		    if(heap_size == 4'b0001) begin
			    checkin_mem[1] = 8'b0;
				id_mem[1] = 5'b0;
				heap_size = 4'b0;
			end
			else begin
				checkin_mem[1] = checkin_mem[heap_size];
				id_mem[1] = id_mem[heap_size];
				id_tmp = id_mem[heap_size];
				check_tmp = checkin_mem[heap_size];

				heap_size = heap_size - 1;
				hole = 4'b0001;

				for(i = 12; i > 0; i = i - 1) begin
					if(hole*2 <= heap_size) begin
						child = hole*2;

						if(child != heap_size && checkin_mem[child + 1] < checkin_mem[child]) begin
							child = child + 1;
						end
					
						if(checkin_mem[child] < check_tmp) begin
							checkin_mem[hole] = checkin_mem[child];
							id_mem[hole]  = id_mem[child];
							hole = child;
						end
					end
				end

				checkin_mem[hole] = check_tmp;
				id_mem[hole]  = id_tmp;
			end
			  
		end
	end
	
	else if(mode == 2'b00) begin
	   if(heap_size > 4'b0 && list_index <= heap_size) begin
		ready = 0;
		listBusy = 1;
		listOutput = id_mem[list_index];
		list_index = list_index+1;
      end
      else begin
		ready = 1;
		listBusy = 0;
		list_index = 4'b0001;
      end		
	end
	
end

endmodule