
/* SOURCES:
 * http://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread.h.html
 * http://stackoverflow.com/questions/23529773/dining-philosopher-program-c
 * Old conestoga college project
 */ 

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
  
#define NUMBEROFPHILOSOPHERS 5

/*the possible states of the philosophers*/
#define THINKING 0
#define HUNGRY 1
#define EATING 2

/*macros to get the left+right philosophers to the current one, copied from the stack overflow example in the sources*/
#define LEFTPHILOSOPHER (philosopher+4)%NUMBEROFPHILOSOPHERS
#define RIGHTPHILOSOPHER (philosopher+1)%NUMBEROFPHILOSOPHERS
  
sem_t mutex;
sem_t sem[NUMBEROFPHILOSOPHERS];
int number_of_eating = 0;
int number_of_philosophers = 0;
  
void *simulation(void *num);
void pick_up_fork(int);
void put_down_fork(int);
void begin_eating(int);
  
int philosopher_state[NUMBEROFPHILOSOPHERS];
int philosopher_eat_count[NUMBEROFPHILOSOPHERS];
int phil_num[NUMBEROFPHILOSOPHERS]={0,1,2,3,4};

int phil_eaten[NUMBEROFPHILOSOPHERS] = {0};
 
void main(int argc, char *argv[])
{
    pthread_t thread_id[NUMBEROFPHILOSOPHERS];
    sem_init(&mutex, 0, 1);
    number_of_philosophers = atoi(argv[1]);
    number_of_eating = atoi(argv[2]);
    
	
    int i = 0; 
      
    for(i = 0; i < number_of_philosophers; i++)
    {
        sem_init(&sem[i],0,0);
    }   
    for(i = 0; i < number_of_philosophers; i++)
    {
        pthread_create(&thread_id[i],NULL, simulation, &phil_num[i]);
    }
    for(i = 0; i < number_of_philosophers; i++)
    {
        pthread_join(thread_id[i], NULL);
	}

	printf("All philosophers have eaten atleast %d times. Simulation finished.\n",number_of_eating);
	
}

/*
 * run the simulation, pass in the current philosopher
 */   
void *simulation(void *current_philosopher)
{
	while(1)
	{
		int *i = current_philosopher;/*pointer to modify the philosopher's state and etc later*/
		int x = 0;
		int count = 0;
		//printf("\n[1]%d [2]%d [3]%d [4]%d [5]%d\n",  phil1, phil2,phil3,phil4,phil5);  
		sleep(1);
		pick_up_fork(*i);		
		sleep(1);
		put_down_fork(*i);
		
		/*check how many philosophers have eaten the correct amount of times*/
		for(x = 0; x < number_of_philosophers; x++)
		{
			if(phil_eaten[x] >= number_of_eating)
			{
				count++;
			}
		}
		/*if all of the ate the correct times, exit*/	
		if(count == number_of_philosophers)
		{
			return;
		}
	}
		
}

/*
 * If the forks are available, current philosopher begins eating
 */ 
void begin_eating(int philosopher)
{
	/*if current philosopher is not eating, and neither are the ones beside him, begin to eat*/
    if (philosopher_state[philosopher] == HUNGRY && philosopher_state[LEFTPHILOSOPHER] != EATING && philosopher_state[RIGHTPHILOSOPHER] != EATING)
    {
        philosopher_state[philosopher] = EATING;
        
        printf("Philosopher %d eating\n",philosopher+1);
        
        phil_eaten[philosopher]++;
        
        //if(philosopher == 0){phil1++;}
        //if(philosopher == 1){phil2++;}
        //if(philosopher == 2){phil3++;}
        //if(philosopher == 3){phil4++;}
        //if(philosopher == 4){phil5++;}
        
        sem_post(&sem[philosopher]);/*update mutex*/
    }
}

/*
 * Wait on the mutex (aka the forks), switch state to eating, let that philosopher start to eat, and stop thinking
 */   
void pick_up_fork(int philosopher)
{
    sem_wait(&mutex);
    philosopher_state[philosopher] = HUNGRY;

    begin_eating(philosopher);
    
    sem_post(&mutex);
    sem_wait(&sem[philosopher]);
}

/*
 * Wait on the mutex (aka the forks), switch state to thinking, let that philosopher start to think, and stop eating
 */     
void put_down_fork(int philosopher)
{
	/*wait on mutex, switch state to thinking*/
    sem_wait(&mutex);
    philosopher_state[philosopher] = THINKING;
    
    printf("Philosopher %d thinking\n",philosopher + 1);
    
    /*left and right philosophers can now beging eating as the current one has stopped*/
    begin_eating(LEFTPHILOSOPHER);
    begin_eating(RIGHTPHILOSOPHER);
    
    sem_post(&mutex);/*update mutex*/
}
