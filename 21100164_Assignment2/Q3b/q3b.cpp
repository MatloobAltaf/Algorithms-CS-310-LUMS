#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <utility>
#include <list>
#include <sstream>
#include <algorithm>
using namespace std;
//I'm making an mst actually so the time complexity of my algorithm is O((n+e)log(n))
//where e are the edges
void parse(string fileName,vector<vector<int>>&values);
string last_line;
class Data
{
private:
  int v;
  list<int>*adj;
  vector<pair<int,pair<int,int>>> edges; 
public:
  Data();
  Data(int vertices);
  Data(vector<vector<int>>&values);
  pair<int,int> dedge;
  pair<int,pair<int,int>> added;
  string mst();
  bool isConnected();
  void DFS(int v,vector<bool>&visited);
  void addEdge(int u,int v,int w);
	bool CycleDFS(int u,vector<bool>&visited,vector<int>&parent,int &a,int &b);
	void printCycle(int u,int v,vector<int>&parent);
};
void Data::printCycle(int u,int v,vector<int>&parent)
{
	while(u!=v)
	{
		//cout<<u<<" ";
		u = parent[u];
	}
}
bool Data::CycleDFS(int u,vector<bool>&visited,vector<int>&parent,int &a,int &b)
{
	visited[u] = true;
	for(auto it = adj[u].begin();it!=adj[u].end();it++)
	{
		if(!visited[*it])
		{
			parent[u] = *it;
			CycleDFS(*it,visited,parent,a,b);

		}
		if(visited[*it]&&parent[*it]!=u)
		{
			a = *it;
			b = u;
			// printCycle(*it,u,parent);
			return true;
		}
	}
	return false;


}
Data::Data()
{
  v = 0;
}
Data::Data(int vertices)
{
  v = vertices;
  adj = new list<int>[v];
}
void Data::addEdge(int u,int v,int w)
{
  adj[u].push_back(v);
  adj[v].push_back(u);
  edges.push_back({w,{u,v}});
}
Data::Data(vector<vector<int>>&values)
{
  v = values[0][0];
  values.erase(values.begin());
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<values.size()-1;j++)
    {
      values[j].erase(values[j].begin());

    }
  }

  adj = new list<int>[v];
  vector<vector<int>> w;
  vector<vector<int>> neighbours;
  for(int i=0;i<values.size();i++)
  {
    vector<int> w1;
    for(int j=0;j<values[i].size();j+=2)
    {

      w1.push_back(values[i][j]);
    }
    w.push_back(w1);
  }

  for(int i=0;i<values.size();i++)
  {
    vector<int> w1;
    for(int j=1;j<values[i].size();j+=2)
    {
      w1.push_back(values[i][j]);
    }
    neighbours.push_back(w1);
  }

  bool visited[v][v];
  for(int i=0;i<v;i++)
  {
    for(int j=0;j<v;j++)
    {
      visited[i][j] = false;
    }
  }

    for(int j=0;j<neighbours.size();j++)
    {

      for(int k=0;k<neighbours[j].size();k++)
      {

        adj[j].push_back(w[j][k]);
        if(!visited[j][w[j][k]]&&!visited[w[j][k]][j])
        {
          edges.push_back({neighbours[j][k],{j,w[j][k]}});
          visited[j][w[j][k]] = true;
          visited[w[j][k]][j] = true;
        }
      }
    }
    sort(edges.begin(),edges.end());
}

void Data::DFS(int v,vector<bool>&visited)
{
  visited[v] = true;
  for(auto it = adj[v].begin();it!=adj[v].end();it++)
  {
    if(!visited[*it])
    {
      DFS(*it,visited);
    }
  }
}
bool Data::isConnected()
{
  vector<bool> visited(v,false);
  DFS(0,visited);
  for(int i=0;i<v;i++)
  {
    if(visited[i]==false)
    {
      return false;
    }
  }
  return true;
}
string Data::mst()
{
  string result1 = "MST1:";
  int cost = 0;
  int size = 0;
  vector<int> a;
  vector<int> b;
  vector<int> we;
  vector<pair<int,pair<int,int>>> unused_edges;
  for(int i=edges.size()-1;i>=0;i--)
  {
    int x = edges[i].second.first;
    int y = edges[i].second.second;
    adj[x].remove(y);
    adj[y].remove(x);
    bool result = isConnected();
    string p1 = "(";
    string p2 = ")";

    if(!result)
    {
      adj[x].push_back(y);
      adj[y].push_back(x);
      result1+=" "+p1+to_string(x)+","+to_string(y)+p2;
      cost+=edges[i].first;
      size++;
      a.push_back(x);
      b.push_back(y);
      we.push_back(edges[i].first);
    }
    else
    {
      adj[x].remove(y);
      adj[y].remove(x);
      unused_edges.push_back({edges[i].first,{x,y}});
    }
  }
  result1+="\n";
  result1+="SUM MST1: "+to_string(cost);
  result1+="\n";
	result1+="Added edge: "+to_string(added.second.first)+" "+to_string(added.second.second)+" "+to_string(added.first)+"\n";

  edges.clear();
  for(int i=0;i<a.size();i++)
  {

    edges.push_back({we[i],{a[i],b[i]}});
  }
	edges.push_back(added);
	adj[dedge.first].push_back(dedge.second);
	adj[dedge.second].push_back(dedge.first);
	vector<bool> visited(v,false);
	vector<int> parent(v);
	int aa;
	int bb;
	CycleDFS(0,visited,parent,aa,bb);
	vector<int> nn;
	nn.push_back(bb);
	while(aa!=bb)
	{
		nn.push_back(aa);
		aa = parent[aa];
	}
	nn.push_back(bb);
	vector<pair<int,pair<int,int>>> candidates;
	for(int i=0;i<nn.size();i+=1)
	{
		for(int j = 0;j<edges.size();j++)
		{
			int x = edges[j].second.first;
			int y = edges[j].second.second;
			if((x==nn[i]&&y==nn[i+1])||(y==nn[i]&&x==nn[i+1]))
			{
				candidates.push_back({edges[j].first,{x,y}});
			}
		}
	}
	candidates.push_back({added.first,{dedge.first,dedge.second}});

	sort(candidates.begin(),candidates.end());

	cost = 0;
	result1+="MST2: ";
	for(int i=0;i<edges.size();i++)
	{
		int aaa = candidates[candidates.size()-1].second.first;
		int bbb = candidates[candidates.size()-1].second.second;
		int x = edges[i].second.first;
		int y = edges[i].second.second;

		if((x==aaa&&y==bbb)||(x==bbb&&y==aaa))
		{

		}
		else
		{

			string p1 = "(";
			string p2 = ")";
			result1+=p1+to_string(x)+","+to_string(y)+p2+" ";
			cost+=edges[i].first;
		}
	}
	result1+="\n";
	result1+="SUM MST1: "+to_string(cost);
	return result1;

}

int main(int argc, char** argv)
{

  vector<int> cols;
  vector<int> weights;
  pair <int,int> deleteEdge;
  vector<vector<int>> values;
  parse(argv[1],values);
  Data g(values);
  ifstream infile;
  string s;
  vector<int> de;
  std::size_t prev = 0, pos;
  while ((pos = last_line.find_first_of("(,) ", prev)) != std::string::npos)
  {
      if (pos > prev)
          s = last_line.substr(prev, pos-prev);
          if(s!=" "&&s!="("&&s!=")")
          {
            stringstream ss(s);
            int x;
            ss>>x;
            de.push_back(x);

          }

      prev = pos+1;
  }

  g.dedge.first = de[1];
  g.dedge.second = de[2];
	g.added = {de[de.size()-1],{de[1],de[2]}};

  cout<<g.mst();
    return 0;
}


void parse(string fileName,vector<vector<int>>&values){
	ifstream infile;
	infile.open(fileName);
	string x;
	string s;
	while(getline(infile,x)){
		vector<string> wordVector;
		std::stringstream stringStream(x);
    std::string line;
    while(std::getline(stringStream, line)){
	    last_line = line;
      std::size_t prev = 0, pos;
      while ((pos = line.find_first_of(" ;:", prev)) != std::string::npos){
        if (pos > prev){
						s = line.substr(prev, pos-prev);
        }
				if(s!="n"&&s!="("&&s!=")"){
							wordVector.push_back(s);
				}
        prev = pos+1;
      }
      if(prev < line.length()){
      wordVector.push_back(line.substr(prev, std::string::npos));
      }
    }
		vector<int> lines;
	  for(int i=0;i<wordVector.size();i++){
			if(wordVector[i].find_first_not_of("0123456789") == std::string::npos)	{
			  stringstream s(wordVector[i]);
			  int x;
			  s>>x;
			  lines.push_back(x);
			}
		}
		values.push_back(lines);
	}
}