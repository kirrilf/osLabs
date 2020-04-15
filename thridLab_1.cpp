#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <time.h> 
#include <semaphore.h>
#include <unistd.h>

struct argsThred
{
    bool flag=false;
    int dis = 0;
    int pipe_id;
};



void* f1(void *args){
    argsThred *arg = (argsThred *)args;
    std::cout << "START 1";
    int *buf = new int[10];
    while (!arg->flag)
    {
       
        for (int i = 0; i < 10; i++)
        {
            std::cout << "1" << std::flush;
            buf[i] = i;
        }

        ssize_t wr =  write(arg->dis, buf, 40);
       

        sleep(1);
    }
    std::cout << "\nSTOP 1";

    int* ex=new int(26);
    std::cout << "END1";
    pthread_exit((void*)ex);
   
}

void* f2(void *args){
    argsThred* arg = (argsThred*) args;
    std::cout<<"START 2";
    int *buf = new int[10];
    while(!arg->flag){
       

        for(int i = 0; i < 10; i++){
            std::cout << "2" << std::flush;
            buf[i] = 0;
        } 
        ssize_t rd = read(arg->dis, buf, 40);
        

        sleep(1);
    }
    std::cout << "\nSTOP 2";
    
    int* ex=new int(28);
    std::cout << "END2";
    pthread_exit((void*)ex);
}



int main(){
    
    std::cout << "START\n";
    pthread_t thread1, thread2;
    argsThred args1, args2;
    int fileds[2];
    fileds[0] = args1.dis;
    fileds[1] = args2.dis;
    int pipe_id = pipe(fileds);
    args1.pipe_id = pipe_id;
    args2.pipe_id = pipe_id;
    pthread_create(&thread1, NULL, f1, &args1);
    pthread_create(&thread2, NULL, f2, &args2);
    getchar();
    std::cout << "STOP threads";
    args1.flag = true;
    args2.flag = true;
    void* exi1;
    void* exi2;
    pthread_join(thread1, &exi1); 
    pthread_join(thread2, &exi2);
    std::cout << std::endl<<*(int*)exi1 << std::endl;
    std::cout<<*(int*)exi2 << std::endl;
    delete (int*)exi1;
    delete (int*)exi2;
    int cl1 = close(fileds[0]);
    int cl2 = close(fileds[1]);
    std::cout << cl1 << std::endl;
    std::cout << cl2 << std::endl;
    std::cout<<"THE END" << std::endl;
     

    return 0;
}

