//2_3_School_Band_II 20251108
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>

using namespace std;
void printBandPair(vector<pair<int,int>> &band){
	for(auto &it:band){
		cout<<it.first<<" "<<it.second<<endl;
	}
}
int find_rep(int i,vector<int> &parent,vector<int> &color) {//回傳i所在集合的代表 
    if (parent[i] != i) {
    	int old_parent=parent[i];
        int root= find_rep(old_parent,parent,color);//路徑壓縮，路徑上的點連到root 
        if(color[old_parent]==1){
        	color[i]=1-color[i];
		}
		parent[i]=root;//連到root 
    }
    return parent[i];
}

bool unite(int x,int y,vector<int> &parent,vector<int> &color){
	int xrep = find_rep(x,parent,color);
    int yrep = find_rep(y,parent,color);
    if(xrep==yrep){//在同個集合 
    	if(color[x]==color[y]){//同顏色(在同個群組) 矛盾 
    		return false;
		}
		return true;
	}
    // Make the representative of x's set be the representative of y's set
    color[xrep]=(color[x]==color[y])?1:0;
    parent[xrep] = yrep;
    return true;
}
using namespace std;
int main(){
	//學生人數 ,目前還留存的學生對數 
	int student_count,remaining_pair_count;
	cin>>student_count>>remaining_pair_count;
	vector<pair<int,int>> remaining_bands(remaining_pair_count);//存目前還留存的樂隊
	for(int i=0;i<remaining_pair_count;i++){
		cin>>remaining_bands[i].first>>remaining_bands[i].second;
	}
	int p,k;
	cin>>p>>k;

	vector<vector<pair<int,int>>> all_members(p);
	for(int i=0;i<p;i++) {
		all_members[i].resize(k);
		for(int j=0;j<k;j++) {
			cin>>all_members[i][j].first>>all_members[i][j].second;
		}
	}
	vector<int> parent(student_count);
	vector<int> color(student_count);
	for (int i=0;i<student_count;i++) {
		parent[i]=i;
		color[i]=0;
	}
	for(auto &it:remaining_bands){
		unite(it.first,it.second,parent,color);//依據校長的資料建立關係 
	}
	set<int> error;
	for(int i=0;i<p;i++){
		bool contradiction=false;
		vector<int> tempParent=parent;
		vector<int> tempColor=color;
		for(auto &it:all_members[i]){
			if(unite(it.first,it.second,tempParent,tempColor)==false){
				contradiction=true;
				break;
			}
			//cout<<"try unite"<<it.first<<" and "<<it.second<<endl;
		}
		if(contradiction){
			error.insert(i+1);
		}
	}
	//最後結果由小到大輸出 set會自己排 
	for(auto &it:error){
		cout<<it<<endl;
	}
	//printBandPair(remaining_bands);
	return 0;
}
/*
in:
7 5
0 1 0 2 1 3 2 3 4 5
2 3
0 6 2 4 3 6
0 6 0 3 3 5
out:
2
in:
5 2
0 3 2 3
3 2
0 2 2 4
0 1 1 2
3 4 2 4
out:
1
3
*/
