/*2_2_Police_Arrest20251025*/
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int find_rep(int i ,vector<int>& parents) {//回傳i所再集合的代表 
    if (parents[i] != i) {
        parents[i]= find_rep(parents[i],parents);//路徑壓縮，路徑上的點連到root 
    }
    return parents[i];
}

void unite(int x,int y ,vector<int>& parents, vector<int>& max_population){
	int rootX=find_rep(x,parents);
	int rootY=find_rep(y,parents);
	if(rootX!=rootY){
		parents[rootX]=rootY;
		max_population[rootY]= max(max_population[rootX],max_population[rootY]);
	}
}

bool hasRoad(int u,int v,set<pair<int,int>> &roads){
	if(u>v) swap(u,v);//這裡swap是因為假如插入1 3跟插入3 1若不swap會看做兩個不同的邊，但題目是無向圖 
	return roads.count({u,v});//存在該元素回傳1否則0 
}
void cutRoad(int u,int v,set<pair<int,int>> &roads){
	if(u>v) swap(u,v);
	roads.erase({u,v});
}

int main(){
	int city_count,road_count,operation_count;
	set<pair<int,int>> roads;
	cin>>city_count>>road_count>>operation_count;
	vector<int> gang_population(city_count+1);//第i座城市幫派份子數目 
	for(int i=1;i<=city_count;i++){
		cin>>gang_population[i];
	}
	
	vector<pair<int,int>> edgeList;
    for(int i=0; i<road_count;i++){//輸入雙向連通道路 
        int u,v;
        cin>>u>>v;
        if(u>v) swap(u,v);
        roads.insert({u,v});
        edgeList.push_back({u,v});
    }
	//記下操作
	vector<pair<int,int>> op_cut(operation_count);
    vector<int> op_query(operation_count); 
    vector<int> op_type(operation_count);
	//1 u v：切斷城市 u 和城市 v 之間的道路（保證該道路存在且未被切斷）。
	//2 c：查詢城市 c 以及所有與城市 c 連通的城市中，幫派份子人數的最大值。
	for(int i=0;i<operation_count;i++){
		cin>>op_type[i];
		if(op_type[i]==1){//1 cut 2 search 
			cin>>op_cut[i].first>>op_cut[i].second;
            if(op_cut[i].first>op_cut[i].second) 
				swap(op_cut[i].first, op_cut[i].second);
            // 先把這條邊記錄要砍掉
		}
		else if(op_type[i]==2){
            cin >> op_query[i];
		}
		else{
			cout<<"Invalid operation"<<endl;
		}
	}
	
    // 把所有被 cut 的邊先從 roads 刪除（表示最後狀態下已斷開）
    for(int i=0;i<operation_count;i++){
        if(op_type[i]==1){
            roads.erase(op_cut[i]);
        }
    }
    vector<int> parents(city_count+1);
	vector<int> max_population(city_count+1);
	for(int i=1;i<=city_count;i++){
		parents[i]=i;
        max_population[i]=gang_population[i];
	}
	// 建立「最後狀態」的連通情況
	for(auto &e : roads){
        unite(e.first,e.second,parents,max_population);
    }

    // 反向處理操作（因為 cut 要反過來變成 union）
    vector<int> ans; 
    for(int i=operation_count-1;i>=0;i--){
        if(op_type[i]==2){
            int city=op_query[i];
            int root=find_rep(city,parents);
            ans.push_back(max_population[root]);
        }
        else{
            // cut 反過來就是 union
            int u=op_cut[i].first;
            int v=op_cut[i].second;
            unite(u,v,parents,max_population);
        }
    }

    // 因為答案是反向記錄，倒回輸出
    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]<<endl;
    }
	return 0;
} 

/*
in:
2 1 5
7 3
1 2
2 1
2 2
1 1 2
2 1
2 2
out:
7
7
7
3

in:
3 3 6
4 5 6
1 2
2 3
3 1
2 3
1 1 3
2 1
1 2 3
2 1
2 3
out:
6
6
5
6
*/
