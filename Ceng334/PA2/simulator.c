#include <stdio.h>
#include <stdlib.h>

// os libs
#include <pthread.h>
#include <semaphore.h>

// hw libs
#include "helper.h"
#include "writeOutput.h"

// semaphore
#define SM_INIT(sem, value) (sem_init(&(sem), 0, value))
#define SM_WAIT(sem) (sem_wait(&(sem)))
#define SM_SIGNAL(sem) (sem_post(&(sem)))


typedef struct{
	int sender_id;
	int sender_hub_id;
	int receiver_id;
	int receiver_hub_id;
}Package;

typedef struct{
	int hub_id;
	int distance;
}Distance_info;

typedef struct{
	pthread_t tid;
	int id;
	int size_incoming;
	int size_outgoing;
	int size_charging;
	int* distance_arr;
	Distance_info* sorted_distance_arr;
	int sender_id;
	int receiver_id;
	sem_t incoming_empty;
	sem_t incoming_mutex;
	sem_t outgoing_empty;
	sem_t outgoing_full;
	sem_t outgoing_mutex;
	sem_t charging_empty;
	sem_t general_drone_mutex;
	int current_outgoing_number;
	int current_incoming_number;
	int current_drone_number;
	Package* outgoing_arr;
	Package* incoming_arr;
	int* drone_id_arr;
	int is_active;
	int is_drone_called;
}Hub;

typedef struct{
	pthread_t tid;
	int id;
	int wait_time;
	int hub_id;
	int num_package;
	int num_remaining_package;
}Sender;

typedef struct{
	pthread_t tid;
	int id;
	int wait_time;
	int hub_id;
}Receiver;

typedef struct{
	pthread_t tid;
	int id;
	int travel_speed;
	int start_hub_id;
	int current_hub_id;
	int destination_hub_id;
	int is_called;
	int is_available;
	int max_range;
	int current_range;
	long long last_charge_start;
	Package current_package;
	sem_t drone_notify;
}Drone;



void *hub_routine(void* ptr);
void *sender_routine(void* ptr);
void *receiver_routine(void* ptr);
void *drone_routine(void* ptr);
int AssignAndNotifyDrone(Package pack, Hub* hub);
void CallDroneFromHubsHelper(int destination_hub_id, Drone* drone);
int CallDroneFromHubs(Hub* hub);
void TakePackageFromHub(int cur_hub_id);
void DropPackageToHub(Package pack, int target_hub_id);
void LeaveHub(int cur_hub_id);
void ArriveHub(int drone_id, int target_hub_id, int range_decrease, int called_flag);
void WaitAndReserveDestinationSpace(int target_hub_id);
void WaitAndReserveChargingSpace(int destination_hub_id);
void UpdateRanges(Hub* hub);


int hub_number, drone_number;

sem_t active_sender_mutex, active_hub_mutex;
int active_sender_number, active_hub_number;

Hub* hub_array;
Sender* sender_array;
Receiver* receiver_array;
Drone* drone_array;


int cmpfunc(const void * a, const void * b){
	return ((*(Distance_info*)a).distance - (*(Distance_info*)b).distance);
}

int main(void) {
	scanf("%d", &hub_number);

	active_sender_number = hub_number;
	active_hub_number = hub_number;

	SM_INIT(active_sender_mutex, 1);
	SM_INIT(active_hub_mutex, 1);


	hub_array = (Hub*) calloc(hub_number, sizeof(Hub));
	int size_in, size_out, size_charge;
	for(int i = 0; i < hub_number; i++){
		hub_array[i].id = i+1;
		scanf("%d %d %d", &size_in, &size_out, &size_charge);
		hub_array[i].size_incoming = size_in;
		hub_array[i].size_outgoing = size_out;
		hub_array[i].size_charging = size_charge;
		hub_array[i].distance_arr = (int*) calloc(hub_number, sizeof(int));
		hub_array[i].sorted_distance_arr = (Distance_info*) calloc(hub_number, sizeof(Distance_info));
		for(int j = 0; j < hub_number; j++){
			scanf("%d", &(hub_array[i].distance_arr[j]));
			hub_array[i].sorted_distance_arr[j].hub_id = j+1;
			hub_array[i].sorted_distance_arr[j].distance = hub_array[i].distance_arr[j];
		}

		qsort(hub_array[i].sorted_distance_arr, hub_number, sizeof(Distance_info), cmpfunc);

		hub_array[i].current_incoming_number = 0;
		hub_array[i].current_outgoing_number = 0;
		hub_array[i].current_drone_number = 0;
		hub_array[i].incoming_arr = (Package*) calloc(size_in, sizeof(Package));
		hub_array[i].outgoing_arr = (Package*) calloc(size_out, sizeof(Package));
		hub_array[i].drone_id_arr = (int*) calloc(size_charge, sizeof(int));
		hub_array[i].is_active = 1;
		hub_array[i].is_drone_called = 0;

		SM_INIT(hub_array[i].incoming_empty, size_in);
		SM_INIT(hub_array[i].incoming_mutex, 1);
		SM_INIT(hub_array[i].outgoing_empty, size_out);
		SM_INIT(hub_array[i].outgoing_full, 0);
		SM_INIT(hub_array[i].outgoing_mutex, 1);
		SM_INIT(hub_array[i].general_drone_mutex, 1);
	}

	sender_array = (Sender*) calloc(hub_number, sizeof(Sender));
	int sender_wait_time, sender_hub_id, num_package;
	for(int i = 0; i < hub_number; i++){
		sender_array[i].id = i+1;
		scanf("%d %d %d", &sender_wait_time, &sender_hub_id, &num_package);
		sender_array[i].wait_time = sender_wait_time;
		sender_array[i].hub_id = sender_hub_id;
		sender_array[i].num_package = num_package;
		sender_array[i].num_remaining_package = num_package;
		hub_array[sender_hub_id - 1].sender_id = i+1;
	}

	receiver_array = (Receiver*) calloc(hub_number, sizeof(Receiver));
	int receiver_wait_time, receiver_hub_id;
	for(int i = 0; i < hub_number; i++){
		receiver_array[i].id = i+1;
		scanf("%d %d", &receiver_wait_time, &receiver_hub_id);
		receiver_array[i].wait_time = receiver_wait_time;
		receiver_array[i].hub_id = receiver_hub_id;
		hub_array[receiver_hub_id - 1].receiver_id = i+1;
	}


	scanf("%d", &drone_number);

	drone_array = (Drone*) calloc(drone_number, sizeof(Drone));
	int travel_speed, start_hub_id, max_range;
	for(int i = 0; i < drone_number; i++){
		drone_array[i].id = i+1;
		scanf("%d %d %d", &travel_speed, &start_hub_id, &max_range);
		drone_array[i].travel_speed = travel_speed;
		drone_array[i].start_hub_id = start_hub_id;
		drone_array[i].current_hub_id = start_hub_id;
		drone_array[i].destination_hub_id = -1;
		drone_array[i].is_called = 0;
		drone_array[i].is_available = 1;
		drone_array[i].max_range = max_range;
		drone_array[i].current_range = max_range;
		drone_array[i].last_charge_start = timeInMilliseconds();
		hub_array[start_hub_id - 1].drone_id_arr[hub_array[start_hub_id - 1].current_drone_number] = i+1;
		hub_array[start_hub_id - 1].current_drone_number += 1;

		SM_INIT(drone_array[i].drone_notify, 0);
	}


	for (int i = 0; i < hub_number; i++)
	{
		SM_INIT(hub_array[i].charging_empty, hub_array[i].size_charging - hub_array[i].current_drone_number);
	}


	// Create threads
	InitWriteOutput();
	for(int i = 0; i < hub_number; i++){
		pthread_create(&(hub_array[i].tid), NULL, hub_routine, (void *)&hub_array[i]);
		pthread_create(&(sender_array[i].tid), NULL, sender_routine, (void *)&sender_array[i]);
		pthread_create(&(receiver_array[i].tid), NULL, receiver_routine, (void *)&receiver_array[i]);
	}

	for(int i = 0; i < drone_number; i++){
		pthread_create(&(drone_array[i].tid), NULL, drone_routine, (void *)&drone_array[i]);
	}



	// End of the program
	for(int i = 0; i < hub_number; i++){
		pthread_join(hub_array[i].tid, NULL);
		pthread_join(sender_array[i].tid, NULL);
		pthread_join(receiver_array[i].tid, NULL);
	}

	for(int i = 0; i < drone_number; i++){
		pthread_join(drone_array[i].tid, NULL);
	}



	for(int i = 0; i < hub_number; i++){
		free(hub_array[i].distance_arr);
		free(hub_array[i].incoming_arr);
		free(hub_array[i].outgoing_arr);
		free(hub_array[i].drone_id_arr);
		free(hub_array[i].sorted_distance_arr);
	}

	free(hub_array);
	free(sender_array);
	free(receiver_array);
	free(drone_array);

	return 0;
}



void *sender_routine(void* ptr){
	Sender* sender = (Sender*) ptr;
	SenderInfo sender_info;
	Hub* sender_hub = &(hub_array[sender->hub_id - 1]);
	FillSenderInfo(&sender_info, sender->id, sender->hub_id, sender->num_package, NULL);
	WriteOutput(&sender_info, NULL, NULL, NULL, SENDER_CREATED);

	while(sender->num_remaining_package != 0){
	
		int random_hub_id = (rand() % hub_number) + 1;
		while(random_hub_id == sender->hub_id){
			random_hub_id = (rand() % hub_number) + 1;
		}

		int target_receiver_id = hub_array[random_hub_id - 1].receiver_id;
		Package delivery_pack;
		delivery_pack.sender_id = sender->id;
		delivery_pack.sender_hub_id = sender->hub_id;
		delivery_pack.receiver_id = target_receiver_id;
		delivery_pack.receiver_hub_id = random_hub_id;

		SM_WAIT(sender_hub->outgoing_empty);
		SM_WAIT(sender_hub->outgoing_mutex);
		sender_hub->outgoing_arr[sender_hub->current_outgoing_number] = delivery_pack;
		sender_hub->current_outgoing_number += 1;
		SM_SIGNAL(sender_hub->outgoing_mutex);
		SM_SIGNAL(sender_hub->outgoing_full);

		PackageInfo pack_info;
		FillPacketInfo(&pack_info, sender->id, sender->hub_id, target_receiver_id, random_hub_id);
		FillSenderInfo(&sender_info, sender->id, sender->hub_id, sender->num_remaining_package, &pack_info);
		WriteOutput(&sender_info, NULL, NULL, NULL, SENDER_DEPOSITED);
		sender->num_remaining_package -= 1;
		wait(UNIT_TIME * (sender->wait_time));
	}

	SM_WAIT(active_sender_mutex);
	active_sender_number--;
	if(active_sender_number == 0){
		for(int i = 0; i < hub_number; i++){
			SM_SIGNAL(hub_array[i].outgoing_full);
		}
	}
	SM_SIGNAL(active_sender_mutex);
	FillSenderInfo(&sender_info, sender->id, sender->hub_id, sender->num_remaining_package, NULL);
	WriteOutput(&sender_info, NULL, NULL, NULL, SENDER_STOPPED);

	return NULL;
}

void *receiver_routine(void* ptr){
	Receiver* receiver = (Receiver*) ptr;
	ReceiverInfo receiver_info;
	Package received_pack;
	Hub* receiver_hub = &(hub_array[receiver->hub_id - 1]);
	FillReceiverInfo(&receiver_info, receiver->id, receiver->hub_id, NULL);
	WriteOutput(NULL, &receiver_info, NULL, NULL, RECEIVER_CREATED);

	while(receiver_hub->is_active){

		while(receiver_hub->current_incoming_number){
			SM_WAIT(receiver_hub->incoming_mutex);
			received_pack = receiver_hub->incoming_arr[receiver_hub->current_incoming_number - 1];
			receiver_hub->current_incoming_number -= 1;
			SM_SIGNAL(receiver_hub->incoming_mutex);
			SM_SIGNAL(receiver_hub->incoming_empty);

			PackageInfo pack_info;
			FillPacketInfo(&pack_info, received_pack.sender_id, received_pack.sender_hub_id, received_pack.receiver_id, received_pack.receiver_hub_id);
			FillReceiverInfo(&receiver_info, receiver->id, receiver->hub_id, &pack_info);
			WriteOutput(NULL, &receiver_info, NULL, NULL, RECEIVER_PICKUP);
			wait(UNIT_TIME * (receiver->wait_time));
		}
	}

	FillReceiverInfo(&receiver_info, receiver->id, receiver->hub_id, NULL);
	WriteOutput(NULL, &receiver_info, NULL, NULL, RECEIVER_STOPPED);

	return NULL;

}


int drone_exit_check(){


	SM_WAIT(active_hub_mutex);
	if(!active_hub_number){
		SM_SIGNAL(active_hub_mutex);
		return 0;
	}
	SM_SIGNAL(active_hub_mutex);
	return 1;
}


void *drone_routine(void* ptr){
	Drone* drone = (Drone*) ptr;
	DroneInfo drone_info;
	PackageInfo pack_info;
	FillDroneInfo(&drone_info, drone->id, drone->start_hub_id, drone->max_range, NULL, 0);
	WriteOutput(NULL, NULL, &drone_info, NULL, DRONE_CREATED);


	while(drone_exit_check()){

		SM_WAIT(drone->drone_notify);

		if(!(drone_exit_check()))
			break;

		if(drone->is_called == 0){
			Package pack = drone->current_package;
			int cur_hub_id = pack.sender_hub_id;
			int target_hub_id = pack.receiver_hub_id;
			int travel_distance = hub_array[cur_hub_id - 1].distance_arr[target_hub_id - 1];

			WaitAndReserveDestinationSpace(target_hub_id);

			long long charged_time = timeInMilliseconds() - drone->last_charge_start;
			drone->current_range = calculate_drone_charge(charged_time, drone->current_range, drone->max_range);
			int required_range = travel_distance / (drone->travel_speed);

			while(drone->current_range < required_range){
				charged_time = timeInMilliseconds() - drone->last_charge_start;
				drone->current_range = calculate_drone_charge(charged_time, drone->current_range, drone->max_range);
			}


			LeaveHub(cur_hub_id);

			TakePackageFromHub(cur_hub_id);
			FillPacketInfo(&pack_info, pack.sender_id, pack.sender_hub_id, pack.receiver_id, pack.receiver_hub_id);
			FillDroneInfo(&drone_info, drone->id, drone->current_hub_id, drone->current_range, &pack_info, 0);
			WriteOutput(NULL, NULL, &drone_info, NULL, DRONE_PICKUP);

			travel(travel_distance, drone->travel_speed);

			ArriveHub(drone->id, target_hub_id, range_decrease(travel_distance, drone->travel_speed), 0);

			DropPackageToHub(pack, target_hub_id);
			FillPacketInfo(&pack_info, pack.sender_id, pack.sender_hub_id, pack.receiver_id, pack.receiver_hub_id);
			FillDroneInfo(&drone_info, drone->id, drone->current_hub_id, drone->current_range, &pack_info, 0);
			WriteOutput(NULL, NULL, &drone_info, NULL, DRONE_DEPOSITED);


		}else{
			int cur_hub_id = drone->current_hub_id;
			int destination_hub_id = drone->destination_hub_id;
			int travel_distance = hub_array[cur_hub_id - 1].distance_arr[destination_hub_id - 1];

			WaitAndReserveChargingSpace(destination_hub_id);


			long long charged_time = timeInMilliseconds() - drone->last_charge_start;
			drone->current_range = calculate_drone_charge(charged_time, drone->current_range, drone->max_range);
			int required_range = travel_distance / (drone->travel_speed);

			while(drone->current_range < required_range){
				charged_time = timeInMilliseconds() - drone->last_charge_start;
				drone->current_range = calculate_drone_charge(charged_time, drone->current_range, drone->max_range);
			}

			LeaveHub(cur_hub_id);

			FillDroneInfo(&drone_info, drone->id, drone->current_hub_id, drone->current_range, NULL, destination_hub_id);
			WriteOutput(NULL, NULL, &drone_info, NULL, DRONE_GOING);

			travel(travel_distance, drone->travel_speed);

			ArriveHub(drone->id, destination_hub_id, range_decrease(travel_distance, drone->travel_speed), 1);

			FillDroneInfo(&drone_info, drone->id, drone->current_hub_id, drone->current_range, NULL, 0);
			WriteOutput(NULL, NULL, &drone_info, NULL, DRONE_ARRIVED);
		}

	}


	FillDroneInfo(&drone_info, drone->id, drone->current_hub_id, drone->current_range, NULL, 0);
	WriteOutput(NULL, NULL, &drone_info, NULL, DRONE_STOPPED);

	return NULL;
}


int hub_exit_check(Hub* hub){

	SM_WAIT(hub->outgoing_mutex);
	SM_WAIT(hub->incoming_mutex);
	SM_WAIT(active_sender_mutex);
	if(!(active_sender_number || hub->current_outgoing_number || hub->current_incoming_number)){
		SM_SIGNAL(active_sender_mutex);
		SM_SIGNAL(hub->incoming_mutex);
		SM_SIGNAL(hub->outgoing_mutex);
		return 0;
	}
	SM_SIGNAL(active_sender_mutex);
	SM_SIGNAL(hub->incoming_mutex);
	SM_SIGNAL(hub->outgoing_mutex);

	return 1;
}

void *hub_routine(void* ptr){
	Hub* hub = (Hub*) ptr;
	HubInfo hub_info;
	FillHubInfo(&hub_info, hub->id);
	WriteOutput(NULL, NULL, NULL, &hub_info, HUB_CREATED);

	Package pack;
	int is_assigned;
	while(hub_exit_check(hub)){

		SM_WAIT(hub->outgoing_full);


		start:

		if(!hub_exit_check(hub))
			break;

		UpdateRanges(hub);

		SM_WAIT(hub->outgoing_mutex);
			pack = hub->outgoing_arr[hub->current_outgoing_number - 1];
		SM_SIGNAL(hub->outgoing_mutex);

		SM_WAIT(hub->general_drone_mutex);
			is_assigned = AssignAndNotifyDrone(pack, hub);
		SM_SIGNAL(hub->general_drone_mutex);


		if(!is_assigned){
			if(!hub->is_drone_called){
				int is_found = CallDroneFromHubs(hub);
				if(!is_found){
					wait(UNIT_TIME);
				}else{
					hub->is_drone_called = 1;
				}
			}
			goto start;
		}


	}

	// HubStopped
	SM_WAIT(active_hub_mutex);
	hub->is_active = 0;
	active_hub_number--;
	if(active_hub_number == 0){
		for(int i = 0; i < drone_number; i++)
			SM_SIGNAL(drone_array[i].drone_notify);
	}
	SM_SIGNAL(active_hub_mutex);
	FillHubInfo(&hub_info, hub->id);
	WriteOutput(NULL, NULL, NULL, &hub_info, HUB_STOPPED);

	return NULL;
}


int AssignAndNotifyDrone(Package pack, Hub* hub){

	Drone* drone_var = NULL;
	int range_var = -1;

	Drone* drone_tmp;
	int range_tmp; 

	for(int i = 0; i < hub->current_drone_number; i++){
		drone_tmp = &drone_array[hub->drone_id_arr[i] - 1];

		if(!(drone_tmp->is_available))
			continue;

		range_tmp = drone_tmp->current_range;

		if(range_tmp > range_var){
			drone_var = drone_tmp;
			range_var = range_tmp;
		}
	}

	if(drone_var != NULL){
		drone_var->current_package = pack;
		drone_var->is_called = 0;
		drone_var->is_available = 0;
		SM_SIGNAL(drone_var->drone_notify);
		return 1;
	}

	return 0;
}




void CallDroneFromHubsHelper(int destination_hub_id, Drone* drone){
	drone->destination_hub_id = destination_hub_id;
	drone->is_called = 1;
	drone->is_available = 0;
	SM_SIGNAL(drone->drone_notify);
}

int CallDroneFromHubs(Hub* hub){
	int tmp_hub_id, tmp_drone_id;
	Hub* tmp_hub;
	Drone* tmp_drone;

	for(int i = 1; i < hub_number; i++){
		tmp_hub_id = hub->sorted_distance_arr[i].hub_id;
		tmp_hub = &hub_array[tmp_hub_id - 1];

		SM_WAIT(tmp_hub->general_drone_mutex);

		for(int j = 0; j < tmp_hub->current_drone_number; j++){
			tmp_drone_id = tmp_hub->drone_id_arr[j];
			tmp_drone = &drone_array[tmp_drone_id - 1];

			if(tmp_drone->is_available){
				CallDroneFromHubsHelper(hub->id, tmp_drone);
				SM_SIGNAL(tmp_hub->general_drone_mutex);
				return 1;
			}
		}

		SM_SIGNAL(tmp_hub->general_drone_mutex);
	}

	return 0;
}



void TakePackageFromHub(int cur_hub_id){
	Hub* hub = &(hub_array[cur_hub_id - 1]);
	SM_WAIT(hub->outgoing_mutex);
		hub->current_outgoing_number--;
	SM_SIGNAL(hub->outgoing_mutex);
	SM_SIGNAL(hub->outgoing_empty);
}

void DropPackageToHub(Package pack, int target_hub_id){
	Hub* hub = &(hub_array[target_hub_id - 1]);
	SM_WAIT(hub->incoming_mutex);
		hub->incoming_arr[hub->current_incoming_number] = pack;
		hub->current_incoming_number++;
	SM_SIGNAL(hub->incoming_mutex);
}

void LeaveHub(int cur_hub_id){
	Hub* hub = &(hub_array[cur_hub_id - 1]);
	SM_WAIT(hub->general_drone_mutex);
		hub->current_drone_number--;
	SM_SIGNAL(hub->general_drone_mutex);
	SM_SIGNAL(hub->charging_empty);
}

void ArriveHub(int drone_id, int target_hub_id, int range_decrease, int called_flag){
	Hub* hub = &(hub_array[target_hub_id - 1]);
	Drone* drone = &(drone_array[drone_id - 1]);
	SM_WAIT(hub->general_drone_mutex);
		hub->drone_id_arr[hub->current_drone_number] = drone_id;
		hub->current_drone_number++;

		if(called_flag){
			hub->is_drone_called = 0;
		}

		drone->current_hub_id = target_hub_id;
		drone->current_range -= range_decrease;
		drone->last_charge_start = timeInMilliseconds();
		drone->is_available = 1;
	SM_SIGNAL(hub->general_drone_mutex);
}

void WaitAndReserveDestinationSpace(int target_hub_id){
	Hub* hub = &(hub_array[target_hub_id - 1]);
	SM_WAIT(hub->incoming_empty);
	SM_WAIT(hub->charging_empty);
}

void WaitAndReserveChargingSpace(int destination_hub_id){
	Hub* hub = &(hub_array[destination_hub_id - 1]);
	SM_WAIT(hub->charging_empty);
}


void UpdateRanges(Hub* hub){
	long long charged_time;
	Drone* drone;
	SM_WAIT(hub->general_drone_mutex);
	for(int i = 0; i < hub->current_drone_number; i++){
		drone = &drone_array[hub->drone_id_arr[i] - 1];
		charged_time = timeInMilliseconds() - drone->last_charge_start;
		drone->current_range = calculate_drone_charge(charged_time, drone->current_range, drone->max_range);
	}
	SM_SIGNAL(hub->general_drone_mutex);
}	