#include "message.h"

// os libs
#include <unistd.h>

// abs
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))


int health, given_damage, defence, attack_range;



void monster_terminate(void){
	close(0);
	close(1);
	close(2);
	exit(0);
}


coordinate generate_position(int i, coordinate m_coord){
	coordinate new_coord;

	switch(i){
		case 0:
			new_coord.x = m_coord.x;
			new_coord.y = m_coord.y - 1;
			break;
		case 1:
			new_coord.x = m_coord.x + 1;
			new_coord.y = m_coord.y - 1;
			break;
		case 2:
			new_coord.x = m_coord.x + 1;
			new_coord.y = m_coord.y;
			break;
		case 3:
			new_coord.x = m_coord.x + 1;
			new_coord.y = m_coord.y + 1;
			break;
		case 4:
			new_coord.x = m_coord.x;
			new_coord.y = m_coord.y + 1;
			break;
		case 5:
			new_coord.x = m_coord.x - 1;
			new_coord.y = m_coord.y + 1;
			break;
		case 6:
			new_coord.x = m_coord.x - 1;
			new_coord.y = m_coord.y;
			break;
		case 7:
			new_coord.x = m_coord.x - 1;
			new_coord.y = m_coord.y - 1;
			break;
	}

	return new_coord;
}

coordinate find_new_position(coordinate m_coord, coordinate p_coord){
	coordinate best_pos = generate_position(0, m_coord);
	int best_dist = abs(best_pos.x - p_coord.x) + abs(best_pos.y - p_coord.y);

	for(int i = 1; i < 8; i++){
		coordinate calc_pos = generate_position(i, m_coord);
		int calc_dist = abs(calc_pos.x - p_coord.x) + abs(calc_pos.y - p_coord.y);

		if(best_dist > calc_dist){
			best_dist = calc_dist;
			best_pos = calc_pos;
		}
	}

	return best_pos;
}

void make_response(monster_message w_message){
	health = health - MAX(0, (w_message.damage - defence));

	coordinate m_coord = w_message.new_position;
	coordinate p_coord = w_message.player_coordinate;
	int distance_between = abs(m_coord.x - p_coord.x) + abs(m_coord.y - p_coord.y);


	if(health <= 0){
		monster_response m_response;
		m_response.mr_type = 3;
		write(1, &m_response, sizeof(monster_response));
		monster_terminate();
	}else if(distance_between <= attack_range){
		monster_response m_response;
		m_response.mr_type = 2;
		m_response.mr_content.attack = given_damage;
		write(1, &m_response, sizeof(monster_response));
	}else{
		coordinate calculated_pos = find_new_position(m_coord, p_coord);
		monster_response m_response;
		m_response.mr_type = 1;
		m_response.mr_content.move_to = calculated_pos;
		write(1, &m_response, sizeof(monster_response));
	}

}


int main(int argc, char* argv[]) {

	health = atoi(argv[1]);
	given_damage = atoi(argv[2]);
	defence = atoi(argv[3]);
	attack_range = atoi(argv[4]);

	// init ready response
	monster_response m_response;
	m_response.mr_type = 0;
	write(1, &m_response, sizeof(monster_response));

	while(1){
		monster_message w_message;
		read(0, &w_message, sizeof(monster_message));

		if(w_message.game_over){
			monster_terminate();
		}else{
			make_response(w_message);
		}
	}


	return 0;
}