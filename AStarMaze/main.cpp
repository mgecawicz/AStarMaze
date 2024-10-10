//
//  main.cpp
//  AStarMaze
//
//  Created by Michael Gecawicz on 10/9/24.
//

#include <iostream>
#include <thread>
#include <random>
#include <cmath>
#include <vector>
#include <locale>
#include <codecvt>
#include <string>

using namespace std;

int sz = 60;
const int INITIAL_CELL_DIST = 10000;

vector<vector<int>> cells(sz, vector<int>(sz, 0));
vector<vector<int>> cr(sz, vector<int>(sz, INITIAL_CELL_DIST));

int x = 2, y = 2;

int gx = 48, gy = 48;


vector<vector<int>> path;
vector<vector<int>> visited;

void sleepFor(unsigned int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

double dist(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void shuffleDirections(vector<vector<int>>& directions) {
    random_device rd;
    mt19937 gen(rd());
    shuffle(directions.begin(), directions.end(), gen);
}

void generateMaze(int a, int b, int locationValue){
    cr[a][b] = locationValue;
    vector<vector<int>> directions = {
        {0, 1},   // down
        {1, 0},   // right
        {0, -1},  // up
        {-1, 0}   // left
    };
    shuffleDirections(directions);
    for (int i = 0; i < directions.size(); i++){
        int nx = a + directions[i][0] * 2;
        int ny = b + directions[i][1] * 2;
        double distToTarget = dist(a,b,gx,gy);
        if (nx > 0 && ny > 0 && nx < cr.size() && ny < cr[0].size() && cr[nx][ny] == INITIAL_CELL_DIST) {
            cr[a + directions[i][0]][b + directions[i][1]] = distToTarget;
            generateMaze(nx, ny, int(distToTarget));
        }
    }
}

void backtrack(){
    if (path.empty()){
        sleepFor(5000);
        cout << "COULD NOT FIND PATH" << endl;
        return;
    }
    x = path.back()[0];
    y = path.back()[1];
    path.pop_back();
}



string bestDir(int desire){
    float highestDr = INITIAL_CELL_DIST;
    string bestDirection = "NONE";
    
    vector<pair<string, pair<int, int>>> directions = {
        {"RIGHT", {1, 0}},
        {"DOWN", {0, 1}},
        {"LEFT", {-1, 0}},
        {"UP", {0, -1}}
    };
    
    for (const auto& dir : directions) {
        int nx = x + dir.second.first;
        int ny = y + dir.second.second;
        if (nx >= 0 && ny >= 0 && nx < sz && ny < sz && cr[nx][ny] < highestDr && cells[nx][ny] == desire) {
            highestDr = cr[nx][ny];
            bestDirection = dir.first;
        }
    }
    return bestDirection;
}
void findBestFit(int desire) {
    string bestDirection = bestDir(desire);
    if (bestDirection == "RIGHT") {
        ++x;
    } else if (bestDirection == "DOWN") {
        ++y;
    } else if (bestDirection == "LEFT") {
        --x;
    } else if (bestDirection == "UP") {
        --y;
    } else {
        backtrack();
        return;
    }
    path.push_back({x, y});
    visited.push_back({x, y});
}

void draw(){
    bool complete = false;
    
    while(complete == false){
        
        if (dist(x,y,gx,gy) < sqrt(2)){
            cout << "Found Objective" << endl;
            sleepFor(1000);
            complete = true;
        }
        system("clear");
        findBestFit(0);
        
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (cr[i][j] > 1000) {
                    cells[i][j] = -1;
                }
            }
        }
        for (const auto& p : visited){
            cells[p[0]][p[1]] = 1;
        }
        for (const auto& p : path){
            cells[p[0]][p[1]] = 2;
        }
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                if (i == x && j == y) {
                    printf("\x1B[34m▓\033[0m");
                } else if (i == gx && j == gy) {
                    printf("\033[1;33m&\033[0m");
                } else if (cells[i][j] == 1) {
                    printf("\x1B[36m▓\033[0m");
                } else if (cells[i][j] == 2) {
                    printf("\x1B[31m▓\033[0m");
                } else if (cells[i][j] == -1) {
                    printf("▓");
                } else {
                    cout << ' ';
                }
            }
            cout << endl;
        }
    }
}

int main(int argc, const char * argv[]) {
    generateMaze(1,1,0);
    draw();
    return 0;
}
