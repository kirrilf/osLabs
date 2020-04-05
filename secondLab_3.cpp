#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <time.h> 
#include <unistd.h>
#include <semaphore.h>
#include <cstring>

struct argsThred
{
    bool flag=false;
	sem_t* sem;
};



void* f1(void *args){
    argsThred* arg = (argsThred*) args;
    std::cout<<"START 1";
    timespec time;
    int erro = 0;

    while(!arg->flag){
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_sec++;
        if(!(erro = sem_timedwait(arg->sem, &time))){

            for(int i = 0; i < 5; i++){
                std::cout << "1" << std::flush;
            } 
    
            sem_post(arg->sem);

            sleep(1);
        }else{
            std::cout << "Thread1:" << strerror(erro) << std::endl;
        }
    }
    std::cout << "\nSTOP 1";
    
    pthread_exit(0);
   
}

void* f2(void *args){
    argsThred* arg = (argsThred*) args;
    std::cout<<"START 2";
    timespec time;
    int erro = 0;

    while(!arg->flag){
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_sec++;
        if(!(erro = sem_timedwait(arg->sem, &time))){

            for(int i = 0; i < 5; i++){
                std::cout << "2" << std::flush;
            } 
    
            sem_post(arg->sem);

            sleep(1);
        }else{
            std::cout << "Thread2:" << strerror(erro) << std::endl;
        }
    }
    std::cout << "\nSTOP 2";
    
    pthread_exit(0);
}



int main(){
    
    std::cout << "START\n";
    pthread_t thread1, thread2;
    argsThred args1, args2;
    sem_t sem;
    args1.sem = &sem;
    args2.sem = &sem;
    sem_init(&sem, 0, 1);
    pthread_create(&thread1, NULL, f1, &args1);
    pthread_create(&thread2, NULL, f2, &args2);
    getchar();
    std::cout << "STOP threads";
    args1.flag = true;
    args2.flag = true;
    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL);
    sem_destroy(&sem);
   
    std::cout<<"THE END" << std::endl;
     

    return 0;
}
