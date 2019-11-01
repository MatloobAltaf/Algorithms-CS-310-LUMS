#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct door
{
	int number;
	bool isOpen;
	int instances;
	int antiInstances;
	door(){
		number = 0;
		isOpen = false;
		instances = 0;
		antiInstances = 0;
	}
	door(int n, bool b){
		number = n;
		isOpen = b;
		instances = 0;
		antiInstances = 0;
	}
};

struct room{
	int left;
	int right;
	bool isOpen;
	bool isLeftAnti;
	bool isRightAnti;
	room(){
		isOpen = false;
		left= 0;
		right= 0;
		isLeftAnti = 0;
		isRightAnti = 0;
	}
	room(int i, bool b1, int j, bool b2){
		isOpen = false;
		left= i;
		right= j;
		isLeftAnti = b1;
		isRightAnti = b2;
	}
};
class Rooms
{
private:
	int n;
	int types;
	int openRooms;
	struct room* rooms;
	//struct door* doors;
	struct door* sortedDoors;
	pair<int, int>* output;
public:
	Rooms();
	Rooms(vector <struct room> d, vector<struct door> dr, int l, int s);
	~Rooms();
	void print();
	void open();
	int inRoom(struct door p);
	int usedDoor(int f);
	void sortDoors();
	void sortOutput();
	static bool sortOut(const pair<int, bool>& b1, const pair<int, bool>& b2){
		return(b1.first > b2.first);
	}
	static bool sort_condition(const struct door pair1,const struct door pair2){
		return((pair2.antiInstances-pair2.instances) > (pair1.antiInstances-pair2.instances));
	}

};
Rooms::Rooms(){
	n = 0;
	types = 0;
}
Rooms::Rooms(vector <struct room> d, vector<struct door> dr, int l, int s)
{
	n = s;
	types = l;
	openRooms = 0;
	rooms = new room [n];
	output = new pair<int, int> [types];
	//doors = new door[types];
	sortedDoors = new door[types];
	for(int i = 0; i < n; i++){
		rooms[i].isLeftAnti = d[i].isLeftAnti;
		rooms[i].isOpen = d[i].isOpen;
		rooms[i].isRightAnti = d[i].isRightAnti;
		rooms[i].left = d[i].left;
		rooms[i].right = d[i].right;
	}
	for(int i = 0; i < types; i++){
		sortedDoors[i].antiInstances = dr[i].antiInstances;
		sortedDoors[i].instances = dr[i].instances;
		sortedDoors[i].isOpen = dr[i].isOpen;
		sortedDoors[i].number = dr[i].number;
	}
}

Rooms::~Rooms()
{
}
void Rooms::open(){
	for(int i = 0; i< types; i++ ){
		int rNumber = this->inRoom(sortedDoors[i]);
		sortedDoors[i].isOpen = true;
		if(sortedDoors[i].instances >= sortedDoors[i].antiInstances && !rooms[rNumber].isOpen){
			//sortedDoors[i].instances = 0;
			//sortedDoors[i].isOpen = true;
			//sortedDoors[i].antiInstances = 0;
			output[i].first = sortedDoors[i].number;
			output[i].second =  1;
			if(rooms[rNumber].left == sortedDoors[i].number){
				rooms[rNumber].isOpen = true; openRooms++;
				if(!rooms[rNumber].isLeftAnti){
					for(int j = rNumber+1; j < n; j++){
						if(rooms[j].left == sortedDoors[i].number && !rooms[i].isLeftAnti){
							rooms[i].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].instances--;
						}
						else if(rooms[j].right == sortedDoors[i].number && !rooms[i].isRightAnti){
							rooms[j].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].instances--;
						}
					}
				}
			}
			if(rooms[rNumber].right == sortedDoors[i].number){
				rooms[rNumber].isOpen = true;  openRooms++;
				if(!rooms[rNumber].isRightAnti){ 
					for(int j = rNumber+1; j < n; j++){
						if(rooms[j].left == sortedDoors[i].number && !rooms[i].isLeftAnti){
							rooms[i].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].instances--;
						}
						else if(rooms[j].left == sortedDoors[i].number && !rooms[i].isRightAnti){
							rooms[j].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].instances--;
						}
					}
				}
			}
		}
		else if(sortedDoors[i].instances < sortedDoors[i].antiInstances && !rooms[rNumber].isOpen){
			//sortedDoors[i].instances = 0;
			//sortedDoors[i].isOpen = true;  openRooms++;
			//sortedDoors[i].antiInstances = 0;
			output[i].first = sortedDoors[i].number;
			output[i].second =  0;
			if(rooms[rNumber].left == sortedDoors[i].number){
				rooms[rNumber].isOpen = true;  openRooms++;
				if(rooms[rNumber].isLeftAnti){
					for(int j = rNumber+1; j < n; j++){
						if(rooms[j].left == sortedDoors[i].number && rooms[i].isLeftAnti){
							rooms[i].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].antiInstances--;
						}
						else if(rooms[j].left == sortedDoors[i].number && rooms[i].isRightAnti){
							rooms[j].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].antiInstances--;
						}
					}
				}
			}
			if(rooms[rNumber].right == sortedDoors[i].number){
				rooms[rNumber].isOpen = true;  openRooms++;
				if(rooms[rNumber].isRightAnti){
					for(int j = rNumber+1; j < n; j++){
						if(rooms[j].left == sortedDoors[i].number && rooms[i].isLeftAnti){
							rooms[i].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].antiInstances--;
						}
						else if(rooms[j].left == sortedDoors[i].number && rooms[i].isRightAnti){
							rooms[j].isOpen = true;  openRooms++;
							//sortedDoors[this->usedDoor(rooms[i].right)].antiInstances--;
							(sortedDoors+(this->usedDoor(rooms[i].right)))->antiInstances--;
						}
					}
				}
			}
		}
	}
}
int Rooms::inRoom(struct door p){
	for(int i = 0; i<n; i++){
		if(p.number == rooms[i].left || p.number == rooms[i].right)
			return i;
	}
	return 0;
}
void Rooms::print(){
//	cout<<openRooms<<endl;
// for(int j =0; j<types; j++)
// 	cout<<sortedDoors[j].number<<"\"<<sortedDoors[j].instances<<"\t"<<sortedDoors[j].antiInstances<<"\t"<<sortedDoors[j].isOpen<<endl;

	if(openRooms == n){
		cout<<"Yes"<<endl;
		for(int i = 0; i < types; i++){
    		//cout<<output[i].first<<"\t";
			cout<<output[i].second<<endl;
		}
	}
	else{
		cout<<"No"<<endl;
	}
}
bool ifExist(int j, vector <struct door> dr){
	for(auto i = 0; i < dr.size(); i++){
		if(j == dr[i].number){
			return true;
		}
	}
	return false;
}
int findDoor(int j, vector<struct door> dr){
	for(auto i = 0; i < dr.size(); i++){
		if(j == dr[i].number){
			return i;
		}
	}
	return -1;
}
int Rooms::usedDoor(int f){
	for(int i = 0; i < types; i++){
		if(sortedDoors[i].number == f){
			return i;
		}
	}
	return 0;
}
void Rooms::sortDoors(){
	sort(sortedDoors,sortedDoors+types, sort_condition);
}
void Rooms::sortOutput(){
	sort(output,output+types, sortOut);
}
int main(int argc, char** argv)
{
	if(argc < 2){
		exit(1);
	}
	int iSize = 0;
	int iTypes = 0;
	ifstream inFile;
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(1);
	}
	string line;
	getline(inFile,line);
	if(line[0] == 'n'){
		iSize = stoi(line.substr(2,line.find('\0')));
	}
	getline(inFile,line);
	if(line[0] == 'k'){
		iTypes = stoi(line.substr(2,line.find('\0')));
	}
	vector<struct room> ds;
	vector<struct door> dr;
	
	while(!inFile.eof()){
		getline(inFile, line);
		if(line == ""){
			continue;
		}
		string first = line.substr(0,line.find(' '));
		string second = line.substr(first.size()+1, line.find('\0'));
		int left = 0, right = 0;
		bool isLeftAnti, isRightAnti;
		if(first.size() == 2){
			left = stoi(first.substr(1, first.find('\0')));
			isLeftAnti = false;

		}
		else{
			left = stoi(first.substr(2, first.find('\0')));
			isLeftAnti = true;

		}
		if(second.size() == 2){
			right = stoi(second.substr(1, second.find('\0')));
			isRightAnti = false;

		}
		else{
			right = stoi(second.substr(2, second.find('\0')));
			isRightAnti = true;

		}
		if(!ifExist(left, dr)){
			struct door tempDoor(left, false);
			if(isLeftAnti){
				tempDoor.antiInstances++;
			}
			else{
				tempDoor.instances++;
			}
			dr.push_back(tempDoor);

		}
		else{
			if(isLeftAnti){
				dr[findDoor(left, dr)].antiInstances++;
			}
			else{
				dr[findDoor(left, dr)].instances++;
			}
		}

		if(!ifExist(right, dr)){
			struct door tempDoor(right, false);
			if(isRightAnti){
				tempDoor.antiInstances++;
			}
			else{
				tempDoor.instances++;
			}
			dr.push_back(tempDoor);
		}
		else{
			if(isRightAnti){
				dr[findDoor(right, dr)].antiInstances++;
			}
			else{
				dr[findDoor(right, dr)].instances++;
			}
		}
		struct room temp(left, isLeftAnti, right, isRightAnti);
		ds.push_back(temp);
		
	}
	inFile.close();
	Rooms r(ds, dr, iTypes, iSize);
	r.sortDoors();
	r.open();
	r.print();
	return 0;
}