/**************************************    Race Condition   **********************************/
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;
int count=0;

void increase(){
    mtx.lock();
    for(int i=0; i<10000000; i++){
        count++;
    }
    mtx.unlock();
}

int main()
{
    thread t1(increase);
    thread t2(increase);
    t1.join();
    t2.join();
    cout<<count<<endl;

    return 0;
}
