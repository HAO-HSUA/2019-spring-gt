# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

## How to run

### Linux

```
# clone first (with submodu
$ git clone --recursive https://github.com/<your-name>/Graph-Theory-Project-Template.git
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
```

### Windows
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
演算法思路(無向圖):

這次作業目標主要是找最短路徑，輸入為一個graph，使用函示庫將graph輸入至程式中，由於函式庫採用的是有向圖的設計模式，而本次作業我主要以
無向圖為主要構想，所以我會根據現有graph的邊，自己額外補上相反的方向，使graph的節點都為雙向的。
ex:graph中有edge,a->g，我會補上g->a的edge。

中國郵差問題是一個graph中出現奇數degree的vertex，導致無法在不走重複路徑下，走完graph中所有的edge。
根據上述，在程式設計中，我會先去計算graph中哪些的vertex具有奇數的degree，除此之外，還會將具有奇數degree的vertex進行保存。

若要將graph中所有edge走完，勢必會走重複路徑，那勢必要考慮重複走哪些路段可以具有最短路徑的情形。
根據理論，可以推測重複的路徑都與奇數degree的vertex有關，因此我會去計算具有奇數degree的vertex的集合中，兩兩vertex之間的最短路徑。
除了上述，還要去思考奇數degree的vertex數量超過兩個以上，需從節點的排列組合中挑選一組，可以確保graph具有最短路徑。

經過上述步驟，將重複的路徑納入一起考慮，可以使一開始的graph存在尤拉迴圈，因此可以從圖中任選一點同時為起點和終點，必須經過尤拉graph
中所有的edge，最後再回到起始點，這個過程的關鍵在決定graph中的vetex鄰域，也就是說有可能會發生走不回起始點的情形。
ex:原先是一個connected graph，節點的順序若決定不好，有可能會面臨成disconnected graph的事件。


綜合上述過程，就可以找出一個graph中的最短路徑。
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
程式碼解說:
1.
	nm->interpret("text.txt"); 
    Edge *elist = nm->elist;                  /*這裡主要是將graph讀入，並宣告一些變數*/
	Vertex **vlist=nm->vlist;
	string a;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
	int initial_path_num=0;;
    while(elist!=NULL){
        initial_path_num+=1;                 /*這裡主要是確認edge數量由無與輸入測試資料相同*/
		elist=elist->next;
    }
	cout<<initial_path_num<<endl;
	elist=nm->elist;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
2.
	 int v_num=0;
	 while(vlist[v_num]!=NULL){
		 
			v_num++;                       
			                                  /*計算graph中vertex數量;變數size主要是拿來建立矩陣的維度*/
	 }
	  cout<<"v:"<<v_num;
	  cout<<endl;
	  const int size=v_num;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

3.  int degree[size][2];
	int count=0;
	elist=nm->elist;
	for (int i=0;i<size;i++){
		while(elist!=NULL){
			if((elist->head->name)==(vlist[i]->name)  || (elist->tail->name)==(vlist[i]->name))
				count=count+1;
			else
				count=count;
			elist=elist->next;
		}
	                                              /*建立一個2維degree陣列，第一維存放每個vertex的degree，
												    第二維用來判斷是否為奇數degree，1:是奇數degree,0:不是 */
		degree[i][1]=count;
		if(count%2!=0)
			degree[i][2]=1;
		else
			degree[i][2]=0;
		count=0;
		elist=nm->elist;
	}
	for(int i=0;i<size;i++){
			cout<<degree[i][1]<<";"<<degree[i][2]<<endl;
	
	}
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
4.	for(int i=0;i<size;i++){
			if(degree[i][2]==1){
				odd_vertices.push_back(nm->get_node(nm->vlist[i]->name));
			}
	
	}                                                     /*將具有奇數degree的vertex存入odd_vertices*/
	cout<<odd_vertices.size()<<endl;
    cout<<";"<<endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
5.	elist=nm->elist;
	for (int i=0;i<initial_path_num;i++){
		nm->connect(elist->tail->name,elist->head->name);
		elist=elist->next;                                /*因為無向圖的考量，將單向graph變為雙向graph*/
	}
	  nm->print_all_e();	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
6.	const int mini_path_size=odd_vertices.size();
	cout<<"::::"<<mini_path_size<<endl;
	int mini_path[mini_path_size][mini_path_size];
	Path *path;
	path=new Path();                                       /*這裡主要是針對具有奇數degree的vertex，兩兩的最短距離，
	path->append(nm->elist);                                 我是使用find_path這個函式庫，計算最短路徑，而mini_path陣列
	vector<vector <Edge*>> pa;                               是存放最短路徑的陣列，由於是無向圖構思，這個陣列是對稱的。*/
	vector <Edge*> p_temp;
	for (int i=0;i<mini_path_size;i++){
		for(int j=0;j<mini_path_size;j++){
			if(i==j){
				mini_path[i][j]=0;
			}
			else{
				pa=path->find_paths((odd_vertices[i]->name),(odd_vertices[j]->name));
				for(int z=0;z<pa.size();z++){
					if(z==0||p_temp.size()>pa[z].size())
						p_temp=pa[z];
				}
				mini_path[i][j]=p_temp.size();	
			
			}		
		}	
	
	}
	for (int i=0;i<mini_path_size;i++){
		for(int j=0;j<mini_path_size;j++){
			cout<<mini_path[i][j]<<endl;
		}	
	}
	cout<<"----------------------------------------------------"<<endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
7.	int flag=0;
	int i=0;
	int var=0;
	cout<<"......."<<odd_vertices.size()/2<<endl;
		while(flag<(odd_vertices.size()/2)){
			nm->connect(odd_vertices[i]->name,odd_vertices[i+1]->name);
			nm->connect(odd_vertices[i+1]->name,odd_vertices[i]->name);
			while(1){
				if(vlist[var]->name==odd_vertices[i]->name)
					break;
				else
					var=var+1;
			}
			degree[var][1]=degree[var][1]+1;
			var=0;
			while(1){                                              /*這裡主要是在針對兩兩奇數degree的vertex進行配對，
				if(vlist[var]->name==odd_vertices[i+1]->name)       並且將配對後的重複路徑添加到原先graph中，使graph成為尤拉圖，
					break;                                          成為尤拉圖，過程中因為重複路徑會造成原先的vertex的degree改變，
				else                                                需重新計算每個vertex degree。*/
					var=var+1;
			}
			degree[var][1]=degree[var][1]+1;
			var=0;
			
			i=i+2;
			flag=flag+1;
		}
		
		nm->print_all_e();
		for(int i=0;i<size;i++){
			cout<<degree[i][1]<<";"<<degree[i][2]<<endl;
	
		}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
8. 		elist=nm->elist;
		int path_num=0;
		while(elist!=NULL){
		adv[elist->head->name].push_back(elist);                  /*這裡主要是記錄添加重複路徑的情況下graph中edge的個數*/
		path_num+=1;
		elist=elist->next;                                        
		}
		cout<<path_num<<endl;
		cout<<";"<<endl;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
9.  count=0;
		while(elist!=NULL && count!=v_num){
			for(int i=0;i<adv[elist->head->name].size();i++)	
				cout<<adv[elist->head->name].at(i)->head->name<<adv[elist->head->name].at(i)->tail->name<<";"<<endl;
			a=elist->head->name;
			elist=elist->next;
			/*if(a==elist->head->name)
				elist=elist->next;
			else
				elist=elist;*/                                *這裡主要先決定graph中的起始點，會根據這個起始點找到相鄰的節點,
			while(elist->head->name==a){                      在眾多的相鄰節點下，以connected graph作為判斷，判斷這條edge若切
				a=elist->head->name;                          斷後，是否會改變connect graph的性質，我一樣是用find-path的函示庫，
				elist=elist->next;                            若任兩點的path數量大於1，代表即使切斷，也不會使原先的connected
			}                                                 graph變為disconnected；至於另外一個判斷條件為若還沒走到最後，就將 
			count+=1;	                                      起始點周遭的edge都走完，這樣也是不合理的，最後會將走過正確的edge存入
		}                                                     aaa向量裡。
		string hvlist;
		elist=nm->elist;
		hvlist=vlist[0]->name;
		Path *path2;
		path2=new Path();
		vector<vector <Edge*>> pa1;
		path2->append(nm->elist);
		i=0;
		while(i<path_num/2){
			//elist=nm->elist;
			while(elist!=NULL){
				if(hvlist==elist->head->name)	
					plist.push_back(elist);
				elist=elist->next;
			
			}
			int z=0;
			cout<<"..cc.."<<plist.size()<<endl;
			if(plist.size()>1){
				while(1){
					vector<vector <Edge*>> pa1;
					path2->append(nm->elist);
					pa1=path2->find_paths((plist[z]->head->name),(plist[z]->tail->name));
					path2->debug();
					cout<<"......"<<pa1.size()<<endl;
					if(pa1.size()>1 ){
						if(i!=7 && (plist[z]->tail->name==vlist[0]->name))
							z=z+1;
						else
							break;
					}
					
					else
						z=z+1;	
				}		
			}
			aaa.push_back(plist[z]);
			nm->disconnect((plist[z]->head->name),(plist[z]->tail->name));
			nm->disconnect((plist[z]->tail->name),(plist[z]->head->name));
			nm->print_all_e();
			hvlist=plist[z]->tail->name;
			cout<<hvlist<<endl;
			plist.clear();
			z=0;
			elist=nm->elist;
			adv.clear();
			i=i+1;
		
		}
		for(int i=0;i<aaa.size();i++){
			cout << aaa.at(i)->head->name << "->" << aaa.at(i)->tail->name << endl;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
測試資料:                                        
           a b                                              
           c a
           c d
           d e
           e c
           e b
		 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
測試結果:
           a->c
           c->d
           d->e
           e->b
           b->e
           e->c
           c->b
           b->a
		   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		   
Bug Report:
		我有發現使用find_paths，並不會將所有路徑一次找出來。
		還有輸入節點的數量不能超過10點，這樣vlist會出錯。