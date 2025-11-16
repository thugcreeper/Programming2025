/*1_3_School_Band_I 20251005*/
#include<iostream>
#include<vector>
#include <utility>
#include<set>
using namespace std;

void printTest(set<int> &people,vector<pair<int,int>> &friendArr){
	cout<<"people set:"<<endl; 
	for(auto &i:people){
		cout<<i<<" ";
	}
	cout<<"\nfriend pair:"<<endl; 
	for(auto &i:friendArr){
		cout<<i.first<<" "<<i.second<<endl;
	}
}
bool canGrouped(int population,vector<pair<int,int>> &friendArr){
	vector<vector<int>> adjlist(population+1);
	vector<int> color(population+1,-1);//-1未上色 只有0 1兩顏色 
	
	for(auto &i:friendArr){//建立graph 
		adjlist[i.first].push_back(i.second);
		adjlist[i.second].push_back(i.first);
	}
	for(int i=1;i<=population;i++){
		if(color[i]!=-1) continue;
		vector<int> stack={i};
		color[i]=0;
		while(!stack.empty()){
			int temp=stack.back();//stack中最後一個元素
			stack.pop_back();//記得pop避免無窮迴圈 
			for(int j:adjlist[temp]){//檢查和temp相鄰的所有node 
				if(color[j]==-1){
					color[j]=1-color[temp];//給相反的顏色確保兩人不認識 
					stack.push_back(j);	
				}
				else if(color[j]==color[temp]){//顏色一樣,不可分在同一組 
					return false;
				}
			}
		}
	}
	return true;
}
int main(){
	int population,friendPairs;//學校人數、認識的有幾對
	cin>>population>>friendPairs;
	set<int> people;
	vector<pair<int,int>> friendArr;
	for(int i=0;i<friendPairs;i++){
		pair<int,int> friends;
		cin>>friends.first>>friends.second;
		people.insert(friends.first);
		people.insert(friends.second);
		friendArr.push_back(friends);
	}
	if(canGrouped(population,friendArr)){
		cout<<"YES"<<endl;
	}
	else{
		cout<<"IMPOSSIBLE"<<endl;
	}
	//printTest(people,friendArr);
	return 0;
}
/*
in:
5 3
1 2
1 3
4 5
out:
yes

in:
4 5
1 2
1 4
2 3
2 4
3 4
out:
IMPOSSIBLE
*/
