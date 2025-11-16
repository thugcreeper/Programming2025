/*3_1_Interstellar_Engine 20251110*/
#include<iostream>
#include<vector>
#include<utility>
#include <queue>
#include<algorithm>
#include<climits>
using namespace std;

struct edges{
	int u;
	int v;
	int weight;
};

vector<vector<pair<int,int>>> createAdjList(int vertice_count,vector<edges>& edges){
	vector<vector<pair<int,int>>> adjList(vertice_count+1);
	for(auto &it:edges){
		int u=it.u;
		int v=it.v;
		int w=it.weight;
		adjList[v].push_back({u,w});
		adjList[u].push_back({v,w});
	}
	return adjList;
}

void printAdjList(vector<vector<pair<int,int>>>& adjList) {
    for (int i=0;i<adjList.size();i++) {
        cout <<i<<":";
        for (auto& p : adjList[i])
            cout<<"("<<p.first<<","<< p.second<<") ";
        cout<<endl;
    }
}

vector<long long> dijkstra_length(int start,vector<vector<pair<int,int>>>& adjList){
	int len=adjList.size();
	vector<long long> distance(len,LLONG_MAX);
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> my_priority_queue;

	distance[start]=0;
	my_priority_queue.push({0,start});//0 1表示到星球1需要的時間是0 
	while(!my_priority_queue.empty()){
		pair<long long,int> top = my_priority_queue.top();
		my_priority_queue.pop();
		long long d = top.first;
		int u = top.second;
		if(d>distance[u]){//沒有比較快，不用更新 
			continue;
		}
		for(auto &edge : adjList[u]){//拜訪u所有相鄰節點 
			int v=edge.first;
			int w=edge.second;
		
			if(d+(long long)w<distance[v]){//舉離更短，要更新 
				distance[v]=d+(long long)w;
				my_priority_queue.push({distance[v], v});
			}
		}	
	}
	return distance;
}
int main(){
	int planet_count,lane_count;
	cin>>planet_count>>lane_count;
	vector<edges> edgeList(lane_count);
	vector<int> engines(planet_count+1);
	for(int i=0;i<lane_count;i++){
		struct edges temp_edge;
		cin>>temp_edge.u>>temp_edge.v>>temp_edge.weight;
		edgeList[i]=temp_edge;
	}
	vector<vector<pair<int,int>>> adjList(planet_count+1);
	adjList=createAdjList(planet_count,edgeList);
	//printAdjList(adjList);
	for(int i=1;i<=planet_count;i++){
		cin>>engines[i];
	}
	//計算任意兩點之間的最短距離
	vector<vector<long long>> dist_len(planet_count+1);
	for(int i=1; i<=planet_count; i++){
		dist_len[i]=dijkstra_length(i, adjList);
	}
	//使用某星球的引擎跨越整張圖
	vector<long long> min_time(planet_count+1,LLONG_MAX);
	min_time[1]=0; //init 從星球1出發
	//greater<> 由小排到大 
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> my_priority_queue;

	my_priority_queue.push({0,1});//0 1表示到星球1需要的時間是0 
	while(!my_priority_queue.empty()){
		pair<long long,int> top = my_priority_queue.top();
		my_priority_queue.pop();
		long long currentTime = top.first;
		int u = top.second;
		if(currentTime>min_time[u]){//沒有比較快，不用更新 
			continue;
		}
		for(int v=1;v<=planet_count;v++){ 
			if(v==u) continue;
			if(dist_len[u][v]==LLONG_MAX) continue;
			
			//題目設定: 使用效率係數為 s的引擎通過長度為 w的航線，
			//需要花費 w*s 的時間。
			long long travelTime=dist_len[u][v]*(long long)engines[u];
			if(currentTime+travelTime<min_time[v]){//舉離更短，要更新 
				min_time[v]=currentTime+travelTime;
				my_priority_queue.push({min_time[v], v});
			}
		}	
	}
	cout<<min_time[planet_count]<<endl;
	return 0;
}
/*
in:
5 5
1 2 2
3 2 1
2 4 5
2 5 7
4 5 1
5 2 1 3 3
out:
19

in:
5 10
1 2 5
1 3 5
1 4 4
1 5 8
2 3 6
2 4 3
2 5 2
3 4 1
3 5 8
4 5 2
7 2 8 4 1
out:
36

in:
7 10
3 2 8
2 1 4
2 5 7
2 6 4
7 1 2
4 3 5
6 4 2
6 7 1
6 7 4
4 5 9
7 6 5 4 3 2 1
out:
14
*/
