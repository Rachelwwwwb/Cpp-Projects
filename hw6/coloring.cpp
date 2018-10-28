#include <queue>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Node{
    char letter;
    int x;
    int y;
    Node (char let ,int _x, int _y){
        letter = let;
        x = _x;
        y = _y;
    }
};

bool coloring(vector<vector<int>> adjacency_matrix, vector<int>& color, int index) 
{ 
    if (index == (int)adjacency_matrix.size()) return true; 
    for (int color_index = 1; color_index <= 4; color_index++) 
    { 
        bool safe = true;
         for (size_t i = 0; i < adjacency_matrix.size(); i++){ 
            if (adjacency_matrix[index][i] && color_index == color[i]) safe = false; 
        }
        if (safe) 
        { 
           color[index] = color_index; 
           if (coloring (adjacency_matrix, color, index+1))    return true;
           else  {
                 color[index] = 0;}
        } 
    } 
    return false;
} 
  
int main(int argc, char* argv[]){
    if (argc < 2){
        cout << "Missing file name!!!" << endl;
        return 1;
    }
    int blocks, rows, columns;

    ifstream ifile (argv[1]);

    if (ifile.fail()){
        cout << "Invalid file name!" << endl;
        return 1;
    }
    ifile >> blocks >> rows >> columns;

    //build an adjacency matrix
    vector<vector<int>> adjacency_matrix;
    for (int i = 0; i < blocks; i++){
        vector<int> tmp;
        adjacency_matrix.push_back(tmp);
        for (int j = 0; j < blocks; j++){
            adjacency_matrix[i].push_back(0);
        }
    }

    vector<vector<Node*>> graph;
    vector<vector<bool>> visited;

    for (int i = 0; i < rows; i++){
        vector<Node*> graphtmp;
        vector <bool> visittmp;
        graph.push_back(graphtmp);
        visited.push_back(visittmp);
        for (int j = 0; j < columns; j++){
            char tmp;
            ifile >> tmp;
            graph[i].push_back(new Node (tmp, i, j));
            visited[i].push_back(false);
        }
    }

    Node* start = graph[0][0];
    bool TBC = true;

    while (TBC){
        TBC = false;
        queue<Node*> q;
        q.push(start);
        visited[start->x][start->y] = true;
        int contX = 0;
        int contY = 0;

        //if the queue is not empty
        while (!q.empty()){
            Node*head = q.front();
		    q.pop();
            //search the up, down, left and right of the node
            //and test if it is out of border
            if(head->x+1 < rows){
		        if (visited[head->x+1][head->y] == false && graph[head->x+1][head->y]->letter == head->letter){
			        q.push(graph[head->x+1][head->y]);
			        visited[head->x+1][head->y] = true;
		        }
                else if (graph[head->x+1][head->y]->letter != head->letter){
                    adjacency_matrix[(int)head->letter - 'A'][(int)graph[head->x+1][head->y]->letter - 'A'] = 1;
                    adjacency_matrix[(int)graph[head->x+1][head->y]->letter - 'A'][(int)head->letter - 'A'] = 1;
                }
            }

            if (head->x-1 > 0){
                if (visited[head->x-1][head->y] == false && graph[head->x-1][head->y]->letter == head->letter){
			        q.push(graph[head->x-1][head->y]);
			        visited[head->x-1][head->y] = true;
		        }
                else if (graph[head->x-1][head->y]->letter != head->letter){
                    adjacency_matrix[(int)head->letter - 'A'][(int)graph[head->x-1][head->y]->letter - 'A'] = 1;
                    adjacency_matrix[(int)graph[head->x-1][head->y]->letter - 'A'][(int)head->letter - 'A'] = 1;
                }
            }

            if (head->y+1 < columns){
                if (visited[head->x][head->y+1] == false && graph[head->x][head->y+1]->letter == head->letter){
			        q.push(graph[head->x][head->y+1]);
			        visited[head->x][head->y+1] = true;
		        }
                else if (graph[head->x][head->y+1]->letter != head->letter){
                    adjacency_matrix[(int)head->letter - 'A'][(int)graph[head->x][head->y+1]->letter - 'A'] = 1;
                    adjacency_matrix[(int)graph[head->x][head->y+1]->letter - 'A'][(int)head->letter - 'A'] = 1;
                }
            }

            if (head->y-1 > 0){
                if (visited[head->x][head->y-1] == false && graph[head->x][head->y-1]->letter == head->letter){
			        q.push(graph[head->x][head->y-1]);
			        visited[head->x][head->y-1] = true;
		        }
                else if (graph[head->x][head->y-1]->letter != head->letter){
                    adjacency_matrix[(int)head->letter - 'A'][(int)graph[head->x][head->y-1]->letter - 'A'] = 1;
                    adjacency_matrix[(int)graph[head->x][head->y-1]->letter - 'A'][(int)head->letter - 'A'] = 1;
                }
            }
        }

        //search to find the next starting node
        //the search starts from the last start
        bool toBreak = false;
        for (int i = contX; i < rows; i++){
            if (i == contX){
                for (int j = contY; j < columns; j++){
                        if (visited[i][j] == false){
                        start = graph[i][j];
                        contX = i;
                        contY = j;
                        TBC = true;
                        toBreak = true;
                        break;
                        }
                if (toBreak) break;
                }
            }
            if (toBreak) break; 

            else{
                for (int j = 0; j < columns; j++){
                    if (visited[i][j] == false){
                        start = graph[i][j];
                        contX = i;
                        contY = j;
                        TBC = true;
                        toBreak = true;
                        break;
                    }
                if (toBreak) break;
            }
                if (toBreak) break;
            }
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            delete graph[i][j];
        }
    }

    vector<int> color;
    for (int i = 0; i < blocks; i ++){
        color.push_back(0);}
    coloring(adjacency_matrix, color, 0); 

    for (int i = 0; i < blocks; i ++){
        char a = (char) (i + 'A');
        cout << a << " " << color[i] << endl;
    }
    return 0;
}