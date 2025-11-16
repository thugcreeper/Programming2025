/*3_2_What_is_floyd 20251116*/
#include<iostream>
#include<vector>
#include<utility>
#include<climits>
#include<algorithm> 
using namespace std;

struct edges{
	int u;
	int v;
	long long weight;
};
void floyd_warshall(vector<vector<long long>> &dist,int vertice_count){
	int i,j,k;
	for( k=1;k<=vertice_count;k++){
		for( i=1;i<=vertice_count;i++){
			for( j=1;j<=vertice_count;j++){
				if(dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX&&
				dist[i][k]+dist[k][j]<dist[i][j]){
					dist[i][j]=dist[i][k]+dist[k][j];
					
				}
			}
		}
	}
}


int main(){
	int city_count,road_count,query_count;
	cin>>city_count>>road_count>>query_count;
	vector<edges> edgeList(road_count+1);//大小要多1，因為測資的city從1開始，這樣比較好算	

	for(int i=1;i<=road_count;i++){
		cin>>edgeList[i].u>>edgeList[i].v>>edgeList[i].weight;
	}
	//距離初始化，自己到自己是0其他是無限大 
	vector<vector<long long>> dist(city_count+1,vector<long long>(city_count+1, LLONG_MAX));
	for(int i=1;i<=city_count;i++){
		dist[i][i]=0;
	}

	for(auto &e : edgeList) {
        dist[e.u][e.v]=min(dist[e.u][e.v],e.weight);
        dist[e.v][e.u]=min(dist[e.v][e.u],e.weight);
    }
	floyd_warshall(dist,city_count);
	for(int i=0;i<query_count;i++){
		int cityA,cityB;
		cin>>cityA>>cityB;
		if(dist[cityA][cityB]==LLONG_MAX){
			cout<<-1<<endl;
		}
		
		else
		cout<<dist[cityA][cityB]<<endl;
		
	}
	return 0;
}
/*
in:
4 3 5
1 2 5
1 3 9
2 3 3
1 2
2 1
1 3
1 4
3 2
out:
5
5
8
-1
3
in:
10 20 10
2 5 6
2 8 1
3 6 5
6 8 7
3 8 1
8 10 9
3 5 7
9 10 4
7 8 1
4 5 10
1 2 3
2 3 10
6 9 2
6 7 9
8 9 6
5 8 5
7 10 4
1 8 2
3 4 1
5 6 3
4 9
7 6
1 2
7 8
7 10
10 7
3 8
5 2
4 8
4 5
out:
8
7
3
1
4
4
1
6
2
7

*/
