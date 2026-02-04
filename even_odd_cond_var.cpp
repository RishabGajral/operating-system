/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;
mutex mtx;
bool odd=true;
int counter=1;

void even(){
  while(true){
      
      unique_lock<mutex> imtx(mtx);
      while(odd && counter<=10 ){
          cv.wait(imtx);
      }
      
      if(counter >10){
          cv.notify_one();
          break;
      }
      
      cout<<"thread 1"<< counter<<endl;
      counter++;
      odd=!odd;
      imtx.unlock();
      cv.notify_one();
      
  }  
}

void odd1(){
     while(true){
      
      unique_lock<mutex> imtx(mtx);
      while(!odd && counter<=10 ){
          cv.wait(imtx);
      }
      
      if(counter >10){
          cv.notify_one();
          break;
      }
      
      cout<<"thread 2"<< counter<<endl;
      counter++;
      odd=!odd;
      imtx.unlock();
      cv.notify_one();
      
  }  
}

int main()
{
   thread t1(even);
   thread t2(odd1);
   
   t1.join();
   t2.join();
}
