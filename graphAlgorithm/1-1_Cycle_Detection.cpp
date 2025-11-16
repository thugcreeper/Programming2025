/*1_1_Cycle_Detection 20250918*/ 
#include<iostream>
#include<vector>

using namespace std;
vector<vector<int>> createAdjList(int vertice_count,vector<vector<int>>&edges){//create adjacent list
	vector<vector<int>> adjList(vertice_count+1);
    for (auto &it : edges){
        adjList[it[0]].push_back(it[1]); // Directed edge from it[0] to it[1]
        adjList[it[1]].push_back(it[0]);
    }
    return adjList;
}
int countOccurrences(const vector<vector<int>>& adjList,int u,int v){//檢查 u 的鄰居中 v 出現幾次
    int counter=0;
    for (int x:adjList[u]) if (x==v) counter++;
    return counter;
}

int dfs(int current,int parent,vector<vector<int>>&adjList,vector<bool> &visited,vector<int> &parentArr){
	visited[current]=true;
	for(int neighbor:adjList[current]){
		if(neighbor==parent) {
			if(parent!=-1 && countOccurrences(adjList,current,neighbor)>1){
				return 2;
			}		
			continue; 	
		} 

		if(visited[neighbor]){//has cycle
			int length=1;
			int temp = current;
            while (temp != neighbor) {
                length++;
                temp = parentArr[temp];
            }
            return length; 
        } 
		else{
            parentArr[neighbor] = current;//current變成neighbor的parent 
            int cycleLength = dfs(neighbor, current, adjList, visited, parentArr);
            if (cycleLength > 0) return cycleLength;
        }	
	}
	return 0;//no cycle	
}
int getCycleLen(int vertice_count,vector<vector<int>>&edges){
	vector<vector<int>> adjList=createAdjList(vertice_count,edges);
	vector<bool> visited(vertice_count+1,false);//vertice從1-5 size設6(0-5) 
	vector<int> parentArr(vertice_count+1, -1);	

	for (int i=1;i<=vertice_count;i++) {
        if(!visited[i]) {
            parentArr[i]=-1;
            int length=dfs(i, -1, adjList, visited, parentArr);
            if (length > 0) return length;
        }
    }
    return 0;
}
int main(){
	int vertice_count,edge_count;//頂點和邊的個數
	cin>>vertice_count>>edge_count;
	
	vector<vector<int>>edges(edge_count,vector<int>(2));
	for(int i=0;i<edge_count;i++){
		cin>>edges[i][0]>>edges[i][1];
	}
	int length=getCycleLen(vertice_count,edges); 
	if(length) cout<<length;
	else cout<<"There is no cycle."<<endl;
	return 0;
}
/*
in:
5 5
1 2
1 3
2 4
2 5
1 5
out:
3
in:
5 4
1 3
2 4
1 4
3 5
out:
There is no cycle.
in:
(重邊) 
2 2
1 2
1 2
out:
2
*/
