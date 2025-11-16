/*1_2_Pouring_Water_Problem_II 20250920*/
#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
typedef struct{
	vector<int> cups;
	int steps;
}State;

int gcd(int a,int b){
    if (b==0)
       return a;
    return gcd(b, a%b);
}

int pouring_water(vector<int> &cups,set<vector<int>> &visited,int t,int k){//t:要喝的總量，k:可執行次數 
	//push一開始狀態到queue 
	queue<State> q;
	State initial;
	initial.steps=0;
	initial.cups=vector<int>(7,0);
	q.push(initial);
	int g = cups[1];
	for (int i = 2; i <= 6; i++) {//若兩個杯子的gcd無法整除1為false 
	    g = gcd(g,cups[i]);
	}
	if (t%g!= 0) {
	    return 0; 
	}
    if(t==0)
    	return 1;
    
	while(!q.empty()){//BFS
		int sum = 0;
		State current=q.front();
		q.pop();
        for (int x : current.cups) sum += x;

        if(sum==t && current.steps<=k){
        	return 1;
		}

        for(int i=1;i<=6;i++){
        	if (current.cups[i] < cups[i]) {
		        State next = current;
		        next.cups[i] = cups[i];//裝滿 
		        next.steps++;
		        if(next.steps <= k && !visited.count(next.cups)){//count用於檢查這個狀態是否造訪過 
		        	q.push(next);
		        	visited.insert(next.cups);
				}
    		}
		}
		for (int i=1; i<=6; i++) {
		    if (current.cups[i] > 0) {
		        State next = current;
		        next.cups[i] = 0;//倒掉 
		        next.steps++;
		    	if(next.steps <= k && !visited.count(next.cups)){
	        	q.push(next);
	        	visited.insert(next.cups);
				}
		    }
		}
		for(int i=1;i<=6;i++){
			for(int j=1;j<=6;j++){
				if (i==j) continue;
		        if (current.cups[i] == 0) continue;   // 沒東西倒
		        if (current.cups[j] == cups[j]) continue; // j 已滿
		        State next = current;
		        int space = cups[j] - next.cups[j];//被倒的杯子還剩多少空間 
		        int move = min(next.cups[i], space);//可以倒的量 
		        next.cups[i] -= move;
		        next.cups[j] += move;
		        next.steps++;
		        if(next.steps <= k && !visited.count(next.cups)){
		        	q.push(next);
		        	visited.insert(next.cups);
				}
			}
		}	
	}
	return 0;
}
int main(){ 
	int t,k;//t、k 代表朋友們想喝的紅茶量、限制的操作次數 
	vector<int> cups(7);
	set<vector<int>> visited;
	cin>>t>>k;
	for(int i=1;i<=6;i++){
		cin>>cups[i];
	}
	if(pouring_water(cups,visited,t,k)){
		cout<<"True"<<endl;
	}
	else{
		cout<<"False"<<endl;	
	}
	return 0;
} 
/*
in:
10 3
1 2 3 4 5 6
out:
true
in:
3 10
2 2 2 2 2 2
out:
false
in:
5 3
1 1 1 1 1 1
out:
false
*/
