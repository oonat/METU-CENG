#include <sys/socket.h>
#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

// os libs
#include <wait.h>
#include <unistd.h>

// hw libs
#include "message.h"
#include "logging.h"

#include <stdio.h>
#include <stdlib.h>


typedef struct{
	int fd;
	pid_t pid;
	coordinate coord;
}Player;

typedef struct{
	int fd;
	pid_t pid;
	char symbol;
	coordinate coord;
	bool alive;
}Monster;

void create_player();
Monster create_monster(int num);
int cmpfunc(const void * a, const void * b);
void check_ready();
void end_of_the_game();
void sent_player_message(int player_total_damage);
bool is_coordinate_valid(coordinate coord);
void sort_and_update_map();


map_info* mapdetails;
Player* player;
int initial_monster_num;
int alive_monster_num;
Monster* monster_arr;


int main(void) {

	mapdetails = (map_info*) malloc(sizeof(map_info));
	scanf("%d %d", &(mapdetails->map_width), &(mapdetails->map_height));

	create_player();

	scanf("%d", &initial_monster_num);
	alive_monster_num = initial_monster_num;
	monster_arr = (Monster*) calloc(alive_monster_num, sizeof(Monster));
	for(int i = 0; i < alive_monster_num; i++){
		monster_arr[i] = create_monster(i);
	}


	check_ready();

	sort_and_update_map();
	print_map(mapdetails);



	int player_total_damage = 0;
	int is_left;
	while(1){
		player_response p_resp;
		sent_player_message(player_total_damage);
		is_left = read(player->fd, &p_resp, sizeof(player_response));
		
		if(is_left == 0){
			// left
			waitpid(player->pid, NULL, 0);
			close(player->fd);
			end_of_the_game(3);
		}else if(p_resp.pr_type == 3){
			// dead
			waitpid(player->pid, NULL, 0);
			close(player->fd);
			end_of_the_game(2);
		}else if(p_resp.pr_type == 1){
			// move
			if(p_resp.pr_content.move_to.x == mapdetails->door.x && p_resp.pr_content.move_to.y == mapdetails->door.y){
				player->coord = p_resp.pr_content.move_to;
				end_of_the_game(0);
			}else if(is_coordinate_valid(p_resp.pr_content.move_to))
				player->coord = p_resp.pr_content.move_to;
		}


		for(int i = 0; i < alive_monster_num; i++){
			monster_message m_message;
			m_message.new_position = monster_arr[i].coord;
			m_message.damage = (p_resp.pr_type == 2) ? p_resp.pr_content.attacked[i] : 0;
			m_message.player_coordinate = player->coord;
			m_message.game_over = false;
			write(monster_arr[i].fd, &m_message, sizeof(monster_message));
		}

		player_total_damage = 0;

		for(int i = 0; i < mapdetails->alive_monster_count; i++){
			monster_response m_resp;
			read(monster_arr[i].fd, &m_resp, sizeof(monster_response));

			if(m_resp.mr_type == 3){
				// dead
				waitpid(monster_arr[i].pid, NULL, 0);
				close(monster_arr[i].fd);
				monster_arr[i].alive = false;
				alive_monster_num--;
				if(alive_monster_num == 0)
					end_of_the_game(1);
			}else if(m_resp.mr_type == 1){
				// move
				if(is_coordinate_valid(m_resp.mr_content.move_to))
					monster_arr[i].coord = m_resp.mr_content.move_to;
			}else if(m_resp.mr_type == 2){
				// attack
				player_total_damage += m_resp.mr_content.attack;
			}
		}


		sort_and_update_map();
		print_map(mapdetails);
	}


	return 0;
}



void create_player(){

	pid_t player_pid;
	int player_x, player_y;
	char* player_path;
	char* player_args[3];

	char* door_x_string, *door_y_string;
	scanf("%ms %ms", &door_x_string, &door_y_string);
	sscanf(door_x_string,"%d", &(mapdetails->door.x));
	sscanf(door_y_string,"%d", &(mapdetails->door.y));

	scanf("%d %d", &player_x, &player_y);
	scanf("%ms %ms %ms %ms", &player_path, &player_args[0], &player_args[1], &player_args[2]);

	char* args[] = {player_path, door_x_string, door_y_string, player_args[0], player_args[1], player_args[2], NULL};

	int fd[2];
	PIPE(fd);

	if(!(player_pid = fork())){

		close(fd[0]);
		// socket is both for stdin and stdout
		dup2(fd[1], 0);
		dup2(fd[1], 1);
		close(fd[1]);

		execv(args[0], args);
	}

	close(fd[1]);

	for(int i = 0; args[i] != NULL; i++)
		free(args[i]);


	player = (Player*)malloc(sizeof(Player));

	player->fd = fd[0];
	player->pid = player_pid; 
	coordinate coord = {player_x, player_y};
	player->coord = coord;

}


Monster create_monster(int num){
	pid_t monster_pid;
	char* monster_path;
	char symbol;
	int monster_x, monster_y;
	char* monster_args[4];

	scanf("%ms %c %d %d %ms %ms %ms %ms", &monster_path, &symbol, &monster_x, &monster_y, &monster_args[0], &monster_args[1], &monster_args[2], &monster_args[3]);
	char* args[] = {monster_path, monster_args[0], monster_args[1], monster_args[2], monster_args[3], NULL};


	int fd[2];
	PIPE(fd);

	if(!(monster_pid = fork())){

		close(fd[0]);
		// socket is both for stdin and stdout
		dup2(fd[1], 0);
		dup2(fd[1], 1);
		close(fd[1]);

		close(player->fd);

		for(int i = 0; i < num; i++)
			close(monster_arr[i].fd);

		execv(args[0], args);
	}

	close(fd[1]);

	for(int i = 0; args[i] != NULL; i++)
		free(args[i]);

	Monster monster;

	monster.fd = fd[0];
	monster.pid = monster_pid; 
	monster.symbol = symbol;
	coordinate coord = {monster_x, monster_y};
	monster.coord = coord;
	monster.alive = true;

	return monster;

}


int cmpfunc(const void * a, const void * b){
	coordinate coord_a = ((Monster*) a)->coord;
	bool a_alive = ((Monster*) a)->alive;
	coordinate coord_b = ((Monster*) b)->coord;
	bool b_alive = ((Monster*) b)->alive;

	if(a_alive == true && b_alive == false) 
		return -1;

	if(a_alive == false && b_alive == true) 
		return 1;

	if(coord_a.x == coord_b.x)
		return coord_a.y - coord_b.y;

	return coord_a.x - coord_b.x;
}


void check_ready(){

	while(true){
		player_response p_resp;
		read(player->fd, &p_resp, sizeof(player_response));
		if(p_resp.pr_type == 0)
			break;
	}

	for(int i = 0; i < alive_monster_num; i++){
		while(true){
			monster_response m_resp;
			read(monster_arr[i].fd, &m_resp, sizeof(monster_response));
			if(m_resp.mr_type == 0)
				break;
		}
	}

}


void end_of_the_game(game_over_status end_status){

	sort_and_update_map();
	print_map(mapdetails);
	print_game_over(end_status);

	// reached or survived
	if(end_status == 0 || end_status == 1){
		player_message p_message;
		p_message.game_over = true;
		write(player->fd, &p_message, sizeof(player_message));
		waitpid(player->pid, NULL, 0);
		close(player->fd);
	}


	monster_message m_message;
	m_message.game_over = true;
	for(int i = 0; i < alive_monster_num; i++){
		write(monster_arr[i].fd, &m_message, sizeof(monster_message));
		waitpid(monster_arr[i].pid, NULL, 0);
		close(monster_arr[i].fd);
	}

	free(player);
	free(mapdetails);
	free(monster_arr);

	exit(0);
}


void sent_player_message(int player_total_damage){
	player_message message_to_player;
	message_to_player.new_position = player->coord;
	message_to_player.total_damage = player_total_damage;
	message_to_player.alive_monster_count = alive_monster_num;

	for(int i = 0; i < alive_monster_num; i++){
		message_to_player.monster_coordinates[i] = monster_arr[i].coord;
	}

	message_to_player.game_over = false;
	write(player->fd, &message_to_player, sizeof(player_message));
}



bool is_coordinate_valid(coordinate coord){
	if(coord.x == mapdetails->door.x && coord.y == mapdetails->door.y){
		return false;
	}else if(coord.x <= 0 || coord.x >= (mapdetails->map_width-1) || coord.y <= 0 || coord.y >= (mapdetails->map_height-1)){
		return false;
	}else{
		if(coord.x == player->coord.x && coord.y == player->coord.y)
			return false;

		for(int i = 0; i < mapdetails->alive_monster_count; i++){
			if(monster_arr[i].alive && coord.x == monster_arr[i].coord.x && coord.y == monster_arr[i].coord.y)
				return false;
		}
	}

	return true;
}


void sort_and_update_map(){
	qsort(monster_arr, initial_monster_num, sizeof(Monster), cmpfunc);

	mapdetails->player = player->coord;
	mapdetails->alive_monster_count = alive_monster_num;

	for(int i = 0; i < alive_monster_num; i++){
		mapdetails->monster_types[i] = monster_arr[i].symbol;
		mapdetails->monster_coordinates[i] = monster_arr[i].coord;
	}
}