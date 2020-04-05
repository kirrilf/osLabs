
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <time.h> 
#include <unistd.h>




void* f1(void *args){
   bool *fl1 = (bool*)args;
   std::cout<<"START 1";
    while(*fl1){
        std::cout << "1"<<std::flush; 
        sleep(1);
    }
    int* ex=new int(29);
    std::cout<<"END1";
    pthread_exit((void*)ex);
   
}

void* f2(void *args){
    bool *fl2 = (bool*)args;
    std::cout<<"START 2";
    while(*fl2){
        std::cout << "2"<<std::flush;
        sleep(1);
    }

    int* ex=new int(28);
    std::cout << "END2";
    pthread_exit((void*)ex);
   
}



int main(){

    pthread_t thread1;
    pthread_t thread2;
    bool fl1 = true;
    bool fl2 = true;
    void*flOne = (bool*)&fl1;
    void*flTwo = (bool*)&fl2;
    pthread_create(&thread1, NULL, f1, flOne);
    pthread_create(&thread2, NULL, f2, flTwo);
    std::cout<<"ENTER";
    getchar();
    std::cout << "STOP threads";
    fl1 = false;
    fl2 = false;
    void* exi1;
    void* exi2;
    pthread_join(thread1, &exi1);
    std::cout << std::endl<<*(int*)exi1 << std::endl;
    //std::cout<<endl;
    pthread_join(thread2,&exi2);
    std::cout<<*(int*)exi2 << std::endl;
    //std::cout<< endl;
    delete (int*)exi1;
    delete (int*)exi2;
    std::cout<<"THE END" << std::endl;
     

    return 0;
}
