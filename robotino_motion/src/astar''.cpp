// Astar.cpp
// http://en.wikipedia.org/wiki/A*
// Compiler: Dev-C++ 4.9.9.2
// FB - 201012256
#include "astar.h"

node::node()
{
	xPos = 0;
    yPos = 0;
    // total distance already travelled to reach the node
    level = 0;
    // priority=level+remaining distance estimate
    priority = 0;  // smaller: higher priority

	v_base[0] = v_base[1] = 0;
	v_aux[0] = v_aux[1] = 0;
	comando[0] = comando[1] = 0;
	res = 0;
	resx = 0;
	resy = 0;
}

const int dim = 17; //Dimensão do mapa

const int n=17; // horizontal size of the map
const int m=17; // vertical size size of the map
static int map[n*dim + m];
static int closed_nodes_map[n*dim + m]; // map of closed (tried-out) nodes
static int open_nodes_map[n*dim + m]; // map of open (not-yet-tried) nodes
static int dir_map[n*dim + m]; // map of directions
//const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};


// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
string pathFind( const int & xStart, const int & yStart, 
                 const int & xFinish, const int & yFinish )
{
    static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the node maps
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            closed_nodes_map[n*dim + m]=0;
            open_nodes_map[n*dim + m]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    cout << "Depois do n0=new!!!";
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[n*dim + m]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    cout << "Antes do while!!!";
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());
        cout << "Depois do n0 = new!!!";
        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[n*dim + m]=0;
        // mark it on the closed nodes map
        closed_nodes_map[n*dim + m]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        cout << "Antes do if!!!";
        if(x==xFinish && y==yFinish) 
        {
            // generate the path from finish to start
            // by following the directions
            string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[n*dim + m];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }
        cout << "Antes do for!!!";
        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || map[xdx*dim + ydy]==1
                || closed_nodes_map[xdx*dim + ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(), 
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx*dim + ydy]==0)
                {
                    open_nodes_map[xdx*dim + ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx*dim + ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx*dim + ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx*dim + ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx*dim + ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove the wanted node

                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0; // garbage collection
            }
        }
        cout << "Path found!!!";
        delete n0; // garbage collection

    }
    return ""; // no route found
}

queue<int> node::findpath(int* map, int xA, int yA, int xB, int yB)
{
	int movimentox = 0;
	int movimentoy = 0;	
	int movimentoxy1 = 0;
	int movimentoxy2 = 0;
	
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	
    srand(time(NULL));
    
    // create empty map
    for(int y=0;y<m;y++)
    {
        for(int x=0;x<n;x++) map[x*dim + y]=0;
    }

    // fillout the map matrix with a '+' pattern
    for(int x=n/8;x<n*7/8;x++)
    {
        map[x*dim + m/2]=1;
    }
    for(int y=m/8;y<m*7/8;y++)
    {
        map[(n/2)*dim + y]=1;
    }
    
    cout << "RAndom";
    // randomly select start and finish locations
   // int xA, yA, xB, yB;
    xA = 7;
	yA = 9;
	xB = 9;
	yB = 6;
    

/*	switch(rand()%8)
    {
        case 0: xA=0;yA=0;xB=n-1;yB=m-1; break;
        case 1: xA=0;yA=m-1;xB=n-1;yB=0; break;
        case 2: xA=n/2-1;yA=m/2-1;xB=n/2+1;yB=m/2+1; break;
        case 3: xA=n/2-1;yA=m/2+1;xB=n/2+1;yB=m/2-1; break;
        case 4: xA=n/2-1;yA=0;xB=n/2+1;yB=m-1; break;
        case 5: xA=n/2+1;yA=m-1;xB=n/2-1;yB=0; break;
        case 6: xA=0;yA=m/2-1;xB=n-1;yB=m/2+1; break;
        case 7: xA=n-1;yA=m/2+1;xB=0;yB=m/2-1; break;
    }
*/

    cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
    cout<<"Start: "<<xA<<","<<yA<<endl;
    cout<<"Finish: "<<xB<<","<<yB<<endl;
    // get the route
    cout << "Antes do clock!!!";
    clock_t start = clock();
    string route=pathFind(xA, yA, xB, yB);
    if(route=="") cout<<"An empty route generated!"<<endl;
    clock_t end = clock();
    double time_elapsed = double(end - start);
    cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
    cout<<"Route:"<<endl;
    cout<<route<<endl<<endl;

    // follow the route on the map and display it 
    cout << "Antes do if!!!";
    if(route.length()>0)
    {
        int j; char c;
        int x=xA;
        int y=yA;
        map[x*dim + y]=2;
        for(int i=0;i<route.length();i++)
        {
            c =route.at(i);
            j=atoi(&c); 
            x=x+dx[j];
            y=y+dy[j];
            map[x*dim + y]=3;
            
            queue_temp.push(dx[j]);
            queue_temp.push(dy[j]);

        }
        queue_temp.push(10);
        queue_temp.push(10);

        printf("\nSize do queue_temp: %d\n", queue_temp.size());
        map[x*dim + y]=4;
    
        // display the map with the route
        for(int y=0;y<m;y++)
        {
            for(int x=0;x<n;x++)
                if(map[x*dim + y]==0)
                    cout<<".";
                else if(map[x*dim + y]==1)
                    cout<<"O"; //obstacle
                else if(map[x*dim + y]==2)
                    cout<<"S"; //start
                else if(map[x*dim + y]==3)
                    cout<<"R"; //route
                else if(map[x*dim + y]==4)
                	cout<<"F"; //finish
            cout<<endl;
        }
     //   printf("(%d,%d)", queue_astar.front(),queue_temp.front());
      //  printf("\n(%d,%d)",queue_astar.size(),queue_temp.size());
        
	}
        //Unindo movimentos na mesma coordenada

			v_base[0] = queue_temp.front(); //x
	    	queue_temp.pop();
	    	v_base[1] = queue_temp.front(); //y
	    	queue_temp.pop();

    /*      	v_aux[0] = queue_temp.front();
        	queue_temp.pop();
        	v_aux[1] = queue_temp.front();
        	queue_temp.pop();
		*/	
			printf("\nAntes do while");
        	while(!queue_temp.empty())
        	{
        		if(v_base[0] != 10)
        		{
	        		printf("\nentrou no while geral");
	        		printf("\nSize do queue_temp: %d", queue_temp.size());
	        	
	        		printf("\nSize do queue_temp: %d", queue_temp.size());
					//while((v_base[0] - v_aux[0]) != 0 && (v_base[1] - v_aux[1]) == 0) 
	        		while((v_base[1] == 0 && v_base[0] != 10)) //movimento x
	        		{
	        			printf("\nentrou no while do movimento x");
	        			movimentox = movimentox + v_base[0];
	        			comando[0] = movimentox;
	        			comando[1] = 0; 
	        		//	if(!queue_temp.empty())	
						{	
						v_base[0] = queue_temp.front(); //x
			        	queue_temp.pop();
			        	v_base[1] = queue_temp.front(); //y
			        	queue_temp.pop();
			    		}
						t1 = 1;
			        	printf("\nSize do queue_temp: %d", queue_temp.size());
			     }
			    	if(t1 == 1)
			    	{
			    		printf("\nfundiu 7 movimentos");
						queue_astar.push(comando[0]);
	        			queue_astar.push(comando[1]);
	        			movimentox = 0;
	        			t1 = 0;
	        			printf("\ncolocou (7,0) na fila astar ");
				 }
	        		
	        		//while((v_base[1] - v_aux[1]) != 0 && (v_base[0] - v_aux[0]) == 0) //movimento y
	        		
	        		while((v_base[0] == 0 && v_base[0] != 10)) //movimento y
					{
						printf("\nentrou no while do movimento y");
						
	        			movimentoy = movimentoy + v_base[1];
	        			comando[0] = 0;
	        			comando[1] = movimentoy; 
	        		//if(!queue_temp.empty())	
					{
						v_base[0] = queue_temp.front(); //x
			        	queue_temp.pop();
			        	v_base[1] = queue_temp.front(); //y
			        	queue_temp.pop();
			    	}
						t2 = 1;
			        	printf("\nSize do queue_temp: %d", queue_temp.size());
			    	}
			    	if(t2 == 1)
			    	{	printf("\nfundiu movimento y");
			    		queue_astar.push(comando[0]);
	        			queue_astar.push(comando[1]);
	        			movimentoy = 0;
	        			t2 = 0;
			    	}
			    	printf("\njogou mov y na fila");        		
					
	        		//while((v_base[0] - v_aux[0]) != 0 && (v_base[1] - v_aux[1]) != 0) //movimento diagonal
	        		while((v_base[0] < 0) && (v_base[1] < 0) && (v_base[0] > -100) && v_base[0] != 10) //movimento diagonal
					{
						//if(v_base[0] != 10)
						//{
						
						printf("\nentrou no while do movimento xy");
						movimentoxy1 = movimentoxy1 + v_base[0];
						movimentoxy2 = movimentoxy2 + v_base[1];
	        			comando[0] = movimentoxy1;
	        			comando[1] = movimentoxy2; 
	        		//if(!queue_temp.empty())	
	        		{
						v_base[0] = queue_temp.front(); //x
			        	queue_temp.pop();
			        	v_base[1] = queue_temp.front(); //y
			        	queue_temp.pop();
			    	}
						t3 = 1;
			        	printf("\nSize do queue_temp: %d", queue_temp.size());
			    	}
			    	if(t3 == 1)
			    	{
			    		printf("\nfundiu movimento xy");
			    		queue_astar.push(comando[0]);
	        			queue_astar.push(comando[1]);
	        			movimentoxy1 = 0;
	        			movimentoxy2 = 0;
	        			t3 = 0;
	        			
	        			printf("\njogou mov xy");
			    	}
			    	
			    	while((v_base[0] < 0) && (v_base[1] > 0) && (v_base[0] > -100) && v_base[0] != 10) //movimento diagonal
					{
						//if(v_base[0] != 10)
						//{
						
						printf("\nentrou no while do movimento xy");
						movimentoxy1 = movimentoxy1 + v_base[0];
						movimentoxy2 = movimentoxy2 + v_base[1];
	        			comando[0] = movimentoxy1;
	        			comando[1] = movimentoxy2; 
	        		//if(!queue_temp.empty())	
	        		{
						v_base[0] = queue_temp.front(); //x
			        	queue_temp.pop();
			        	v_base[1] = queue_temp.front(); //y
			        	queue_temp.pop();
			    	}
						t3 = 1;
			        	printf("\nSize do queue_temp: %d", queue_temp.size());
			    	}
			    	if(t3 == 1)
			    	{
			    		printf("\nfundiu movimento xy");
			    		queue_astar.push(comando[0]);
	        			queue_astar.push(comando[1]);
	        			movimentoxy1 = 0;
						movimentoxy2 = 0;
	        			t3 = 0;
	        			
	        			printf("\njogou mov xy");
			    	}
			    	
			    	while((v_base[0] > 0) && (v_base[1] > 0) && (v_base[0] > -100) && v_base[0] != 10) //movimento diagonal
					{
						//if(v_base[0] != 10)
						//{
						
						printf("\nentrou no while do movimento xy");
						movimentoxy1 = movimentoxy1 + v_base[0];
						movimentoxy2 = movimentoxy2 + v_base[1];
	        			comando[0] = movimentoxy1;
	        			comando[1] = movimentoxy2; 
	        		//if(!queue_temp.empty())	
	        		{
						v_base[0] = queue_temp.front(); //x
			        	queue_temp.pop();
			        	v_base[1] = queue_temp.front(); //y
			        	queue_temp.pop();
			    	}
						t3 = 1;
			        	printf("\nSize do queue_temp: %d", queue_temp.size());
			    	}
			    	if(t3 == 1)
			    	{
			    		printf("\nfundiu movimento xy");
			    		queue_astar.push(comando[0]);
	        			queue_astar.push(comando[1]);
	        			movimentoxy1 = 0;
	        			movimentoxy2 = 0;
	        			t3 = 0;
	        			
	        			printf("\njogou mov xy");
			    	}
			    	
			    	while((v_base[0] > 0) && (v_base[1] < 0) && (v_base[0] > -100) && v_base[0] != 10) //movimento diagonal
					{
						//if(v_base[0] != 10)
						//{
						
						printf("\nentrou no while do movimento xy");
						movimentoxy1 = movimentoxy1 + v_base[0];
						movimentoxy2 = movimentoxy2 + v_base[1];
	        			comando[0] = movimentoxy1;
	        			comando[1] = movimentoxy2; 
	        		//if(!queue_temp.empty())	
	        		{
						v_base[0] = queue_temp.front(); //x
			        	queue_temp.pop();
			        	v_base[1] = queue_temp.front(); //y
			        	queue_temp.pop();
			    	}
						t3 = 1;
			        	printf("\nSize do queue_temp: %d", queue_temp.size());
			    	}
			    	if(t3 == 1)
			    	{
			    		printf("\nfundiu movimento xy");
			    		queue_astar.push(comando[0]);
	        			queue_astar.push(comando[1]);
	        			movimentoxy1 = 0;
	        			movimentoxy2 = 0;
	        			t3 = 0;
	        			
	        			printf("\njogou mov xy");
			    	}
			    
	        	printf("\nSize do queue_temp: %d", queue_temp.size());
	        	}//else{break;}
	        	
			}
	        
        	
			printf("\nSAIU do while");
			printf("\nSize do queue_temp: %d", queue_temp.size());
        	res = 0;
			resx = 0;
        	resy = 0;
        	
			//printf("(%d,%d)", queue_astar.front(),queue_temp.front());
        	printf("\n Size: %d",queue_astar.size());
        	/*while(!queue_astar.empty())
        	{
        		printf("\n(%d,",queue_astar.front());
        		queue_astar.pop();
        		printf("%d)",queue_astar.front());
				queue_astar.pop();        		
        	}
        	*/
 			printf("\nSize do queue_astar: %d", queue_astar.size());
    
    //getchar(); // wait for a (Enter) keypress  
    //return(0);
 			return queue_astar;
}
/*
int main()
{
	node oie;
	
	oie.findpath();
	
	
	return 0;
	
	
}
*/
