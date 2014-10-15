////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stlastar.h" // See header for copyright and usage information

#include <iostream>
#include <stdio.h>
#include <queue>

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

// Global data

// The world map

const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;

int xmov, ymov;
int xinit, yinit;
int xtraj,ytraj;
std::queue<int> queue_temp;
std::queue<int> queue;
int comando[2];

void fila()
{
	int v_base[2]; //valor que servir� de compara��o para saber se ou x ou y sofreram altera��es. Ser� sempre o 1� valor
	int v_aux[2]; //valor que subtrair� de v_base para saber se houve altera��o de x e/ou y

	int res = 0;
	int resx = 0;
	int resy = 0;

	v_base[0] = queue_temp.front(); //x
	queue_temp.pop();
	v_base[1] = queue_temp.front(); //y
	queue_temp.pop();
		
	v_aux[0] = queue_temp.front();
	queue_temp.pop();
	v_aux[1] = queue_temp.front();
	queue_temp.pop();
	
	while(!queue_temp.empty())
	{
		
		while((v_base[0] - v_aux[0]) != 0 && (v_base[1] - v_aux[1]) == 0) //movimento x
		{
			res = res + (v_aux[0] - v_base[0]);
			
			v_base[0] = v_aux[0];
			
			v_aux[0] = queue_temp.front();
			queue_temp.pop();
			v_aux[1] = queue_temp.front();
			queue_temp.pop();		
		}
		comando[0] = res*0.25;
		comando[1] = v_base[1]*0.25;
		queue.push(comando[0]);
		queue.push(comando[1]);
		res = 0;
		
		while((v_base[1] - v_aux[1]) != 0 && (v_base[0] - v_aux[0]) == 0) //movimento y
		{
			res = res + (v_aux[1] - v_base[1]);
			
			v_base[1] = v_aux[1];
			
			v_aux[0] = queue_temp.front();
			queue_temp.pop();
			v_aux[1] = queue_temp.front();
			queue_temp.pop();		
		}
		comando[0] = v_base[0]*0.25;
		comando[1] = res*0.25;
		queue.push(comando[0]);
		queue.push(comando[1]);
		res = 0;
		
		while((v_base[0] - v_aux[0]) != 0 && (v_base[1] - v_aux[1]) != 0) //movimento diagonal
		{
			resx = resx + (v_aux[0] - v_base[0]);
			resy = resy + (v_aux[1] - v_base[1]);
			
			v_base[0] = v_aux[0];
			v_base[1] = v_aux[1];
			
			v_aux[0] = queue_temp.front();
			queue_temp.pop();
			v_aux[1] = queue_temp.front();
			queue_temp.pop();		
		}
		comando[0] = resx*0.25;
		comando[1] = resy*0.25;
		queue.push(comando[0]);
		queue.push(comando[1]);
		resx = 0;
		resy = 0;
		
		
		
	}

	
}

int world_map[ MAP_WIDTH * MAP_HEIGHT ] = 
{
/*
// 0001020304050607080910111213141516171819
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
	1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
	1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
	1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
	1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
	1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
	1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

};
*/

// 00010203040506070809101112131415
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,   // 00
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,   // 01
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 02
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 03
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 04
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 05
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 06
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 07
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 08
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 09
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 10
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 11
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 12
	9,9,1,1,1,1,1,1,1,1,1,1,1,1,9,9,   // 13
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,   // 14
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,   // 15
	
};
// map helper functions

int GetMap( int x, int y )
{
	if( x < 0 ||
	    x >= MAP_WIDTH ||
		 y < 0 ||
		 y >= MAP_HEIGHT
	  )
	{
		return 9;	 
	}

	return world_map[(y*MAP_WIDTH)+x];
}



// Definitions

class MapSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;	
	
	MapSearchNode() { x = y = 0; }
	MapSearchNode( int px, int py ) { x=px; y=py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo(); 


};

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	//robotino movements 
	if(x != xinit || y != yinit)
	{
		//movimentos horizontais e verticais
		if(xmov < x && ymov == y) {xtraj++;}
		if(xmov > x && ymov == y) {xtraj--;}
		if(xmov == x && ymov < y) {ytraj++;}
		if(xmov == x && ymov > y) {ytraj--;}
	}
	if(x != xinit && y != yinit)
	{
		//movimentos diagonais
		if(xmov < x && ymov < y) {xtraj++; ytraj++;}
		if(xmov < x && ymov > y) {xtraj++; ytraj--;}
		if(xmov > x && ymov < y) {xtraj--; ytraj++;}
		if(xmov > x && ymov > y) {xtraj--; ytraj--;}
	}
	xmov = x;
	ymov = y;
	
	queue_temp.push(xtraj);
	queue_temp.push(ytraj); 
		
	char str[100];
	sprintf( str, "Node position : (%d,%d)   (%d,%d)  size: %d\n", x,y,xtraj,ytraj,queue_temp.size() );

	cout << str;
	
	fila();

}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	float xd = float( ( (float)x - (float)nodeGoal.x ) );
	float yd = float( ( (float)y - (float)nodeGoal.y) );

	return xd + yd;

}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x, y-1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y ) < 9)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (GetMap( x, y+1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );

}


// Main

void astar()
{
	cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	AStarSearch<MapSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;
	
	while(SearchCount < NumSearches)
	{

		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = 2;//rand()%MAP_WIDTH;
		nodeStart.y = 2;//rand()%MAP_HEIGHT; 
				
		xinit = nodeStart.x;
		yinit = nodeStart.y;
		
		xtraj = 0;
		ytraj = 0;

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = 13;//rand()%MAP_WIDTH;						
		nodeEnd.y = 13;//rand()%MAP_HEIGHT; 
		
		// Set Start and goal states
		
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();
				
			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				p->PrintNodeInfo();
	#endif			
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";

				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif
				int steps = 0;

				node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}

					node->PrintNodeInfo();
					steps ++;
				
				};

				cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();

	
		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			cout << "Search terminated. Did not find goal state\n";
		
		}

		// Display the number of loops the search went through
		cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}
	
	//return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
