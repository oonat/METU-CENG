`timescale 1ns / 1ps 
module lab3_2(
			input[3:0] command,
			input CLK, 
			input mode,
			output reg [7:0] total_time1,
			output reg [7:0] total_time0,
			output reg [7:0] total_cost1,
			output reg [7:0] total_cost0,
			output reg [3:2] coord_x,
			output reg [1:0] coord_y,
			output reg warning
    );

   //Modify the lines below to implement your design .

	
	
	initial begin
	coord_x = 2'b01;
	coord_y = 2'b01;
	total_time1 = 8'b0;
	total_time0 = 8'b0;
	total_cost1 = 8'b0;
	total_cost0 = 8'b0;
	end
	

	always@(posedge CLK)
	begin
	if(mode == 0)
	   begin
		   warning <= 1'b0;

		   total_time1 <= (((((10*total_time1)+total_time0+1)<20)?((10*total_time1)+total_time0+1):(((10*total_time1)+total_time0+1)-20))<10)?0:1;

		   total_time0 <= (((((10*total_time1)+total_time0+1)<20)?((10*total_time1)+total_time0+1):(((10*total_time1)+total_time0+1)-20))<10)?((((10*total_time1)+total_time0+1)<20)?((10*total_time1)+total_time0+1):(((10*total_time1)+total_time0+1)-20)):(((((10*total_time1)+total_time0+1)<20)?((10*total_time1)+total_time0+1):(((10*total_time1)+total_time0+1)-20))-10);

			if(command == 4'b0000)
			   begin
			   coord_x <= coord_x;
			   coord_y <= coord_y;
			   total_cost1 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?0:1;

               total_cost0 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20)):(((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))-10);
			   end
			else if(command == 4'b0001)
			   begin
			   if(coord_x == 2'b00 || coord_y == 2'b10)
			      begin
			      coord_x <= coord_x;
			      coord_y <= coord_y;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20)):(((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))-10);
                  end
               else
                  begin
                  coord_x <= coord_x-1;
			      coord_y <= coord_y+1;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20)):(((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))-10);
                  end
			   end
	        else if(command == 4'b0010)
	           begin
	           coord_x <= coord_x;
			   coord_y <= (coord_y==2'b10)?(2'b00):(coord_y+1);
			   total_cost1 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?0:1;

               total_cost0 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20)):(((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))-10);
	           end
	        else if(command == 4'b0011)
	           begin
			   if(coord_x == 2'b10 || coord_y == 2'b10)
			      begin
			      coord_x <= coord_x;
			      coord_y <= coord_y;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20)):(((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))-10);
                  end
               else
                  begin
                  coord_x <= coord_x+1;
			      coord_y <= coord_y+1;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20)):(((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))-10);
                  end
			   end
			else if(command == 4'b0100)
			   begin
	           coord_x <= (coord_x==2'b10)?(2'b00):(coord_x+1);
			   coord_y <= coord_y;
			   total_cost1 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?0:1;

               total_cost0 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20)):(((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))-10);
	           end
	        else if(command == 4'b0101)
	           begin
			   if(coord_x == 2'b10 || coord_y == 2'b00)
			      begin
			      coord_x <= coord_x;
			      coord_y <= coord_y;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20)):(((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))-10);
                  end
               else
                  begin
                  coord_x <= coord_x+1;
			      coord_y <= coord_y-1;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20)):(((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))-10);
                  end
			   end
			else if(command == 4'b0110)
			   begin
	           coord_x <= coord_x;
			   coord_y <= (coord_y==2'b00)?(2'b10):(coord_y-1);
			   total_cost1 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?0:1;

               total_cost0 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20)):(((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))-10);
	           end
	        else if(command == 4'b0111)
	           begin
			   if(coord_x == 2'b00 || coord_y == 2'b00)
			      begin
			      coord_x <= coord_x;
			      coord_y <= coord_y;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))<10)?((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20)):(((((10*total_cost1)+total_cost0+1)<20)?((10*total_cost1)+total_cost0+1):(((10*total_cost1)+total_cost0+1)-20))-10);
                  end
               else
                  begin
                  coord_x <= coord_x-1;
			      coord_y <= coord_y-1;
			      total_cost1 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?0:1;

                  total_cost0 <= (((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))<10)?((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20)):(((((10*total_cost1)+total_cost0+3)<20)?((10*total_cost1)+total_cost0+3):(((10*total_cost1)+total_cost0+3)-20))-10);
                  end
			   end
			else if(command == 4'b1000)
			   begin
	           coord_x <= (coord_x==2'b00)?(2'b10):(coord_x-1);
			   coord_y <= coord_y;
			   total_cost1 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?0:1;

               total_cost0 <= (((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))<10)?((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20)):(((((10*total_cost1)+total_cost0+2)<20)?((10*total_cost1)+total_cost0+2):(((10*total_cost1)+total_cost0+2)-20))-10);
	           end
	        else
	           begin
	           coord_x <= coord_x;
			   coord_y <= coord_y;
			   total_cost1 <= total_cost1;
               total_cost0 <= total_cost0;
	           end
				
	    end
	
	else	
	begin
	coord_x <= 2'b00;
	coord_y <= 2'b00;
	total_time1 <= 8'b0;
	total_time0 <= 8'b0;
	total_cost1 <= 8'b0;
	total_cost0 <= 8'b0;
	warning <= 1'b1;
	end
	
	end
	
	

endmodule