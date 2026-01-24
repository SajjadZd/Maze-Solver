#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

#define WHITE 15
#define YELLOW 6
#define GREEN 10
#define BLUE 9
#define RED 12

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct Cell {
    int x, y;
};

class MazeSolver {
private:
    int height, width;
    vector<vector<int> > maze;
    vector<vector<bool> > visited;
    vector<vector<Cell> > parent;
    
    void dfsMaze(int x, int y)
	{
	    int directions[4] = {0, 1, 2, 3};
	
	    // Shuffle directions
	    for (int i = 0; i < 4; i++) {
	        int r = rand() % 4;
	        swap(directions[i], directions[r]);
	    }
	
	    for (int i = 0; i < 4; i++) {
	        int dir = directions[i];
	        int nx = x, ny = y;
	
	        if (dir == 0) nx = x + 2;     // down
	        if (dir == 1) nx = x - 2;     // up
	        if (dir == 2) ny = y + 2;     // right
	        if (dir == 3) ny = y - 2;     // left
	
	        if (nx > 0 && ny > 0 && nx < height - 1 && ny < width - 1) {
	            if (maze[nx][ny] == 1) {
	                // break wall
	                maze[(x + nx) / 2][(y + ny) / 2] = 0;
	                maze[nx][ny] = 0;
	
	                dfsMaze(nx, ny);   // backtracking
	            }
	        }
	    }
	}


public:
    MazeSolver(int h, int w) {
        height = h;
        width = w;

        maze.resize(height, vector<int>(width));
        visited.resize(height, vector<bool>(width, false));
        parent.resize(height, vector<Cell>(width));
    }

    void generateMaze() {
			
	    for (int i = 0; i < height; i++)
	        for (int j = 0; j < width; j++)
	            maze[i][j] = 1;
	
	    dfsMaze(1, 1);
	
	    // Connect start
	    maze[0][0] = 0;
	    maze[1][0] = 0;
	
	    // Connect end
	    maze[height - 1][width - 1] = 0;
	    maze[height - 2][width - 1] = 0;
    }

    bool bfsSolve() {
    	
    	for (int i = 0; i < height; i++)
    	{
    		for (int j = 0; j < width; j++)
        	{
        		visited[i][j] = false;
			}
		}
    
        
        queue<Cell> q;
        q.push({0, 0});
        visited[0][0] = true;
        parent[0][0] = {-1, -1};

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            Cell current = q.front();
            q.pop();

            if (current.x == height - 1 && current.y == width - 1)
            {
            	return true;
			}

            for (int i = 0; i < 4; i++) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];

                if (nx >= 0 && ny >= 0 && nx < height && ny < width) {
                    if (!visited[nx][ny] && maze[nx][ny] == 0) {
                        visited[nx][ny] = true;
                        parent[nx][ny] = current;
                        q.push({nx, ny});
                    }
                }
            }
        }
        return false;
    }

    void printMaze() 
	{
	    cout << "\nGenerated Maze:\n";
	    for (int i = 0; i < height; i++) {
	        for (int j = 0; j < width; j++) {
	
	            if (i == 0 && j == 0) {
	                setColor(BLUE);
	                cout << "[]";
	            }
	            else if (i == height - 1 && j == width - 1) {
	                setColor(RED);
	                cout << "[]";
	            }
	            else if (maze[i][j] == 1) {
	                setColor(YELLOW);
	                cout << "[]";
	            }
	            else {
	                setColor(WHITE);
	                cout << "[]";
	            }
	        }
	        cout << endl;
	    }
	    setColor(WHITE);
	}
	
	void printSolvedMaze() 
	{
	    Cell cur = {height - 1, width - 1};
	    while (cur.x != -1 && cur.y != -1) {
	        if (!(cur.x == 0 && cur.y == 0) &&
	            !(cur.x == height - 1 && cur.y == width - 1)) {
	            maze[cur.x][cur.y] = 2;
	        }
	        cur = parent[cur.x][cur.y];
	    }
	
	    cout << "\nSolved Maze:\n";
	    
	    for (int i = 0; i < height; i++) {
	        for (int j = 0; j < width; j++) {
	
	            if (i == 0 && j == 0) {
	                setColor(BLUE);
	                cout << "[]";
	            }
	            else if (i == height - 1 && j == width - 1) {
	                setColor(RED);
	                cout << "[]";
	            }
	            else if (maze[i][j] == 1) {
	                setColor(YELLOW);
	                cout << "[]";
	            }
	            else if (maze[i][j] == 2) {
	                setColor(GREEN);
	                cout << "--";
	            }
	            else {
	                setColor(WHITE);
	                cout << "[]";
	            }
	        }
	        cout << endl;
	    }
	    setColor(WHITE);
	}

};

int main() {
    srand(time(0));

    int height, width;
    cout << "Enter maze height: ";
    cin >> height;
    cout << "Enter maze width: ";
    cin >> width;
    
    cout << "\n{";
    setColor(BLUE);
    cout << "[]";
    setColor(WHITE);
    cout << " = Start, ";
    
    setColor(RED);
    cout << "[]";
    setColor(WHITE);
    cout << " = End, ";
    
    setColor(YELLOW);
    cout << "[]";
    setColor(WHITE);
    cout << " = Walls, ";
    
    setColor(GREEN);
    cout << "--";
    setColor(WHITE);
    cout << " = Solved Path, [] = Empthy Path}\n";
	    
    
    if (height % 2 == 0) height++;
	if (width % 2 == 0) width++;

    MazeSolver solver(height, width);

    solver.generateMaze();
    solver.printMaze();
    
    

    if (solver.bfsSolve())
    {
    	solver.printSolvedMaze();
	}
    else
    {
    	cout << "\nNo path found from S to E.\n";
	}

    return 0;
}

