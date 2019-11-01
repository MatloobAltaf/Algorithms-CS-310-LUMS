#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//Each door is taken to open all the associated rooms
//so the time complexity is O(klog(n))

struct door
{
	int number; // store the number of unique doors it can
    int name;
    bool isLocked;
	door(){
		number = 0;
        name = 0;
		isLocked = false;
	}
	door(int n, int nm, bool b){
		number = n;
        name =nm;
	//	isLocked = b;
	}
};

struct room{
	int left;
	int right;
	bool isOpen;
	room(){
		isOpen = false;
		left= 0;
		right= 0;
	}
	room(int i, int j, bool b2){
		isOpen = b2;
		left= i;
		right= j;
	}
};

vector<int> sameDoorLabel;

class Rooms
{
private:
	int n;
    int k;
	int openRooms;
    vector<int> doorsToOpen;
    struct room* rooms;
	struct door* doors;
    
public:
	Rooms();
	Rooms(struct room d[], struct door dr[], int s, int j);
	~Rooms();
	void print();
	void open();
    void remove(std::vector<int> &v);
    int addHelper();
    int find(int j);
    static bool sortCondition(const struct door d1, const struct door d2 );
    void sorting();
    static bool sortCondition2(const int d1, const int d2 );
    void sorting2();
};
Rooms::Rooms(){
	n = 0;
	openRooms = 0;
}
Rooms::Rooms(struct room d[], struct door dr[], int s, int j)
{
	n = s;
    k = j;
	rooms = d;
	doors = dr;
    
}

Rooms::~Rooms()
{
}
void Rooms::open(){
	sorting();
    while(addHelper() > 0){
            int var = 0;
            if(sameDoorLabel.size()>0){
                var = find(sameDoorLabel[0]);
                sameDoorLabel.erase(sameDoorLabel.begin());
            }
            openRooms += doors[var].number;
            doors[var].number = 0;
            doorsToOpen.push_back(doors[var].name);
            if(doors[var].name >= k){
                doors[find(doors[var].name-k)].isLocked = true;
                doors[find(doors[var].name-k)].number = 0;
            }
            else{
                doors[find(doors[var].name+k)].isLocked = true;
                doors[find(doors[var].name+k)].number = 0;
            }
            for(int j = 0; j < n; j++){
                if(rooms[j].left == doors[var].name){
                    rooms[j].isOpen = true;
                    //openRooms++;
                    if(doors[find(rooms[j].right)].number != 0){
                        doors[find(rooms[j].right)].number--;
                    }
                }
                else if(rooms[j].right == doors[var].name){
                    rooms[j].isOpen = true;
                    //openRooms++;
                    if(doors[find(rooms[j].left)].number != 0){
                        doors[find(rooms[j].left)].number--;
                    }
                }
            }
            sorting();
    }
}
int Rooms::find(int j){
    for(int i =0; i < 2*k; i++){
        if(doors[i].name == j){
            return i;
        }
    }
    return 0;
}
void Rooms::remove(std::vector<int> &v){
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}
    v.erase(end, v.end());
}
void Rooms::print(){
    remove(doorsToOpen);
    sorting2();
    //cout<<openRooms<<endl;
    for(int i = doorsToOpen.size(); i<n; i++){
        doorsToOpen.push_back(0);
    }
    if(openRooms == n){
        cout<<"Yes"<<endl;
        for(int i = 0; i <k; i++){
            if(doorsToOpen[i] >= 3){
                cout<<0<<endl;
            }
            else if(doorsToOpen[i] < 3 && doorsToOpen[i] >= 0){
                cout<<1<<endl;
            }
           // cout<<doorsToOpen[i]<<endl;
        }
    }
    else{
        cout<<"No"<<endl;
    }

    // for(int i =0; i < 2*k; i++){
    //     //cout<<rooms[i].left<<"\t"<<rooms[i].right<<endl;
    //     cout<<doors[i].name<<"\t"<<doors[i].number<<"\t"<<doors[i].isLocked<<endl;
    // }
}
int Rooms::addHelper(){
    int s = 0;
    for(int i = 0; i < 2*k; i++){
        if(!doors[i].isLocked){
            s += doors[i].number;
        }
    }
    return s;
}
bool Rooms::sortCondition(const struct door d1, const struct door d2 ){
    return (d2.number < d1.number);
}
bool Rooms::sortCondition2(const int d1, const int d2 ){
    return (d2 > d1);
}
void Rooms::sorting2(){
    sort(doorsToOpen.begin(), doorsToOpen.end(), sortCondition2);
}
void Rooms::sorting(){
    sort(doors, doors+2*k, sortCondition);
}
int main(int argc, char** argv)
{
	if(argc < 2){
		exit(1);
	}
	int iSize = 0;
	int iTypes = 0;
	ifstream inFile;
    //argv[1] = "test44.txt";
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
	struct door* dr = new door [2*iTypes];
    struct room* rm = new room [iSize];
	int loop = 0;
	while(!inFile.eof()){
		getline(inFile, line);
		if(line == ""){
			continue;
		}
		string first = line.substr(0,line.find(' '));
		string second = line.substr(first.size()+1, line.find('\0'));
		int i = 0;
        int f = 0;
        if(first.size() == 2){
            i  = stoi(first.substr(1,first.find('\0')));
        }
        else{
            i  = iTypes + stoi(first.substr(2,first.find('\0')));
        }
		if(second.size() == 2){
            f  = stoi(second.substr(1,second.find('\0')));
        }
        else{
            f  = iTypes + stoi(second.substr(2,second.find('\0')));
        }

        rm[loop].left = i;
        rm[loop].right = f;
        dr[i].name = i;
        dr[f].name = f;
        if(i == f){
            dr[i].number++;
            sameDoorLabel.push_back(i);
        }
        else{
            dr[i].number++;
            dr[f].number++;
        }

        loop++;
	}
	inFile.close();
    Rooms r(rm, dr, iSize, iTypes);
	r.open();
	r.print();
	return 0;
}