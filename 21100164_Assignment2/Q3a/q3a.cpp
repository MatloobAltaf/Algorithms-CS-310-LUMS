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
  vector<pair<int,pair<int,int>>> edges; //<weight,<first node,second node>>
public:
  Data();
  Data(int vertices);
  Data(vector<vector<int>>&values);
  void print();
  pair<int,int> dedge;
  string mst();
  bool isConnected();
  void DFS(int v,vector<bool>&visited);
  void addEdge(int u,int v,int w);

};
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
          //cout<<"Entered here"<<endl;
        }
      }
    }
    sort(edges.begin(),edges.end());
}
void Data::print()
{
  for(int i=0;i<v;i++)
  {
    cout<<i<<":";
    for(auto it = adj[i].begin();it!=adj[i].end();it++)
    {
      cout<<*it<<" ";
    }
    cout<<endl;
  }
  cout<<"Edge to remove:"<<dedge.first<<","<<dedge.second<<endl;
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
      //cout<<"("<<x<<","<<y<<")"<<endl;
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
  //cout<<"Total cost is:"<<cost<<endl;
  adj[dedge.first].remove(dedge.second);
  adj[dedge.second].remove(dedge.first);
  //now need to subtract the cost
  int d,e,f;
  for(int i=0;i<edges.size();i++)
  {
    int x = edges[i].second.first;
    int y = edges[i].second.second;
    if(x==dedge.first&&y==dedge.second)
    {
      d = dedge.first;
      e = dedge.second;
      f = edges[i].first;
      string p1 = "(";
      result1+="Removed Edge: "+p1+to_string(d)+","+to_string(e)+")\n";

      cost = cost - edges[i].first;
      break;
    }
  }
  edges.clear();
  for(int i=0;i<a.size();i++)
  {
    if(d==a[i]&&e==b[i])
    {

    }
    else
    edges.push_back({we[i],{a[i],b[i]}});
  }
  //cout<<edges.size()<<endl;

  sort(unused_edges.begin(),unused_edges.end());
  bool conn = isConnected();
  if(conn)
  {
    bool search = false;
    for(int i=0;i<edges.size();i++)
    {
      if(edges[i].second.first==dedge.first&&edges[i].second.second==dedge.second)
      {
        search = true;
      }
    }
    cost = 0;
    if(!search)
    {
      for(int i=0;i<edges.size();i++)
      {
        result1+="("+to_string(edges[i].second.first)+","+to_string(edges[i].second.second)+") ";
        cost+=edges[i].first;


      }
    }
    result1+="\n";
    result1+="SUM MST1: "+to_string(cost);
    return result1;
  }

  for(int i=0;i<unused_edges.size();i++)
  {
    int x = unused_edges[i].second.first;
    int y = unused_edges[i].second.second;
    int z = unused_edges[i].first;
    adj[x].push_back(y);
    adj[y].push_back(x);
    conn = isConnected();
    if(conn)
    {
      edges.push_back({z,{x,y}});
      break;
    }
    else
    {
      adj[x].remove(y);
      adj[y].remove(x);
    }
  }
  if(!conn)
  {
    result1 +="T2 cannot be constructed\n";
    return result1;
  }
  cost = 0;
  result1+="MST2: ";
  for(int i=0;i<edges.size();i++)
  {
    result1+="("+to_string(edges[i].second.first)+","+to_string(edges[i].second.second)+") ";
    cost+=edges[i].first;
    //cout<<edges[i].second.first<<","<<edges[i].second.second<<endl;
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
  while ((pos = last_line.find_first_of("(,)", prev)) != std::string::npos)
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