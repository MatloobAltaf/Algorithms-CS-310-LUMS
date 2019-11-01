#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;



//	This algorithm calculates the ratio p/l and on the basis of which it sorts the array of p and r
//	Expected time is calculated by keeping the product in reference
//	The time complexity of this algorithm is O(nlog(n))

class timeToRack{
	private:
		double *p;
		double*r;
		double*product;
		int *index;
		int size;
		string result;
	public:
		timeToRack(int s);
		void initRacks(vector<double>&values);
		void initProd(vector<double>&values);
		void products();
		void initIndeces();
		void print();
		void calProd();
		void refactoring();
		void expTime();
		~timeToRack();
};
timeToRack::timeToRack(int s){
	size = s;
	p = new double [size];
	r = new double [size];
	product = new double[size];
	index = new int[size];
}
void timeToRack::initRacks(vector<double>&values){
	for(int i=0;i<size;i++){
		r[i] = values[i];
	}
}
void timeToRack::initProd(vector<double>&values){
	for(int i=0;i<size;i++){
		p[i] = values[i];
	}
}
void timeToRack::products(){
	for(int i=0;i<size;i++){
		product[i] = 0;
	}
}
void timeToRack::initIndeces(){
	for(int i=0;i<size;i++){
		index[i] = i;
	}
}
void timeToRack::print()
{
	cout<<result<<endl;
}
void timeToRack::calProd()
{
	for(int i=0;i<size;i++)
	{
		product[i] = p[i]/r[i];
	}
	// printProduct();
	//sort(product,product+size,greater<double>());
	for(int i=0;i<size;i++)
	{
		double min = product[i];
		int ind = i;
		for(int j=i+1;j<size;j++)
		{
			// cout<<product[min]<<endl;
			// cout<<product[j]<<endl;
			if(min<product[j])
			{

				min = product[j];
				ind = j;
			}
		}
		//cout<<ind<<endl;

		double temp = product[ind];
		//cout<<temp<<endl;
		product[ind] = product[i];
		product[i] = temp;
	}
}
void timeToRack::refactoring(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(product[i]==p[j]/r[j]){
				result+=to_string(j+1)+" ";
				break;
			}
		}
	}
	result+="\n";
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(product[i]==p[j]/r[j]){
				swap(p[i],p[j]);
				swap(r[i],r[j]);
				break;
			}
		}
	}
}
void timeToRack::expTime()
{
	products();
	initIndeces();
	calProd();
	refactoring();
	double time = 0;
	double sudo = 0;
	for(int i=0;i<size;i++)
	{

			time+=p[i]*(r[i]+sudo);
			sudo+=r[i];
		}
		result+="Expected Time " +to_string(time);

	}

timeToRack::~timeToRack()
{
	delete []p;
	delete []r;
	delete []product;
	delete []index;
	p = NULL;
	r = NULL;
	product = NULL;
	index = NULL;
}

int getSize(vector<vector<double>>&result)
{
	return result[0][0];
}
void removeSize(vector<vector<double>>&result)
{
	result.erase(result.begin());
}
void parse(string fileName,vector<vector<double>>&values){
	ifstream infile;
	infile.open(fileName);
	string x;
	string s;
	while(getline(infile,x)){
			vector<string> wordVector;
			std::stringstream stringStream(x);
			std::string line;
			while(std::getline(stringStream, line)){
    			std::size_t prev = 0, pos;
    			while ((pos = line.find_first_of(" ", prev)) != std::string::npos){
        			if (pos > prev){
						s = line.substr(prev, pos-prev);
					}
					if(s!="p"&&s!="n"&&s!="L"){
							wordVector.push_back(s);
					}
       				 prev = pos+1;
    			}
    			if (prev < line.length())
        		wordVector.push_back(line.substr(prev, std::string::npos));
			}
			vector<double> lines;
			for(int i=0;i<wordVector.size();i++){
				stringstream s(wordVector[i]);
				double x;
				s>>x;
				lines.push_back(x);
			}
			values.push_back(lines);
		}
}
int main(int argc, char** argv)
{
	ifstream infile;
	string fileName = argv[1];
	vector<vector<double>> result;
	parse(fileName,result);
	const int size = getSize(result);
	removeSize(result);

	timeToRack t(size);
	t.initRacks(result[0]);
	t.initProd(result[1]);
	t.expTime();
	t.print();

	return 0;
}