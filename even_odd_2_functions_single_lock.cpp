#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int count_=0;
mutex m1;

void even(){
    while(1){
        m1.lock();
        if(count_%2==0){
        cout<<"even number" << count_ <<endl;
        count_++;
     }
    if(count_>100){
        m1.unlock();
        break;
    }
    m1.unlock();
  }

}

void odd(){
    while(1){
        m1.lock();
        if(count_%2==1){
        cout<<"odd number" << count_ <<endl;
        count_++;
    }
    if(count_>100){
        m1.unlock(); // if you dont put unlock here, program never terminates.
        break;      // as it will break from while loop and m1 will be locked if unlocked is not used.
        
    }
    m1.unlock();
    
  }
  
  
}
int main()
{
    thread t1(even);
    thread t2(odd);
    t1.join();
    t2.join();
}
