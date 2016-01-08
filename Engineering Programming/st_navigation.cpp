#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

//constant variable for infinitive
const float inf = 1<<31;

//direction arrays
const int X[4] = {1,-1,0,0};
const int Y[4] = {0,0,1,-1};

//class for Grid cells
struct Block { bool u; float w; };

//Elements of heap
struct heapElem { int v; float g; };

//Modified version of heap data structure for this problem
class MinHeap {
    private:
        heapElem *heapArray;	//array to store heap
        int *mapV;		//array to store current location of some vertex
        int size;		//size of the heap
    public:
        //Constructor
        MinHeap(int hs){
            size = 0;					//initially our heap is empty
            heapArray = new heapElem[hs+1];		//allocating memory for heap
            mapV = new int[hs+1];			//allocating memory for location array
            for(int i=0; i<=hs; ++i) mapV[i] = 0;	//initializing location array
        };
        //Destructor, deleting all dynamic arrays
        ~MinHeap(){ delete [] heapArray; delete [] mapV; };
        //Put element to the heap
        void Push(const heapElem &e){
            size++;			//increasing the size of the heap
            heapArray[size].v = e.v;	//saving vertex value
            heapArray[size].g = e.g;	//saving time value
            mapV[e.v] = size;		//saving its location in heap
            Up(size);			//trying to up that node
        };
        //Get the first element from heap
        const heapElem &Top(){ return heapArray[1]; };
        //Take out the first element
        void Pop(){
            heapArray[1].v = heapArray[size].v;	//putting vertex of the last element to the top of the heap
            heapArray[1].g = heapArray[size].g; //putting time of the last element to the top of the heap
            mapV[heapArray[1].v] = 1;		//changing vertex's location in heap
            size--;				//decreasing the size of the heap
            Down(1);				//trying to down that node
        };
        //Modify specific heap element
        bool Modify(const heapElem &e){
            if(e.g < heapArray[mapV[e.v]].g){	//check if new time is less than previous
                heapArray[mapV[e.v]].g = e.g;	//assigning new time value
                Up(mapV[e.v]);			//trying to up that node
                return true;			//indicates that node is updated
            }   return false;			//indicates that node is not updated
        };
        //Check heap for emptiness
        bool IsEmpty(){ if(!this->size) return true; return false; };
        //Swap two elememnts of the heap
        void Swap(int i1, int i2){
            int vv = heapArray[i1].v; heapArray[i1].v = heapArray[i2].v; heapArray[i2].v = vv;	//swap vertesses
          float pp = heapArray[i1].g; heapArray[i1].g = heapArray[i2].g; heapArray[i2].g = pp;	//swap time values
          
          mapV[heapArray[i1].v] = i1;	//assign new location
          mapV[heapArray[i2].v] = i2;	//assign new location
        };
        //Up some element in heap
        void Up(int i1){	//up node while current node is greater than 1 and less than parent node
            while(i1>1 && heapArray[i1].g<heapArray[i1/2].g) { Swap(i1, i1/2); i1 /= 2; }
        };
        //Down some element in heap
        void Down(int i1){
            int i2 = i1;								//variable to store min time value child
            if(i1*2<=size && heapArray[i1*2].g < heapArray[i2].g) i2 = i1*2;		//checking left child
            if(i1*2+1<=size && heapArray[i1*2+1].g < heapArray[i2].g) i2 = i1*2+1;	//checking right child
            if(i1!=i2) { Swap(i1,i2); Down(i2); }		//if one of the children less than current node the swap
        };
        //Check whether element in heap or not
        bool IsInHeap(const heapElem &e){ if(mapV[e.v] == 0) return false; return true; };
};

//function definitions
void disp_input(Block** Grid, const string &st, const int &n, const int &m, const int &sx, const int &sy, const int &fx, const int &fy);
void find_path(Block** Grid, const int &n, const int &m, const int &sx, const int &sy, const int &fx, const int &fy);
bool check_input(const string &, const int &, const int &, const int &, const int &, const int &, const int &, bool, bool);
int get_v(const int &, const int &, const int &);
void path(int*, int, const int &, const int &);
void get_XY(const int &, const int &, int &, int &);

int main(){
    //initialize the input file
    ifstream in; in.open("navigation_in.txt");
    //declare variables
    long long c_time;					//for running time
    bool err;						//error indicator
    int Grids = 0, t, i, j, k, n, m, sx, sy, fx, fy;	//variables for input and operations
    Block ** Grid;					//Grid 2D array
    string st, s = "";					//string variables for input data
    struct timeval start; struct timeval end;		//timers
    //check input file
    if (in.good()) {
        //Get the number of Grids
        in>>Grids;
        //Read and calculate min time distance for each Grid
        for(t=0; t<Grids; t++){
	    //initialize error indicator
            err = false; 
            //get input from file
            while(st[0]!='G') in>>st;
            in>>n>>m>>sx>>sy>>fx>>fy;
            //initialize Grid
            Grid = new Block*[n+2];
            for(i=0; i<=n+1; ++i){ Grid[i] = new Block[m+2]; }
            //get Grid values
            k = 0; i = j = 1;
            while(in>>s){
                if(s[0] == 'G') break;		//break if Grid finishes
                if(i>n) {err = true; break;}	//number of items is more than supposed, error detected, break 
                Grid[i][j].w = atof(s.c_str());	//convert string to float
                Grid[i][j].u = false;		//initialize Grid cell as not used
                k++; j++;			//increment k (number of items) and j (Grid cell position)
                if(j>m) { i++; j = 1; }		//in case j>m increment i to move to the next row and assign 1 to j
            }
            //check input
            if(k!=n*m) err = true;		//check number of items
            check_input(st,n,m,sx,sy,fx,fy,err,true);//check and output errors
	    if(!err)
            for(i=1; i<=n; ++i)			//check each Grid cell for error
                for(j=1; j<=m; ++j)
                    if(Grid[i][j].w>1 || Grid[i][j].w<0.1) { //indicate error
                        printf("INVALID_INPUT(invalid_cost_value):%s(%d,%d)\n", st.c_str(), i, j);
                        err = true;
                    }
	    for(i=0; i<=n+1; i++) { delete [] Grid[i];}
	    delete [] Grid;
	    if(s[0]=='G') st = s; else st = "";
        }
    } else cout<<"Can't_open_the_input_file!\n";
    in.close();
    ifstream iin;
    iin.open("navigation_in.txt");
    st = "";
    if (iin.good()) {
        //Get the number of Grids
        iin>>Grids;
        //Read and calculate min time distance for each Grid
        for(t=0; t<Grids; t++){
            //initiate the starting time
            gettimeofday(&start,NULL);
	    //initialize error indicator
            err = false; 
            //get input from file
            while(st[0]!='G') iin>>st;
            iin>>n>>m>>sx>>sy>>fx>>fy;
            //initialize Grid
            Grid = new Block*[n+2];
            for(i=0; i<=n+1; ++i){ Grid[i] = new Block[m+2]; }
            //get Grid values
            k = 0; i = j = 1;
            while(iin>>s){
                if(s[0] == 'G') break;		//break if Grid finishes
                if(i>n) {err = true; break;}	//number of items is more than supposed, error detected, break 
                Grid[i][j].w = atof(s.c_str());	//convert string to float
                Grid[i][j].u = false;		//initialize Grid cell as not used
                k++; j++;			//increment k (number of items) and j (Grid cell position)
                if(j>m) { i++; j = 1; }		//in case j>m increment i to move to the next row and assign 1 to j
            }
            //check input
            if(k!=n*m) err = true;		//check number of items
            err = check_input(st,n,m,sx,sy,fx,fy,err,false);//check and output errors
	    if(!err)
            for(i=1; i<=n; ++i)			//check each Grid cell for error
                for(j=1; j<=m; ++j)
                    if(Grid[i][j].w>1 || Grid[i][j].w<0.1) { //indicate error
                        err = true;
                    }
            if(!err) {
                //display input data
                disp_input(Grid,st,n,m,sx,sy,fx,fy);  
                //calculate and display min time
                find_path(Grid,n,m,sx,sy,fx,fy);
		//delete dynamic memory
		for(i = 0; i<=n+1; i++) delete [] Grid[i];
		delete [] Grid;
                //display time
                gettimeofday(&end,NULL);                
                c_time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
                printf("Time_for_computation:%lldms\n\n", c_time);
            }
	    if(s[0]=='G') st = s; else st = "";
        }
    } else cout<<"Can't_open_the_input_file!\n";
    in.close();
}

void disp_input(Block** Grid, const string &st, const int &n, const int &m, const int &sx, const int &sy, const int &fx, const int &fy){
    printf("%s,%d,%d\n", st.c_str(), n, m);			//display input data
    printf("(%d,%d),(%d,%d)\n", sx,sy,fx,fy);
    for(int i=1; i<=n; i++){					//display Grid
        for(int j=1; j<=m; j++) printf("|%0.1f", Grid[i][j].w);
        printf("|\n");
    }
}

bool check_input(const string &st, const int &n, const int &m, const int &sx, const int &sy, const int &fx, const int &fy, bool b, bool f){
    //check grid size
    if(n>200 || m>200 || n<1 || m<1) { if(f) printf("INVALID_INPUT(invalid_grid_size):%s\n", st.c_str()); return true; }
    //check number of items
    if(b) { if(f) printf("INVALID_INPUT(invalid_number_items):%s\n", st.c_str()); return true; } else
    //check starting and ending points
    if (sx<1 || sx>n || sy<1 || sy>m || fx<1 || fx>n || fy<1 || fy>m) {
        if(f) printf("INVALID_INPUT(invalid_starting/ending_position):%s\n", st.c_str());
    } return false;
}

void find_path(Block** Grid, const int &n, const int &m, const int &sx, const int &sy, const int &fx, const int &fy){
    int vv = get_v(fx,fy,m), x=0, y=0;	//vertex for final point
     //heap elements
    heapElem e, i; 
    e.v = get_v(sx,sy,m);
    e.g = Grid[sx][sy].w;
	//creating a heap
    MinHeap *mheap = new MinHeap(n*m);
    mheap->Push(e); //pushing starting point to heap
	//array to save predcessors
    int *prev = new int[n*m];
    prev[e.v] = e.v;	//starting points predcessor will be itself
	//while heap is not empty do looking for path
    while(!mheap->IsEmpty()){
        i.v = (mheap->Top()).v; //take the top element from heap
        i.g = (mheap->Top()).g;
        mheap->Pop();	//pop the top element
        
        //cout<<i.v<<endl;
        if(i.v == vv){	//if already in a final positions then write time and exit
            path(prev, i.v, n, m);
            printf("Shortest_Time:%0.1f\n",i.g);
            return;
        }
         
        get_XY(i.v, m, x, y);	//getting coordinates of vertex
        Grid[x][y].u = true;	//marking Grid cell as used
        for(int j=0; j<4; j++)	//looking for neighbor cells
            if(x+X[j]>0 && x+X[j]<=n && y+Y[j]>0 && y+Y[j]<=m && !Grid[x+X[j]][y+Y[j]].u){
                e.g = i.g + Grid[x+X[j]][y+Y[j]].w;	//new time value
                e.v = get_v(x+X[j],y+Y[j],m);		//neighbor's vertex
                if(!mheap->IsInHeap(e)){		//if neighbor is new, we add it to heap
                    mheap->Push(e); 
                    prev[e.v] = i.v;			//saving predcessor for neighbor
                }else{
                    if(mheap->Modify(e)) prev[e.v] = i.v; //if neighbor's min time was updated then save new predcessor for it
                }    
            }
    }
}
//function that calculates vertex for some point
int get_v(const int &a, const int &b, const int &c){ return (a-1)*c+b; }
//function to get coordinates from a vertex
void get_XY(const int &v, const int &m, int &x, int &y) {
    if(v%m==0) {
        x = v/m;
        y = m;
    } else {
        x = v/m+1;
        y = v%m;
    }
}
//function to show a path
void path(int* prev, int vv, const int &n, const int &m){
    int* pp = new int[n*m]; //array to save the path
    int l = 0;
    do {	//get the path from prev array
        pp[l] = vv; l++;
        vv = prev[vv];
    } while(prev[vv] != vv);
    pp[l] = vv;
    int x=0, y=0;
    for(int i=l; i>0; --i) {	//write out the path
        get_XY(pp[i], m, x, y);
        printf("(%d,%d),", x, y);
    }
    get_XY(pp[0], m, x, y);
    printf("(%d,%d)\n", x, y);
}
