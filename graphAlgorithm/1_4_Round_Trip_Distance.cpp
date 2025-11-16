/*1_4_Round_Trip_Distance 20251011*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits> 
using namespace std;

int shortestPathBFS(vector<vector<int>>& adjList, int start, int end) {
	vector<int> distance(adjList.size(),INT_MAX);
	queue<int> q;
	distance[start]=0;
	q.push(start);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(auto &node : adjList[u]){
			if(distance[node]==INT_MAX){//該節點未造訪過 
				distance[node]=distance[u]+1; 
				q.push(node);
			}
			
		}
	}
	if(distance[end]==INT_MAX) return -1;
	else return distance[end]; 
}
vector<vector<int>> createAdjList(int vertice_count,vector<vector<int>>& edges){
	vector<vector<int>>adjList(vertice_count+1);
	for(auto &it:edges){
		int u=it[0];
		int v=it[1];
		//避免重複 有向圖u->v 
		if(find(adjList[u].begin(),adjList[u].end(),v)==adjList[u].end()){//若v不在list中回傳.end() 
			adjList[u].push_back(v);
		}
	}
	return adjList;
}
void printAdjList(vector<vector<int>>& adjList) {
	for (int i=0;i<adjList.size();i++) {
		cout<<i<<": ";
		for(auto& v:adjList[i])
			cout<<v<< " ";
		cout<<endl;
	}
}

int main(){
	int vertice_count,edge_count;//頂點個數、邊個數 
	int search1,search2;//要查詢距離的兩個頂點 
	cin>>vertice_count>>edge_count;
	cin>>search1>>search2;
	vector<vector<int>>edges(edge_count,vector<int>(2));
	for(int i=0;i<edge_count;i++){
		cin>>edges[i][0]>>edges[i][1];
	}
	vector<vector<int>>adjList=createAdjList(vertice_count,edges);
	/*printAdjList(adjList);
	cout<<"shortest path from"<<search1<<" to "<<search2<<" = "<<shortestPathBFS(adjList,search1,search2)<<endl;
	cout<<"shortest path from"<<search2<<" to "<<search1<<" = "<<shortestPathBFS(adjList,search2,search1)<<endl;
	*/
	int dist1=shortestPathBFS(adjList,search2,search1);
	int dist2=shortestPathBFS(adjList,search1,search2);
	if(dist1==-1 || dist2==-1){
		cout<<-1<<endl;
	}
	else{
		cout<<dist1+dist2<<endl;
	}
	return 0;
} 
/*
in:
4 5
0 3
0 1
1 2  
2 3
3 1
1 0
out:5
in:
2 1
0 1
0 1
out:-1
in:
2 2
0 1
0 1
1 0
out:2
*/
