
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

void read(){
    mtx.lock();  //just for mutex , remove for simple without lock program
    if(count==0){
        cout<<"No data to read from"<<endl;
        mtx.unlock();  
        return;
    }
    
    cout<<"read data: "<<buffer[r_index]<<endl;
    r_index=(r_index+1)%SIZE;
    count--;
    mtx.unlock();
}
void write(int val){
    mtx.lock();  //just for mutex , remove for simple without lock program
    if(count==SIZE-1){
        cout<<"Buffer overflow"<<endl;
        mtx.unlock();
        return;
    }
    
    buffer[w_index]=val;
    w_index=(w_index+1)%SIZE;
    count++;
    mtx.unlock();
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


/*=======================OUTPUT======================
No data to read from
read data: 20
read data: 30


...Program finished with exit code 0
Press ENTER to exit console.


*/
