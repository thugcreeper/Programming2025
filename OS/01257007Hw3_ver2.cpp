#include<iostream>
#include<thread>
#include<queue>
#include <chrono>
#include<semaphore.h>

using namespace std;
int sum=0;
sem_t smp;
void addTo(int start,int end){
	int temp=0;
	for(int i=start;i<=end;i++){
		temp+=i;
	}
	sem_wait(&smp);//-1,semaphore value=0,若有thread呼叫這個函式,他會被擋住直到value>0 
	sum+=temp;
	sem_post(&smp);//value+1,如果少這行會發生deadlock 
}
 

int main(){
	//紀錄開始時間點 
	chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
	sem_init(&smp,0,1);//初始化 semaphore 0表示 
	int n=4; 
	int end=100; 
	int range=end/n; 
	vector<thread> threads(n); 
	for(int i=0;i<n;i++){ 
		threads[i]=thread(addTo,i*range+1,(i==n-1)?end:(i+1)*range); 
	}
	for(int i=0;i<n;i++){//等所有thread都結束 
		threads[i].join();
	}


	//結束時間點 
	chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
	int multiTime=(endTime-startTime).count();
	cout<<"Final Sum: "<<sum<<endl;
	cout<<"Multithread time: "<<multiTime<<" nanosecond"<<endl;
	sem_destroy(&smp);
	return 0;
} 
