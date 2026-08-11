
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
using namespace std;

#define SIZE 5
int buffer[SIZE];

mutex mtx;
int r_index=0;
int w_index=0;
int count=0;
condition_variable cv;

void read(){
    unique_lock<mutex>lock(mtx);
    if(count==0){
        cout<<"No data to read from"<<endl;
        cv.wait(lock);
        // return;   Removed as its waiting 
    }
    
    cout<<"read data: "<<buffer[r_index]<<endl;
    r_index=(r_index+1)%SIZE;
    count--;
    
}
void write(int val){
    unique_lock<mutex>lock(mtx);
    if(count==SIZE-1){
        cout<<"Buffer overflow"<<endl;
        lock.unlock();
        cv.notify_all();
        return;
    }
    
    buffer[w_index]=val;
    w_index=(w_index+1)%SIZE;
    count++;
    lock.unlock();
    cv.notify_all();
    
}



int main()
{
    thread t1 (read);
    thread t2 (write,20);
    thread t3 (write,30);
    thread t4 (write,40);
    thread t5 (write,50);
    thread t6 (read);
    thread t7 (read);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    
    
}


/*
No data to read from
read data: 40
read data: 20
read data: 50


output depends on the order of write of the data
Since every thread is independent we cannot guarantee the serial order to be same

such as 20, 30, 40 

*/
