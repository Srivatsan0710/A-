
#include<bits/stdc++.h>
using namespace std;
#define ROW 10
#define COL 10
struct Cell
{
    	int Pi, Pj;
    	double f, g, h;
};

bool isValid(int row, int col)
{
    return ((row >= 0) && (row < ROW) && (col >= 0) && (col < COL));
}

bool notblocked(int grid[][COL], int row, int col)
{
    if (grid[row][col] == 1)
        return true;
    else
        return false;
}

bool isGoal(int row, int col, pair <int,int> dest)
{
    if (row == dest.first && col == dest.second)
        return true;
    else
        return false;
}

double Heuristic(int row, int col, pair <int,int> dest)
{
    return ((double)sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}

void Path(Cell Grid[][COL], pair <int,int> dest)
{
    printf ("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
 
    stack< pair<int, int> > Path;
 
    while (!(Grid[row][col].Pi == row
             && Grid[row][col].Pj == col ))
    {
        Path.push (make_pair (row, col));
        int temp_row = Grid[row][col].Pi;
        int temp_col = Grid[row][col].Pj;
        row = temp_row;
        col = temp_col;
    }
 
    Path.push (make_pair (row, col));
    while (!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        printf("\n---->> (%d,%d) ",p.first,p.second);
    }
    return;
}
 
void AStar(int grid[][COL], pair <int,int> src, pair <int,int> dest)
{
    if (!isValid(src.first, src.second))
    {
        printf ("Invalid value\n");
        return;
    }
    if ( !isValid (dest.first, dest.second))
    {
        printf ("Invalid Value\n");
        return;
    }
    if ( !notblocked(grid, src.first, src.second) || !notblocked(grid, dest.first, dest.second))
    {
        printf ("Blocked\n");
        return;
    }
    if (isGoal(src.first, src.second, dest))
    {
        printf ("Reached\n");
        return;
    }
    bool Closed[ROW][COL];
    memset(Closed, false, sizeof (Closed));
    Cell Grid[ROW][COL];
 
    int i, j;
 
    for (i=0; i<ROW; i++)
    {
        for (j=0; j<COL; j++)
        {
            Grid[i][j].f = 100000.00;
            Grid[i][j].g = 100000.00;
            Grid[i][j].h = 100000.00;
            Grid[i][j].Pi = -1;
            Grid[i][j].Pj = -1;
        }
    }

    i = src.first, j = src.second;
    Grid[i][j].f = 0.0;
    Grid[i][j].g = 0.0;
    Grid[i][j].h = 0.0;
    Grid[i][j].Pi = i;
    Grid[i][j].Pj = j;

    set< pair <double, pair<int, int> > > Open;

    Open.insert(make_pair (0.0, make_pair (i, j)));

    bool found = false;
 
    while (!Open.empty())
    {
        pair<double, pair<int, int> > p = *Open.begin();
        Open.erase(Open.begin());
        i = p.second.first;
        j = p.second.second;
        Closed[i][j] = true;
        double gNew, hNew, fNew;
 
        if (isValid(i-1, j) == true)
        {
            if (isGoal(i-1, j, dest) == true)
            {
                Grid[i-1][j].Pi = i;
                Grid[i-1][j].Pj = j;
                printf ("The destination Reached\n");
                Path (Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i-1][j] == false && notblocked(grid, i-1, j) == true)
            {
                gNew = Grid[i][j].g + 1.0;
                hNew = Heuristic(i-1, j, dest);
                fNew = gNew + hNew;
                if (Grid[i-1][j].f == 100000.00 || Grid[i-1][j].f > fNew)
                {
                    Open.insert( make_pair(fNew,make_pair(i-1, j)));
                    Grid[i-1][j].f = fNew;
                    Grid[i-1][j].g = gNew;
                    Grid[i-1][j].h = hNew;
                    Grid[i-1][j].Pi = i;
                    Grid[i-1][j].Pj = j;
                }
            }
        }

        if (isValid(i+1, j) == true)
        {
            if (isGoal(i+1, j, dest) == true)
            {
                Grid[i+1][j].Pi = i;
                Grid[i+1][j].Pj = j;
                printf("Destination found\n");
                Path(Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i+1][j] == false && notblocked(grid, i+1, j) == true)
            {
                gNew = Grid[i][j].g + 1.0;
                hNew = Heuristic(i+1, j, dest);
                fNew = gNew + hNew;
                if (Grid[i+1][j].f == 100000.00 || Grid[i+1][j].f > fNew)
                {
                    Open.insert( make_pair (fNew, make_pair (i+1, j)));
                    Grid[i+1][j].f = fNew;
                    Grid[i+1][j].g = gNew;
                    Grid[i+1][j].h = hNew;
                    Grid[i+1][j].Pi = i;
                    Grid[i+1][j].Pj = j;
                }
            }
        }
        if (isValid (i, j+1) == true)
        {
            if (isGoal(i, j+1, dest) == true)
            {
                Grid[i][j+1].Pi = i;
                Grid[i][j+1].Pj = j;
                printf("Destination found\n");
                Path(Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i][j+1] == false && notblocked (grid, i, j+1) == true)
            {
                gNew = Grid[i][j].g + 1.0;
                hNew = Heuristic (i, j+1, dest);
                fNew = gNew + hNew;
                if (Grid[i][j+1].f == 100000.00 || Grid[i][j+1].f > fNew)
                {
                    Open.insert( make_pair(fNew, make_pair (i, j+1)));
                    Grid[i][j+1].f = fNew;
                    Grid[i][j+1].g = gNew;
                    Grid[i][j+1].h = hNew;
                    Grid[i][j+1].Pi = i;
                    Grid[i][j+1].Pj = j;
                }
            }
        }
        if (isValid(i, j-1) == true)
        {
            if (isGoal(i, j-1, dest) == true)
            {
                Grid[i][j-1].Pi = i;
                Grid[i][j-1].Pj = j;
                printf("Destination found\n");
                Path(Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i][j-1] == false && notblocked(grid, i, j-1) == true)
            {
                gNew = Grid[i][j].g + 1.0;
                hNew = Heuristic(i, j-1, dest);
                fNew = gNew + hNew;
                if (Grid[i][j-1].f == 100000.00 || Grid[i][j-1].f > fNew)
                {
                    Open.insert( make_pair (fNew, make_pair (i, j-1)));
                    Grid[i][j-1].f = fNew;
                    Grid[i][j-1].g = gNew;
                    Grid[i][j-1].h = hNew;
                    Grid[i][j-1].Pi = i;
                    Grid[i][j-1].Pj = j;
                }
            }
        }
        if (isValid(i-1, j+1) == true)
        {
            if (isGoal(i-1, j+1, dest) == true)
            {
                Grid[i-1][j+1].Pi = i;
                Grid[i-1][j+1].Pj = j;
                printf ("Destination found\n");
                Path (Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i-1][j+1] == false && notblocked(grid, i-1, j+1) == true)
            {
                gNew = Grid[i][j].g + 1.414;
                hNew = Heuristic(i-1, j+1, dest);
                fNew = gNew + hNew;
                if (Grid[i-1][j+1].f == 100000.00 || Grid[i-1][j+1].f > fNew)
                {
                    Open.insert( make_pair (fNew, make_pair(i-1, j+1)));
                    Grid[i-1][j+1].f = fNew;
                    Grid[i-1][j+1].g = gNew;
                    Grid[i-1][j+1].h = hNew;
                    Grid[i-1][j+1].Pi = i;
                    Grid[i-1][j+1].Pj = j;
                }
            }
        }
        if (isValid (i-1, j-1) == true)
        {
            if (isGoal (i-1, j-1, dest) == true)
            {
                Grid[i-1][j-1].Pi = i;
                Grid[i-1][j-1].Pj = j;
                printf ("Destination found\n");
                Path (Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i-1][j-1] == false && notblocked(grid, i-1, j-1) == true)
            {
                gNew = Grid[i][j].g + 1.414;
                hNew = Heuristic(i-1, j-1, dest);
                fNew = gNew + hNew;
                if (Grid[i-1][j-1].f == 100000.00 || Grid[i-1][j-1].f > fNew)
                {
                    Open.insert( make_pair (fNew, make_pair (i-1, j-1)));
                    Grid[i-1][j-1].f = fNew;
                    Grid[i-1][j-1].g = gNew;
                    Grid[i-1][j-1].h = hNew;
                    Grid[i-1][j-1].Pi = i;
                    Grid[i-1][j-1].Pj = j;
                }
            }
        }
        if (isValid(i+1, j+1) == true)
        {
            if (isGoal(i+1, j+1, dest) == true)
            {
                Grid[i+1][j+1].Pi = i;
                Grid[i+1][j+1].Pj = j;
                printf ("Destination found\n");
                Path (Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i+1][j+1] == false &&
                     notblocked(grid, i+1, j+1) == true)
            {
                gNew = Grid[i][j].g + 1.414;
                hNew = Heuristic(i+1, j+1, dest);
                fNew = gNew + hNew;
                if (Grid[i+1][j+1].f == 100000.00 || Grid[i+1][j+1].f > fNew)
                {
                    Open.insert(make_pair(fNew, make_pair (i+1, j+1)));
                    Grid[i+1][j+1].f = fNew;
                    Grid[i+1][j+1].g = gNew;
                    Grid[i+1][j+1].h = hNew;
                    Grid[i+1][j+1].Pi = i;
                    Grid[i+1][j+1].Pj = j;
                }
            }
        }
        if (isValid (i+1, j-1) == true)
        {
            if (isGoal(i+1, j-1, dest) == true)
            {
                Grid[i+1][j-1].Pi = i;
                Grid[i+1][j-1].Pj = j;
                printf("Destination found\n");
                Path(Grid, dest);
                found = true;
                return;
            }
            else if (Closed[i+1][j-1] == false && notblocked(grid, i+1, j-1) == true)
            {
                gNew = Grid[i][j].g + 1.414;
                hNew = Heuristic(i+1, j-1, dest);
                fNew = gNew + hNew;
                if (Grid[i+1][j-1].f == 100000.00 || Grid[i+1][j-1].f > fNew)
                {
                    Open.insert(make_pair(fNew, make_pair(i+1, j-1)));
                    Grid[i+1][j-1].f = fNew;
                    Grid[i+1][j-1].g = gNew;
                    Grid[i+1][j-1].h = hNew;
                    Grid[i+1][j-1].Pi = i;
                    Grid[i+1][j-1].Pj = j;
                }
            }
        }
    }
    if (found == false)
        printf("Search Not Found\n");
 
    return;
}

int main()
{
    int grid[ROW][COL];
    cout << "Enter input matrix grid (10 x 10) : ";
    for(int i=0; i<10; i++)
    {
    	for(int j=0; j<10; j++)
    	{
    		cin >> grid[i][j];
    	}
    }
    int si,sj;
    cout << "Enter Source Location (x,y): ";
    cin >> si >> sj;
    pair<int, int> src = make_pair(si, sj);
    cout << "Enter Destination Location (x,y): ";
    cin >> si >> sj;
    pair<int, int> dest = make_pair(si, sj);
 
    AStar(grid, src, dest);
 
    return 0;
}
