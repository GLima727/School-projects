/*----------------------------------------------------------------------------------------
Guilherme Gonçalves Gutierrez de Lima ist199077
This programm will use the Kanban method to aid in the development of complex projects,
by dividing it into simpler tasks, with user and activity management. 
----------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Constant defines */
#define MAX_TASKS 10000
#define MAX_USERS 49                                      
#define MAX_DESCRIPTION 51                                      
#define MAX_USERS_NAME 21                                       
#define MAX_ACTIVITYS 10
#define MAX_ACTIVITY_NAME 21                                    
#define EXIT_CODE 0
/* Macro defines */
#define key(A) (A)
#define less(A, B)     (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B)  if (less(B, A)) exch(A, B)
typedef int Item;
/* Error defines */
#define TOO_MANY_TASKS "too many tasks\n"
#define TOO_MANY_USERS "too many users\n"
#define TOO_MANY_ACTIVITIES "too many activities\n"
#define DUPLICATE_DESCRIPTION "duplicate description\n"
#define DUPLICATE_ACTIVITY "duplicate activity\n"
#define INVALID_DURATION "invalid duration\n"
#define INVALID_DESCRIPTION "invalid description\n"
#define INVALID_TIME "invalid time\n"
#define NO_SUCH_USER "no such user\n"
#define NO_SUCH_ACTIVITY "no such activity\n"
#define NO_SUCH_TASK "no such task\n"
#define USER_ALREADY_EXISTS "user already exists\n"
#define TASK_ALREADY_STARTED "task already started\n"

/* STRUCTURE */
typedef struct {

    char description[MAX_DESCRIPTION];                          
    char task_users[MAX_USERS][MAX_USERS_NAME];        /* Users of the task. */         
    char activity[MAX_ACTIVITY_NAME];               /* Activity of the task. */
    int anticipated_duration;           /* Anticipated duration of the task. */
    int initial_instance;              /* Instance when the task is created. */
    int task_num_users;             /* How many users there are in the task. */
} Task; 

/* GLOBAL VARIABLES */
/* Variable that holds the information of all tasks. */
Task task[MAX_TASKS +1] = {0}; 
/* Holds the number of tasks. */                                     
int numTasks = 0;
/* Variable that holds the current Time. */                                              
int Time = 0;      
/* Number of users of all tasks. */                                             
int num_users = 0;
/* Number of activitys. */                                              
int num_activitys = 3;
/* Variable that will be used to determine if there is an error 
   in the description of the activity. */                                          
int description_error = 0;     
/* Array that holds all taks ids, will be used to sort them alphabetically. */                                 
int task_ids[MAX_TASKS];
 /* Array that holds all users of all tasks. */                                          
char users[MAX_USERS-1][MAX_USERS_NAME];
/* Array that holds all activitys, starts with 3 activitys already in it. */                                                
char activitys[MAX_ACTIVITYS][MAX_ACTIVITY_NAME] = {"TO DO","IN PROGRESS", "DONE"};     

/* Bubble sort to sort the description of the task ids in alphabetical order.
   Used in the function show_task. */
int sort_show_tasks(int ids[MAX_TASKS], int left, int right){           
    
    int c, d;
    for (c = left ; c < right - 1; c++)
    {
        for (d = left ; d < right - c - 1; d++)
        {
            if (strcmp(task[ids[d + 1]].description, task[ids[d]].description) < 0)
                exch(ids[d],ids[d+1]);
        }
    }
    return EXIT_CODE;         
}

/* Bubble sort to sort the description of the task ids of an activity in 
   alphabetical order. Used in the function list_tasks. */
int sort_list_tasks(int ids[MAX_TASKS], int left, int right){           
    
    int c, d;

    for (c = left ; c < right - 1; c++)
    {                       
        for (d = left ; d < right - c - 1; d++)
        {
            if (task[ids[d + 1]].initial_instance == task[ids[d]].initial_instance 
            && strcmp(task[ids[d + 1]].description, task[ids[d]].description) < 0)
                exch(ids[d],ids[d+1]);
        }
    }
    return EXIT_CODE;         
}   

/* This function will verify if the activity received is in the programm 
   and will return 1 if the error is spotted.
   If the activity received is not in the activitys array, 
   the verifier will be 0. Case not, it will be 1 and an error will be printed. */
    
int ActivityError( char activity[MAX_ACTIVITY_NAME]){

    int a_verifier = 0, activity_number;
    for (activity_number = 0; activity_number < num_activitys; activity_number++)
    {
        if (strcmp(activitys[activity_number], activity) == 0)
            a_verifier++;                                                               
    }
    if (a_verifier != 1)
    {
        printf(NO_SUCH_ACTIVITY);
        return 1;
    }
    return EXIT_CODE;

}

/* This function will verify all the errors in the move_task function, 
   if there is an error it will return 1, case not it will return 0 
   Input: <int> <char array[]> <char array[]>  Output: <int>*/
int errors_move_task(int id, char user[MAX_USERS_NAME], char activity[MAX_ACTIVITY_NAME]){

    int user_number = 0, u_verifier = 0;

    if (strcmp(activity, "TO DO") == 0 && strcmp(task[id].activity, "TO DO") != 0)
    { 
        /* If the task is being moved to the activity "TO DO" 
        and its not in that activity already, there will be an error. */
        printf(TASK_ALREADY_STARTED);
        return 1;
    }
    /* If the user received is not in the users array, verifier will be 0.
     If not, it will be 1. */
    for (user_number = 0; user_number < num_users; user_number++)  
    {
        if (strcmp(users[user_number], user) == 0)
            u_verifier++;
    }
    /* In case the verifier isnt't 1, an error will be printed . */
    if(u_verifier != 1)                                             
    {                                            
        printf(NO_SUCH_USER);
        return 1;                        
    }
    /* This function will check if the description of the activity is valid. */
    if(ActivityError(activity))                                     
        return 1;
    

    return EXIT_CODE;
}

/* This function will add a task to the programm and verify if the duration 
   or description are valid.
   Input: <duration> <description>  Output: task <id> */
int create_task(int duration, char new_description[MAX_DESCRIPTION]){   /* <t> */
                    
    /* The ids start at 1 , so if there's no tasks,
     the first one will have the id of 1. */
    int id = 1; 

    /* Check if, with the a new task, there are more than the maximum amount tasks. */
    if( numTasks + 1 > MAX_TASKS)                  
    {                  
        printf(TOO_MANY_TASKS);
        return EXIT_CODE;
    }

    if( numTasks != 0 )
    {   
        /* If there are tasks, check if the new task has a repeated name. */                         
        for (id = 1; id <= numTasks; id++)
        {

            if(strcmp(task[id].description, new_description) == 0)
            {
                printf(DUPLICATE_DESCRIPTION);
                return EXIT_CODE;
            }

        }
    }
    if(duration <= 0)
    {
        printf(INVALID_DURATION);
        return EXIT_CODE;
    }
    
    /* The name of the task will be given by the input. */
    strcpy(task[id].description, new_description); 
    /* Every new taks will go to the TO DO activity. */      
    strcpy(task[id].activity, "TO DO");
    /* The anticipated duration of the task will be given by the input. */                
    task[id].anticipated_duration = duration;
    /* The current Time of the program will be the initial time of the task. */           
    task[id].initial_instance = 0;
    /* When the task is created it has 0 users. */                   
    task[id].task_num_users = 0;
    /* The id will go into an array to be sorted alphabetically. */                        
    task_ids[numTasks] = id;                           
    numTasks++;
    printf("task %d\n", id);
    return EXIT_CODE;
}

/* This function is going to either list all tasks, or list the tasks by a specific order.
The input will either read a list of numbers, or no number at all. 
In case no number is read, all tasks in the programm will be printed in alphabetical order.
If numbers are read from the input, the function will verify if they are valid ids 
and will print the respective tasks by the order of ids received. */
int show_tasks( ){                 /* <l> */
    int id = 0;
    char c;
    c = getchar();
    if(c == '\n')
    {
        /* In case no ids were requested, list them all in alphabetical order. */
        sort_show_tasks(task_ids, 0, numTasks);                      
        for (id = 0; id < numTasks; id++)
        {
            printf("%d %s #%d %s\n",task_ids[id],task[task_ids[id]].activity, 
            task[task_ids[id]].anticipated_duration, task[task_ids[id]].description);
        }
    }
    else 
    {   
        /* In case ids were requested, list them by the order received. */          
        while(scanf("%d", &id) == 1)                                       
            if( id > numTasks || id <= 0)             
                printf("%d: NO_SUCH_TASK", id);
                
            else    
                printf("%d %s #%d %s\n",id, task[id].activity,
                task[id].anticipated_duration, task[id].description);
        
    }
    return EXIT_CODE;
}

/* This function will receive a number that will advance the Time of the programm.
   A number will be received by the input, if its 0, it will advance 0 in time, 
   wich means it will return the Current Time.
   In case the number isn't 0, it will return the New current Time after it's been advanced. 
   Input: <time> Output*/
int advance_time(int new_time){                                  /* <n> */

    int test = (int)new_time;
    if( new_time == 0)
    {   
        /* If new time is zero, print current Time. */                                  
        printf("%d\n", Time);
    }

    /* If new time is negative or not type integer (test), print the Error. */
    else if(new_time < 0 || new_time != test)               
    {              
        printf(INVALID_TIME);
    }
    else
    {    
        /* If the new time is valid, add to the current time the value of new time. */                                                                       
        Time += new_time;
        printf("%d\n", Time);
    }
    return EXIT_CODE;
    }

/* This function will either add a user to the programm 
   or list all users by order of creation. */
int manage_users(char new_user[MAX_USERS_NAME]){                         /* <u> */

    /* Each user will have a number according to the order it was created,
       unrelated to the user Id. */
    int user_number = 0, i = 0; 

    /* In case there is no new user in the input, list all users. */                          
    if(strlen(new_user) == 0){  
                               
        /* In case there are no users, return a blank space. */
        if( num_users == 0)                              
            return EXIT_CODE;

        else{
            for( i = 0; i < num_users; i++)
                printf("%s\n", users[i]);
        }
    }
    else
    {   
        /* If there is a new user in the input, we must check if the name 
        is repeated or if it will make the number of users above the maximum. */                                                   
        for (user_number = 0; user_number < num_users; user_number++) 
        
        {   
            /* If there is a user with the same name of the new user it will print an Error. */    
            if(strcmp(users[user_number], new_user) == 0)    
            {        
                printf(USER_ALREADY_EXISTS);
                return EXIT_CODE;
            }

            else if( user_number > MAX_USERS - 1)           
            {      
                printf(TOO_MANY_USERS);
                return EXIT_CODE;
            }
        }
        /* We must add the new user inside the array that holds all users. */
        strcpy(users[num_users], new_user);                  
        num_users ++;
        
    }
    return EXIT_CODE;
}

/* This function will move a task from one activity to another, and apply a user to it.    
   It will also check if the elements received by the input are valid.
   Input: <id> <user> <activity>  Output: duration=<time spent> slack=<time slack> */
int move_tasks(int id, char user[MAX_USERS_NAME], char activity[MAX_ACTIVITY_NAME]){     /* <m> */

    int time_spent = 0, time_slack = 0;

    /* If there is no description in the task id then the task hasn't been created yet. */
    if( id > numTasks || id <= 0)                       
    {                    
        printf(NO_SUCH_TASK);
        return 1;
    }

    /* If the task is being moved to the same activity do nothing. */
    if(strcmp(task[id].activity, activity) == 0)               
        return EXIT_CODE;

    /* If errors_move_task returns 1, then there was an error with the input received. */ 
    if(errors_move_task(id, user, activity) == 1)                             
        return EXIT_CODE;

    else if (strcmp(activity, "DONE") == 0)
    {   
        /* Increase the number of users in the task by 1. */                                
        task[id].task_num_users++;
        /* The new user will go into an array that holds all users of the task. */                                        
        strcpy(task[id].task_users[ task[id].task_num_users -1 ], user);
        /* Time spent in the task is the Current Time minus the time the task was started. */
        time_spent = Time - task[id].initial_instance;   

        /* If the activity came from "TO DO" the duration will be 0. */
        if(strcmp(task[id].activity, "TO DO") == 0)                     
        {                     
            time_spent = 0;
            task[id].initial_instance = Time; 
        }
        /* Time slack is the difference between the time it took 
           to complete the task and anticipated duration of the task. */
        time_slack = time_spent - task[id].anticipated_duration;        
        printf("duration=%d slack=%d\n", time_spent, time_slack);
        /* Change status of the task to activity "DONE". */
        strcpy(task[id].activity,"DONE");                               
        return EXIT_CODE;
    }

    else 
    {
        /* The initial instance of the task is the time it leaves the "TO DO" activity. */
        if(strcmp(task[id].activity, "TO DO") == 0)                     
            task[id].initial_instance = Time;
        /* Change status of the task to the activity received by the input. */                          
        strcpy(task[id].activity, activity);
        /* Increase the number of users in the task by 1. */                            
        task[id].task_num_users++;
        /* The new user will go into an array that holds all users of the task. */                                      
        strcpy(task[id].task_users[ task[id].task_num_users -1 ], user);

        return EXIT_CODE;
    }

return EXIT_CODE;
}  
/* This function will list all tasks in a specific activity given by the input. 
   All the tasks will be listed in order of the time they were created.
   Input: <activity>  Output: <id> <initial instance> <description> */
int list_tasks(char activity[MAX_ACTIVITY_NAME]){                                  /* <d> */

    /* The array "ids" will hold all the ids of the tasks that 
       have the activity received. */
    int ids[MAX_TASKS -1], i = 0, id = 0, l = 0;

    /* This function will check if the description of the activity is valid. */   
    ActivityError(activity);                    
    for(id = 0; id <= numTasks; id++)
    {
        if(strcmp(task[id].activity, activity) == 0 ){         
            ids[i++] = id;      
        }
    }

    sort_list_tasks(ids, 0, i);
    for(l = 0; l < i; l++)
        printf("%d %d %s\n",ids[l], task[ids[l]].initial_instance, task[ids[l]].description);

    return EXIT_CODE;
}

/* This function will either add an activity or list them all. 
   If the input reads a valid activity, it will add it to the programm.
   If the input is empty, it will list all activitys by order of creation. */
int manage_activitys(char activity[MAX_ACTIVITY_NAME]){                    /* <a> */
    int i = 0;  
    if(description_error == 1)                     
     /* If the variable description_error is 1 then the activity has an
        invalid description, therefore we will leave this function. */
        return EXIT_CODE;

    /* In case an activity was received, we check its validity. */    
    if(strlen(activity) != 0)                      
    {                     
        /* If there's an activity inside the activitys array with 
           the same name there will be an error. */
        for(i = 0; i < num_activitys; i++)          
        {        
            if (strcmp(activitys[i], activity) == 0)
            {
                printf(DUPLICATE_ACTIVITY);
                return EXIT_CODE;
            }
        }
        /* If the number of activitys is the maximum you cannot create another one. */
        if( num_activitys == MAX_ACTIVITYS)          
        {                   
            printf(TOO_MANY_ACTIVITIES);
            return EXIT_CODE; 
        }

        /* The new valid activity will go into the activitys array 
           and increase the number of activitys. */
        strcpy(activitys[num_activitys], activity); 
        num_activitys++;
        return EXIT_CODE;
    }
    
    else 
    { 
        /* List all activitys by the order they are created, 
           where the first 3 are pre-inserted in the activitys array. */
        for(i = 0; i < num_activitys; i++)                   
            printf("%s\n",activitys[i]);
    }
    return EXIT_CODE;
}

/* This function will be used to read an activity from the input 
   and apply it to the functions. */
int read_activity(char activity[MAX_ACTIVITY_NAME]){
    
    char c;
    int i = 0;
    /* Description error will be turned to 0 in case 
       there has been a previous invalid description. */
    description_error = 0;                          

    while ((c = getchar()) != '\n') 
    {
        /* If the activity has a lowercase character, it will print an error. */
        if(islower(c) && c != ' ')                  
        {                            
            printf(INVALID_DESCRIPTION);
            /* Description error will turn to 1 if the name is invalid. */
            description_error = 1;                  
            return 0;
        }
        activity[i++] = c;                          
    }
    activity[i] = '\0';
    return EXIT_CODE;
}

/* This function will be used to read a task description 
   from the input and apply it to the create task function. */
int read_description(char description[MAX_DESCRIPTION]){
    
    char c;       
    int i = 0;  

    while (i < (MAX_DESCRIPTION) && (c = getchar()) != '\n') 
        description[i++] = c;
    description[i] = '\0';

    return EXIT_CODE;
}

/* This function will be used to read a user from the input 
   and apply it to the functions. */
int read_user(char user[MAX_USERS_NAME]){                   

    char c;
    int i = 0;   

    while ((c = getchar()) != '\n')
    {
        if(c != ' ')
            user[i++] = c;
    }
    user[i] = '\0';
    return EXIT_CODE;
}

/* The main function will keep receiving inputs until it 
   receives a 'q' character as the input.
   Each letter (option) represents a different function in the programm */
int main(){

    char option, description[MAX_DESCRIPTION] = "\0", 
    activity[MAX_ACTIVITY_NAME] = "\0", user[MAX_USERS_NAME] = "\0", c;
    int duration = 0, id;

    while(scanf("%c", &option) == 1 && option != 'q')
    {
            switch(option)
            {
                case 't':                   /* t <int> <description> */

                    scanf("%d ", &duration);
                    read_description(description);
                    create_task(duration, description);   
                    break;

                case 'l':                   /* l <id> <id> ... */
                    show_tasks();  
                    break;

                case 'n':                   /* n <duration> */

                    scanf("%d", &duration);
                    advance_time(duration);
                    break;

                case 'u':                   /* u [user] */

                    read_user(user);   
                    manage_users(user); 
                    break;

                case 'm':                   /*m <id> <user> <activity> */

                    scanf("%d %s ", &id, user);
                    read_activity(activity);
                    move_tasks(id, user, activity); 
                    break;

                case 'd':                   /* d <activity> */
                    if((c = getchar()) == ' ')
                        read_activity(activity);
                    list_tasks(activity);
                    break;

                case 'a':                   /* a [activity] */
                    activity[0] = '\0';
                    if((c = getchar()) == ' ')
                        read_activity(activity);
                    manage_activitys(activity);
                    break;
            }
        }
        return EXIT_CODE;
    }







