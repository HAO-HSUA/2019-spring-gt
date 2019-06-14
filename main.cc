 /* 
    Your main program goes here
*/

#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <queue>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"


using namespace std;

// create NetworkManager first
NetworkManager *nm = new NetworkManager();
map<string, vector<Edge *>> adv;
vector<Edge *> bfs_paths,aaa,plist;
vector<Vertex *> existed_vertices,odd_vertices;
queue<Edge *> bfs_search;
//vector<Vertex *>stake;
void bfs(string src);
int main(int argc, char** argv){

    /* start your program */
	nm->interpret("text.txt");
  
	//nm->print_all_v();
   /* nm->add_switch("a");
    nm->add_switch("d");
    nm->add_switch("b");
    nm->add_switch("c");
    // sub2
	
    nm->add_switch("e");
    nm->add_switch("h");
    nm->add_switch("g");
    nm->add_switch("f");

    nm->connect("a", "e");
    nm->connect("a", "h");
    nm->connect("b", "a");
    nm->connect("b", "c");
    nm->connect("b", "d");
    nm->connect("d", "b");
    nm->connect("d", "c");
    nm->connect("d", "h");

    nm->connect("e", "f");
    nm->connect("e", "h");
    nm->connect("g", "e");
    nm->connect("f", "g");
    nm->connect("h", "g");*/

    Edge *elist = nm->elist;
	//Edge *plist;
	Vertex **vlist=nm->vlist;
	string a;
    // build the edges belong to vertex 
	int initial_path_num=0;;
    while(elist!=NULL){
        //adv[elist->head->name].push_back(elist);
        initial_path_num+=1;
		elist=elist->next;
    }
	cout<<initial_path_num<<endl;
	elist=nm->elist;
	//////////////////////////////////////////////////////////
	/* while(elist!=NULL){
		for(int i=0;i<adv[elist->head->name].size();i++)	
			cout<<adv[elist->head->name].at(i)->head->name<<adv[elist->head->name].at(i)->tail->name<<";"<<endl;
		a=elist->head->name;
		elist=elist->next;
		if(a==elist->head->name)
			elist=elist->next;
		else
			elist=elist;
	 }
	*/
	
	///////////////////////////////////////////////////////////////////
	 int v_num=0;
	 while(vlist[v_num]!=NULL){
		 
			v_num++;
			
	 }
	 
	  cout<<"v:"<<v_num;
	  cout<<endl;
	  const int size=v_num;
	//////////////////
	/////////////////////////////////////////////////////////
	int degree[size][2];
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
	////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<size;i++){
			if(degree[i][2]==1){
				odd_vertices.push_back(nm->get_node(nm->vlist[i]->name));
			}
	
	}
	//cout<< odd_vertices[0]->name<<endl;
    //cout<< odd_vertices[1]->name<<endl;
	cout<<odd_vertices.size()<<endl;
    cout<<";"<<endl;
	//////////////////////////////////////////////////////////////////////////////
	elist=nm->elist;
	for (int i=0;i<initial_path_num;i++){
		nm->connect(elist->tail->name,elist->head->name);
		elist=elist->next;
	}
	  nm->print_all_e();
	/*elist=nm->elist;
	  int path_num=0;
	while(elist!=NULL){
       adv[elist->head->name].push_back(elist);
       path_num+=1;
	   elist=elist->next;
    }
	cout<<path_num<<endl;
	cout<<";"<<endl;
	/////////////////////////////////////////////////////////////////////////////
	elist=nm->elist;
	////////////////////////////////////////////////////////////////////////////////
	//cout<<";;;;"<<adv[elist->head->name].size()<<endl;
	count=0;
	 while(elist!=NULL && count!=v_num){
		for(int i=0;i<adv[elist->head->name].size();i++)	
			cout<<adv[elist->head->name].at(i)->head->name<<adv[elist->head->name].at(i)->tail->name<<";"<<endl;
		a=elist->head->name;
		elist=elist->next;
		if(a==elist->head->name)
			elist=elist->next;
		else
			elist=elist;
		while(elist->head->name==a){
			a=elist->head->name;
			elist=elist->next;
		}
		count+=1;	
	 }*/
	
		
	//////////////////////////////////////////////////////////////////////////////
	const int mini_path_size=odd_vertices.size();
	cout<<"::::"<<mini_path_size<<endl;
	int mini_path[mini_path_size][mini_path_size];
	Path *path;
	path=new Path();
	path->append(nm->elist);
	vector<vector <Edge*>> pa;
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
	/*for(int i=0;i<pa.size();i++){
		if(i==0||p_temp.size()>pa[i].size())
			p_temp=pa[i];
	}
	cout<<p_temp.size()<<endl;
	for(int i=0;i<p_temp.size();i++){
		cout<<p_temp[i]->head->name<<","<<p_temp[i]->tail->name<<endl;
	}
	path->debug();
	///////////////////////////////////////////////////////////////
	pa=path->find_paths("b","e");
	path->debug();*/
	int flag=0;
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
			while(1){
				if(vlist[var]->name==odd_vertices[i+1]->name)
					break;
				else
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
		
		/////////////////////////////////////////////////////////////////////////
		elist=nm->elist;
		int path_num=0;
		while(elist!=NULL){
		adv[elist->head->name].push_back(elist);
		path_num+=1;
		elist=elist->next;
		}
		cout<<path_num<<endl;
		cout<<";"<<endl;
		/////////////////////////////////////////////////////////////////////////////
		elist=nm->elist;
		////////////////////////////////////////////////////////////////////////////////
		//cout<<";;;;"<<adv[elist->head->name].size()<<endl;
		count=0;
		while(elist!=NULL && count!=v_num){
			for(int i=0;i<adv[elist->head->name].size();i++)	
				cout<<adv[elist->head->name].at(i)->head->name<<adv[elist->head->name].at(i)->tail->name<<";"<<endl;
			a=elist->head->name;
			elist=elist->next;
			/*if(a==elist->head->name)
				elist=elist->next;
			else
				elist=elist;*/
			while(elist->head->name==a){
				a=elist->head->name;
				elist=elist->next;
			}
			count+=1;	
		}
		///////////////////////////////////////////////////////////////////
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
		
		
		std::ofstream fout;
		fout.open ("shortpath.txt");
		for(int i=0;i<aaa.size();i++){
			fout << aaa.at(i)->head->name << "->" << aaa.at(i)->tail->name <<endl;
		}
		//fout << this->dotfile;
		fout.close();

		
		
		
		/*while(i<path_num/2){
			elist=elist->next;
			while(elist!=NULL){
				if(hvlist==elist->head->name)	
					plist.push_back(elist);
				elist=elist->next;
			
			}
			elist=nm->elist;
			//pa1=path2->find_paths((plist[1]->head->name),(plist[1]->tail->name));
			//pa1=path2->find_paths("b","e");
			//path2->debug();		
			int z=0;
			while(1){
				path2->append(nm->elist);
				pa1=path2->find_paths((plist[z]->head->name),(plist[z]->tail->name));
				if(pa1.size()>1)
					break;
				else
					z=z+1;	
			}	
			aaa.push_back(plist[z]);
			//cout << aaa.at(0)->head->name << "->" << aaa.at(0)->tail->name << endl;
			nm->disconnect((plist[z]->head->name),(plist[z]->tail->name));
			nm->disconnect((plist[z]->tail->name),(plist[z]->head->name));
			hvlist=plist[z]->tail->name;
			cout<<hvlist<<endl;
			elist=nm->elist;
			adv.clear();
			while(elist!=NULL){
				adv[elist->head->name].push_back(elist);
				elist=elist->next;
			}
			z=0;
			i=i+1;
		}*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//Path *path2;
	
	//vector <Edge*> p_temp;
	/////////////////////////////////////////////////////////////////
	/*int z=0;
	int j=0;
	int cc=0;
	string disconnect_node1,disconnect_node2;
	Edge *bfs_elist=NULL, *tmp=bfs_elist;
	while(z<(path_num/2)){
		existed_vertices.clear();
		bfs_paths.clear();
		if(z==0){
			existed_vertices.push_back(nm->get_node(nm->vlist[0]->name));
			bfs(nm->vlist[0]->name);
			while(!bfs_search.empty()){
				bfs(bfs_search.front()->tail->name);
				bfs_search.pop();
			}
		}
		if(z!=0){
			existed_vertices.push_back(nm->get_node(disconnect_node2));
			bfs(disconnect_node2);
			while(!bfs_search.empty()){
				bfs(bfs_search.front()->tail->name);
				bfs_search.pop();
			}
		}
		
		cout << "BFS: " << endl;
		for(int i=0;i<bfs_paths.size();i++){
			cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name << endl;
			if(tmp==NULL){
				bfs_elist = new Edge(bfs_paths.at(i));
				tmp = bfs_elist;
			} 
			else {
				tmp->next = new Edge(bfs_paths.at(i));
				tmp = tmp->next;
			}
		}
		if(z==0 || z==((path_num/2)-1)){
			disconnect_node1=bfs_paths.at(0)->head->name;
			disconnect_node2=bfs_paths.at(0)->tail->name;
			aaa.push_back(bfs_paths.at(0));
		}
		else{
			while(1){
				while(1){
					if(bfs_paths.at(cc)->tail->name==vlist[j]->name)
						break;
					else
						j=j+1;
				
				}
				if(degree[j][1]!=1){	
					path2=new Path();
					path->append(nm->elist);
					vector<vector <Edge*>> pa1;
					pa1=path->find_paths((bfs_paths.at(cc)->head->name),(bfs_paths.at(cc)->tail->name));
					if(pa1.size()==1){
						cc=cc+1;
						j=0;
					}
					else
						break;
				}	
				else{ 
					cc=cc+1;
					j=0;
				}
			}
			disconnect_node1=bfs_paths.at(cc)->head->name;
			disconnect_node2=bfs_paths.at(cc)->tail->name;
			aaa.push_back(bfs_paths.at(cc));
		}
		j=0;
		cc=0;
		nm->disconnect(disconnect_node1,disconnect_node2);
		nm->disconnect(disconnect_node2,disconnect_node1);
		while(1){
			if(disconnect_node1==vlist[j]->name)
				break;
			j=j+1;
		}
		degree[j][1]=degree[j][1]-1;
		j=0;
		while(1){
			if(disconnect_node2==vlist[j]->name)
				break;
			j=j+1;
		}
		degree[j][1]=degree[j][1]-1;
		j=0;
		for(int i=0;i<size;i++){
			cout<<degree[i][1]<<";"<<degree[i][2]<<endl;
	
		}
		elist=nm->elist;
		adv.clear();
		while(elist!=NULL){
			adv[elist->head->name].push_back(elist);
			elist=elist->next;
		}
		z=z+1;
	}
	cout<<aaa.size()<<"uauuuu"<<endl;
	for(int i=0;i<aaa.size();i++){
			cout << aaa.at(i)->head->name << "->" << aaa.at(i)->tail->name << endl;
	
	}*/
	
	
	
	
	
	
	
	
	
	
	
	
	/////////////////////////////////////////////////////////////////////////
	/*int z=0;
	int j=0;
	int cc=0;
	string disconnect_node1,disconnect_node2;
	Edge *bfs_elist=NULL, *tmp=bfs_elist;
	while(z<(path_num/2)){
		existed_vertices.clear();
		bfs_paths.clear();
		if(z=0){
			existed_vertices.push_back(nm->get_node(nm->vlist[z]->name));
			bfs(nm->vlist[z]->name);
		}	
		else{
			existed_vertices.push_back(nm->get_node(disconnect_node2));
			bfs(disconnect_node2);
		}	
	
		while(!bfs_search.empty()){
			bfs(bfs_search.front()->tail->name);
			bfs_search.pop();
		}

		if(z==0){
			bfs_elist=NULL, *tmp=bfs_elist;
		}
		else{
			bfs_elist=tmp, *tmp=bfs_elist;
		}	
		cout << "BFS: " << endl;
		for(int i=0;i<bfs_paths.size();i++){
			cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name << endl;
			if(tmp==NULL){
				bfs_elist = new Edge(bfs_paths.at(i));
				tmp = bfs_elist;
			} 
			else{
				tmp->next = new Edge(bfs_paths.at(i));	
				tmp = tmp->next;
			}
		}
		if(z==0 || z==((path_num/2)-1)){
			disconnect_node1=bfs_paths.at(0)->head->name;
			disconnect_node2=bfs_paths.at(0)->tail->name;
			aaa.push_back(bfs_paths.at(0));
		}
		else{
			while(1){
				while(1){
					if(bfs_paths.at(cc)->tail->name==vlist[j]->name)
						break;
					else
						j=j+1;
				
				}
				if(degree[j][1]!=1)	
					break;
				else{ 
					cc=cc+1;
					j=0;
				}
			}
			disconnect_node1=bfs_paths.at(cc)->head->name;
			disconnect_node2=bfs_paths.at(cc)->tail->name;
			aaa.push_back(bfs_paths.at(cc));
		}
		j=0;
		cc=0;
		nm->disconnect(disconnect_node1,disconnect_node2);
		nm->disconnect(disconnect_node2,disconnect_node1);
		while(1){
			if(disconnect_node1==vlist[j]->name)
				break;
			j=j+1;
		}
		degree[j][1]=degree[j][1]-1;
		j=0;
		while(1){
			if(disconnect_node2==vlist[j]->name)
				break;
			j=j+1;
		}
		degree[j][1]=degree[j][1]-1;
		j=0;
		elist=nm->elist;
		adv.clear();
		while(elist!=NULL){
			adv[elist->head->name].push_back(elist);
			elist=elist->next;
		}
		z=z+1;
	}*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	////////////////////////////////////////////////////////////////
	
    // BFS
    //existed_vertices.push_back(nm->get_node("b"));
	
	/*existed_vertices.push_back(nm->get_node(nm->vlist[0]->name));
	
	//cout<<existed_vertices.begin()<<endl;
    //bfs(nm->vlist[0]->name);
	bfs(nm->vlist[0]->name);
    while(!bfs_search.empty()){
        bfs(bfs_search.front()->tail->name);
        bfs_search.pop();
    }

    Edge *bfs_elist=NULL, *tmp=bfs_elist;

    cout << "BFS: " << endl;
    for(int i=0;i<bfs_paths.size();i++){
        cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name << endl;
        if(tmp==NULL){
            bfs_elist = new Edge(bfs_paths.at(i));
            tmp = bfs_elist;
        } else {
            tmp->next = new Edge(bfs_paths.at(i));
            tmp = tmp->next;
        }
    }
	nm->disconnect("a","b");
	nm->disconnect("b","a");
	adv.clear();
	nm->print_all_e();
	elist=nm->elist;
	while(elist!=NULL){
		adv[elist->head->name].push_back(elist);
	
	elist=elist->next;
	}
	 cout<<"yaya"<<adv["b"].size()<<endl;
	//existed_vertices.pop();
	existed_vertices.clear();
	bfs_paths.clear();
	while(!bfs_search.empty()){
        bfs_search.pop();
    }
	existed_vertices.push_back(nm->get_node(nm->vlist[1]->name));
	bfs(nm->vlist[1]->name);
    while(!bfs_search.empty()){
        bfs(bfs_search.front()->tail->name);
        bfs_search.pop();
    }

       bfs_elist=tmp, *tmp=bfs_elist;

    cout << "BFS: " << endl;
    for(int i=0;i<bfs_paths.size();i++){
        cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name << endl;
        if(tmp==NULL){
            bfs_elist = new Edge(bfs_paths.at(i));
            tmp = bfs_elist;
        } else {
            tmp->next = new Edge(bfs_paths.at(i));
            tmp = tmp->next;
        }
    }
 /////////////////////////////////////////////////////////////
	existed_vertices.clear();
	bfs_paths.clear();
	existed_vertices.push_back(nm->get_node(nm->vlist[2]->name));
	bfs(nm->vlist[2]->name);
    while(!bfs_search.empty()){
        bfs(bfs_search.front()->tail->name);
        bfs_search.pop();
    }

       bfs_elist=tmp, *tmp=bfs_elist;

    cout << "BFS: " << endl;
    for(int i=0;i<bfs_paths.size();i++){
        cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name << endl;
        if(tmp==NULL){
            bfs_elist = new Edge(bfs_paths.at(i));
            tmp = bfs_elist;
        } else {
            tmp->next = new Edge(bfs_paths.at(i));
            tmp = tmp->next;
        }
    }*/
 
 
 
   /* Gplot *gp = new Gplot();
    gp->gp_add(bfs_elist);
    gp->gp_dump(true);
    gp->gp_export("bfs/bfs");*/  
	

    return 0;
}
void bfs(string src){
   
	for(int i=0;i<adv[src].size();i++){
        // cout << adv[src].at(i)->head->name << "=>" << adv[src].at(i)->tail->name << endl;
        // check the tail is in the existed_vertices or not
		
        if(find(bfs_paths.begin(), bfs_paths.end(), adv[src].at(i))==bfs_paths.end()){
            // if tail is not existed, then push into existed vertices
            if(find(existed_vertices.begin(), existed_vertices.end(), adv[src].at(i)->tail)==existed_vertices.end()){
                // and push this edge into bfs result
                bfs_paths.push_back(adv[src].at(i));
                // not existed, then push into existed
                existed_vertices.push_back(adv[src].at(i)->tail);
                // push
				
				for(int i=0;i<bfs_paths.size();i++){
					cout << bfs_paths.at(i)->head->name << "->" << bfs_paths.at(i)->tail->name<<" | " ;
				}
				cout<<endl;
				
                bfs_search.push(adv[src].at(i));
				cout<<bfs_search.front()->head->name<<bfs_search.front()->tail->name<<";"<<endl;
            }
        }
    }
}
