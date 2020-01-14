#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "the2.h"

/*
 *  returns the order of the letter in the alphabet
 *  if given char is not an ascii letter, returns 0
 */
int letter_order(char c) {
    if (c < 91 && c > 64) {
        return c - 64;
    } else if (c < 123 && c > 96) {
        return c - 96;
    }
    return 0;
}
/*
 * Prints the connections of given user.
 */
void print_connections(User *user) {
    Connection *connection;
    int i;
    for (i = 0; i < BUCKET_SIZE; i++) {
        printf("Bucket %d: ", i);
        if (user->connections[i] != NULL) {
            connection = user->connections[i];
            do {
                printf("[user1: %s, user2: %s, connection_time: %ld] -> ", connection->user1->name,
                       connection->user2->name, connection->connection_time);

            } while ((connection = connection->next_connection) != NULL);
        }
        printf("NULL\n");


    }
}

/*
 * Returns the hash code of the user.
 */
unsigned long hash_code(User *user) {
    unsigned long hash = 0;
    int i = 0;

    while ((*user).name[i] != 0) {
        hash += letter_order((*user).name[i]) * pow(HASH_KEY, i);
        i++;
    }

    return hash;
}

/*
 * Returns the User with given id from environment.
 */
User *get_user(Environment environment, int id) {
    /* TODO: Implement this function. */

    int i = 0;
    while(environment.users[i] != NULL){

     if(environment.users[i]->id == id)
             return environment.users[i];

     i++;

    }




    return NULL;
}

/* Connector maker */
Connection *conmaker(struct connection *prev_connection,struct connection *next_connection,struct user *user1,struct user *user2,long connection_time){

Connection *con = (struct connection *)malloc(sizeof(struct connection));

con->prev_connection = prev_connection;
con->next_connection = next_connection;
con->user1 = user1;
con->user2 = user2;
con->connection_time = connection_time;


return con;

}



/*
 * Connects two user and registers the related connection objects to both users' connection hash tables.
 */
void connect_users(Environment environment, int id1, int id2, long connection_time) {
    /* TODO: Implement this function. */

    User *user1 = get_user(environment,id1);
    User *user2 = get_user(environment,id2);


    int index1;
    int index2;

    struct connection **con_p1 ;
    struct connection **con_p2 ;

    struct connection* curr = NULL ;

    struct connection* tmp = NULL;
    struct connection* tmp2 = NULL;
    struct connection* exchecker;
    struct connection* exchecker2;

    if(id1 == id2)
        return ;

    /*test if users exist */
    if(user1 == NULL || user2 == NULL)
        return ;

    /* we guarantee users exist */
    index1 = hash_code(user2)%BUCKET_SIZE;
    index2 = hash_code(user1)%BUCKET_SIZE;
    con_p1 = (user1->connections);
    con_p2 = (user2->connections);
    exchecker = con_p1[index1];
    exchecker2 = con_p2[index2];

    /* test if connection exists */
      while(exchecker != NULL){
         if(exchecker->user2 ==user2)
             return;
         exchecker = exchecker->next_connection;
      }

      while(exchecker2 != NULL){
         if(exchecker2->user2 ==user1)
             return;
         exchecker2 = exchecker2->next_connection;
      }

    /* for user1's hashset */

    if(con_p1[index1] == NULL){

     con_p1[index1] = conmaker(NULL,NULL,user1,user2,connection_time);

    }else if(connection_time < (con_p1[index1]->connection_time)){

        curr = conmaker(NULL,con_p1[index1],user1,user2,connection_time);

        tmp = con_p1[index1];
        con_p1[index1] = curr;
        tmp->prev_connection = curr;


     }else{

      curr = con_p1[index1];

      while(curr->next_connection != NULL && (curr->next_connection->connection_time < connection_time))
       curr = curr->next_connection;

      tmp2 = conmaker(curr,curr->next_connection,user1,user2,connection_time);

      if (curr->next_connection != NULL)
            tmp2->next_connection->prev_connection = tmp2;

      curr->next_connection = tmp2;


    }


    /* for user2's hashset */
    curr = NULL;
    tmp = NULL;
    tmp2 = NULL;

    if(con_p2[index2] == NULL){

     con_p2[index2] = conmaker(NULL,NULL,user2,user1,connection_time);

    }else if(connection_time < (con_p2[index2]->connection_time)){

        curr = conmaker(NULL,con_p2[index2],user2,user1,connection_time);

        tmp = con_p2[index2];
        con_p2[index2] = curr;
        tmp->prev_connection = curr;


     }else{

      curr = con_p2[index2];

      while(curr->next_connection != NULL && (curr->next_connection->connection_time < connection_time))
       curr = curr->next_connection;

      tmp2 = conmaker(curr,curr->next_connection,user2,user1,connection_time);

      if (curr->next_connection != NULL)
            tmp2->next_connection->prev_connection = tmp2;

      curr->next_connection = tmp2;


    }


}

/*
 * Rstrip the given string.
 */

char *rstrip(char *string) {
  char *end;

  while(isspace((unsigned char)*string)){
    string++;
  }

  if(*string == 0) {
    return string;
  }

  end = string + strlen(string) - 1;
  while(end > string && isspace((unsigned char)*end)){
    end--;
  }

  end[1] = '\0';

  return string;
}


/*
 * Creates a new environment with the information in the given file that contains users
 * with connections and returns it.
 */
Environment *init_environment(char *user_file_name) {
    Environment *environment;
    User *user;
    FILE *fp;
    char *line = NULL;
    char *iter;
    char *sep = " ";
    size_t len = 0;
    size_t read;
    int id, id1, id2;
    long timestamp;
    char *name;
    User* user1, *user2;

    int u_count = 0;

    environment = malloc(sizeof(Environment));
    environment->users = malloc(sizeof(User*));
    environment->users[0] = NULL;

    fp = fopen(user_file_name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        line = rstrip(line);
        if (strcmp(line, "#Users#") == 0) {
            continue;
        } else if (strcmp(line, "#Connections#") == 0) {
            break;
        }
        user = malloc(sizeof(User));
        iter = strtok(line, sep);
        id = atoi(iter);
        iter = strtok(NULL, sep);
        name = malloc(sizeof(char)*strlen(iter));
        strcpy(name, iter);
        user->id=id;
        user->name=name;
        environment->users = realloc(environment->users, sizeof(User*)*(u_count+2));
        environment->users[u_count] = user;
        environment->users[u_count+1] = NULL;
        u_count++;
    }

    /* Uncomment after connect_users function implemented. */
    while ((read = getline(&line, &len, fp)) != -1) {
        line = rstrip(line);
        iter = strtok(line, sep);
        id1 = atoi(iter);
        iter = strtok(NULL, sep);
        id2 = atoi(iter);
        iter = strtok(NULL, sep);
        timestamp = atol(iter);
        connect_users(*environment, id1, id2, timestamp);

    }

    return environment;

}

/*
 * Returns the connection between users with id1 and id2. The connection
 * is the one stored in user1's hash table. If there is no such a connection returns
 * NULL.
 */


Connection *get_connection(Environment environment, int id1, int id2) {
    /* TODO: Implement this function.*/
   User* use1 = get_user(environment,id1);
   User* use2 = get_user(environment,id2);
   unsigned long hash;
   Connection *curr;

   if(id1 == id2)
      return NULL;

   /*test user exist */
    if(use1 == NULL || use2 == NULL)
       return NULL;


    else{

    hash = hash_code(use2);
    curr = (use1->connections)[hash%BUCKET_SIZE];

    while(curr != NULL){
      if(curr->user2 == use2)
         return curr;


    curr = curr->next_connection;
    }
    }


    return NULL;
}


/*
 * Remove connection from the given user. Additionally, finds the other user and removes related connection
 * from her/his table also.
 */


void remove_connection(Environment environment, int id1, int id2) {
    /* TODO: Implement this function. */

    Connection *con1 = get_connection(environment,id1,id2);
    Connection *con2 = get_connection(environment,id2,id1);

    User *user1 = get_user(environment,id1);
    User *user2 = get_user(environment,id2);

    unsigned long hash1;
    unsigned long hash2;

    if(id1 == id2)
       return ;

      if(user1== NULL || user2==NULL)
         return;
     /* do nothing */
     else if(!(con1&&con2))
        return;
     else{

    hash1 = hash_code(user1);
    hash2 = hash_code(user2);

    /* user1 */
    if(con1->prev_connection == NULL && con1->next_connection == NULL){
       (user1->connections)[hash2%BUCKET_SIZE] = NULL;
       free(con1);
    }else if(con1->prev_connection == NULL && con1->next_connection != NULL){
       (user1->connections)[hash2%BUCKET_SIZE] = con1->next_connection;
       con1->next_connection->prev_connection = NULL;
       free(con1);
    }else if(con1->prev_connection != NULL && con1->next_connection == NULL){
       con1->prev_connection->next_connection = NULL;
       free(con1);
    }else{
       con1->prev_connection->next_connection = con1->next_connection;
       con1->next_connection->prev_connection = con1->prev_connection;
       free(con1);
    }

    /* user2 */
    if(con2->prev_connection == NULL && con2->next_connection == NULL){
       (user2->connections)[hash1%BUCKET_SIZE] = NULL;
       free(con2);
    }else if(con2->prev_connection == NULL && con2->next_connection != NULL){
       (user2->connections)[hash1%BUCKET_SIZE] = con2->next_connection;
       con2->next_connection->prev_connection = NULL;
       free(con2);
    }else if(con2->prev_connection != NULL && con2->next_connection == NULL){
       con2->prev_connection->next_connection = NULL;
       free(con2);
    }else{
       con2->prev_connection->next_connection = con2->next_connection;
       con2->next_connection->prev_connection = con2->prev_connection;
       free(con2);
    }
}
}

/*
 * Returns dynamic User array which contains common connections. The last element
 * of the array is NULL, which is mandatory for detecting the end.
 */
User **get_common_connections(Environment environment, User *user1, User *user2) {
    /* TODO: Implement this function. */
    int i = 0;
    int k = 0;
    Connection *curr;
    Connection *lurr;
    User **p = (User **)malloc(sizeof(User *));

    if(user1 != NULL && user2 != NULL){

    while(i<BUCKET_SIZE){
    curr = user1->connections[i];
       while(curr != NULL){
          lurr = user2->connections[i];
              while(lurr != NULL){
                if(lurr->user2->id == curr->user2->id){
                    p[k] = lurr->user2;
                    k++;
                    p = realloc(p,sizeof(User*)*(k+1));


                    break;
                }
                 lurr= lurr->next_connection;
                 }
             curr = curr->next_connection;
    }
    i++;
    }
    }

    p[k] = NULL;


    return p;
}

