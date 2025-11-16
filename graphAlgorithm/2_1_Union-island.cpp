/*2_1_Union-island 20241018*/
#define edge_len 1000
#define set_size edge_len*edge_len
#include<iostream>
#include<vector>
using namespace std;

// 把 (x,y) 轉成唯一ID
int getId(int x, int y){
    return x*edge_len+y;
}

int find_rep(int i,vector<int> &parent) {//回傳i所在集合的代表 
    if (parent[i] != i) {
        parent[i]= find_rep(parent[i],parent);//路徑壓縮，路徑上的點連到root 
    }
    return parent[i];
    /*這裡我原本寫(未路徑壓縮):
	if (parent[i] == i) {
        return i;
    }
	return find_rep(parent[i],parent);
     可能會形成chain，提高時間複雜度 
	*/
}

void make_set(int x,int y,vector<int> &parent){
	int xrep = find_rep(x,parent);
    int yrep = find_rep(y,parent);
    // Make the representative of x's set be the representative of y's set
    parent[xrep] = yrep;
}


int main(){
	int event_count;
	int selection;//1:板塊浮出水面 2:檢查連通 
	int x,y,a,b,c,d;
	vector<int> parent(set_size);
	vector<bool> land(set_size,false);//記錄板塊是否浮出 
	for(int i=0;i<set_size;i++){
		parent[i]=i;
	}
	cin>>event_count;
	for(int i=0;i<event_count;i++){
		cin>>selection;
		if(selection==1){
			cin>>x>>y;
			x--;
			y--;//避免1000的時候超出陣列索引
			int id=getId(x,y); 
			land[id]=true;
			//檢查上下左右 
			int dx[4]={-1,1,0,0};
            int dy[4]={0,0,-1,1};
            for(int k=0;k<4;k++){
                int nx=x+dx[k];
                int ny=y+dy[k];
                if(nx>=0 &&nx<edge_len&&ny>=0&&ny<edge_len){
                    int nid=getId(nx,ny);
                    if(land[nid]) make_set(id,nid,parent);
                }
            }
		}
		else if(selection==2){
			cin>>a>>b>>c>>d;
			a--;b--;c--;d--;
			int id1=getId(a,b);//a b 板塊id 
			int id2=getId(c,d);
			if(land[id1] && land[id2] &&(find_rep(id1,parent) == find_rep(id2,parent)))
			cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
		else{
			cout<<"error"<<endl;
		}
	} 
	
	return 0;
} 
/*
[1 , x, y ] : 位於 (x, y) 小板塊浮出水面 (1 <= x , y <= 1000)
[2, a, b, c, d ] : 科學家想知道此刻位置在 (a,b) 的A板塊是否有跟位於 (c,d) 的C板塊連通 (1 ,<= a, b, c, d <= 1000)
in:
5
1 1 1
1 1 2
1 1 3
2 1 1 1 4
2 1 1 1 3
out:
No
Yes
in:
10
1 1 1
1 1 2
1 2 2
2 1 1 3 3
1 2 3
1 3 3
2 1 1 3 3
1 1000 1000
2 1 1 1000 1000
2 1 1 1 2
out:
No
Yes
No
Yes
*/
