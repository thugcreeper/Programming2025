#include<iostream>
#include<thread>
#include<queue>
#include <chrono>

using namespace std;

queue<int> temp;
int addTo(int start,int end){
	int sum=0;
	for(int i=start;i<=end;i++){
		sum+=i;
	}
	temp.push(sum);
	return sum;
}


int main(){
	//紀錄開始時間點 
	chrono::steady_clock::time_point startTime = chrono::steady_clock::now();
	int sum=0;
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

	int len=temp.size();
	for(int i=0;i<len;i++){
		sum+=temp.front();
		temp.pop();
	}
	//結束時間點 
	chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
	int multiTime=(endTime-startTime).count();
	cout<<"Final Sum: "<<sum<<endl;
	cout<<"Final queue size: "<<temp.size()<<endl;
	cout<<"Multithread time: "<<multiTime<<" nanosecond"<<endl;
	//單執行緒
	startTime = chrono::steady_clock::now();
	sum=addTo(1,100);
	endTime = chrono::steady_clock::now();
	int singleTime=(endTime-startTime).count();
	cout<<"Final Sum: "<<sum<<endl;
	cout<<"Single time: "<<singleTime<<" nanosecond"<<endl;
	cout<<"Speed up: "<<float(singleTime)/multiTime<<endl; 
	return 0;
} 
