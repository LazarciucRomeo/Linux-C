#include "a2_helper.h"
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct thread_arg_t                                        //structura este pentru informatiile unui thread, procesul din care face parte si numarul acestuia(cheia primara) in procesul respectiv
{

	float  process;
	double thread;
	
} ProThred;
pthread_mutex_t mutex; 
pthread_mutex_t mutex2;
pthread_mutex_t mutex3; 
pthread_mutex_t mutex4;
void conditii_thread(ProThred thinfo[])       //functie in care apar conditiile pe care trebuie sa le indeplineasca  un thread apartinand unui anumit proces 
{
	
	if (thinfo->process == 2 && thinfo->thread == 3)
		pthread_mutex_lock(&mutex);

	

	info(BEGIN, thinfo->process, thinfo->thread);

	if (thinfo->process == 2 && thinfo->thread == 5)
		pthread_mutex_unlock(&mutex);

	if (thinfo->process == 2 && thinfo->thread == 5)
		pthread_mutex_lock(&mutex2);
	
	
		
	

	info(END, thinfo->process, thinfo->thread);
		
	if (thinfo->process == 2 && thinfo->thread == 3)
		pthread_mutex_unlock(&mutex2);	

		
	


}
int creare_process(int id)											
{
	float  pid4, pid5, pid6, pid7;
	
	
	float pid= fork();
	while(pid == 0)
	{
		pthread_mutex_init(&mutex, NULL);
			pthread_mutex_init(&mutex2, NULL);
			pthread_mutex_init(&mutex3, NULL);
			
		info(BEGIN, id, 0);
		if (id == 4)
		{
			
			pid7 = creare_process(7);
			pthread_t threads[4];
			
			
			ProThred arg[4] ;
			for(int i=0; i<4;i++){
				arg[i].process=4;            //adaugarea in structura
				arg[i].thread=i+1;
				}			
			//pthread_mutex_lock(&mutex2);
	
			int i=0;
	while( i < 4){
		pthread_create(&threads[i], NULL, (void*)conditii_thread, &arg[i]);
		i++;
	}
	int j=0;
	while ( j < 4){
		pthread_join(threads[j], 0);
		j++;
	}
			waitpid(pid7, '\0', '\0');
			
		}
		if (id == 2)
		{
			
			pid4 = creare_process(4);
			pid5 = creare_process(5);
			
			pthread_t t[5];
			pthread_mutex_lock(&mutex);
		
			ProThred args[5]; 
			int i=0;
			while( i<5){
				args[i].process=2;
				args[i].thread=i+1; 
				i++;             //adaugarea in structura 
				}			
			pthread_mutex_lock(&mutex2);

			
				 i=0;
	while( i < 5){
		pthread_create(&t[i], NULL, (void*)conditii_thread, &args[i]);
		i++;
	}
	int j=0;
	while ( j < 5){
		pthread_join(t[j], 0);
		j++;
	}

			waitpid(pid4, 0, 0);
			waitpid(pid5, 0, 0);
			
		}
		
		 if (id == 5)
		 	//
		{
			pid6 = creare_process(6);

				pthread_t threads[46];
			
			//
			ProThred ar[46] ;
			for(int i=0; i<46;i++){
				ar[i].process=6;               //adaugarea in structura
				ar[i].thread=i+1;
				}			
		
			
		int i=0;
		
	while( i < 6){
		pthread_create(&threads[i], NULL, (void*)conditii_thread, &ar[i]);		//creeare de thread
		i++; 
	}
	int j=0;
	while ( j < 46 ){
		pthread_join(threads[j], 0);
		j++;
		if(i<46){
			pthread_create(&threads[i], NULL, (void*)conditii_thread, &ar[i]);
			i++;
	}

	}
	
			
			waitpid(pid6, '\0', '\0');
			
		}
		
		info(END, id, 0);
		exit(23);
	}

		return pid;
}
int main(){
	int pid2,pid3,pid8;
    init();
    info(BEGIN, 1, 0);
    pid2 = creare_process(2);

    pid3 = creare_process(3);
  
    pid8 = creare_process(8);

    waitpid(pid2,0,0);

    waitpid(pid3,0,0);

    waitpid(pid8, 0, 0);
 

    info(END, 1, 0);
    return 0;
}