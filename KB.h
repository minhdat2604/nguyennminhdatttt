#pragma once
#include <vector>
#include <iostream>

using namespace std;

// Định nghĩa các ký tự hiển thị trong Maze
const char WALL_CHAR = '#';    // Tường
const char PATH_CHAR = ' ';    // Đường đi
const char PLAYER_CHAR = 'P';  // Người chơi
const char START_CHAR = 'S';   // Điểm bắt đầu
const char END_CHAR = 'E';     // Điểm đích
const char ROUTE_BFS = '.';    // Đường đi tự giải bằng BFS
const char ROUTE_DFS = '*';    // Đường đi tự giải bằng DFS

// Cấu trúc lưu trữ tọa độ ô trong mê cung
struct Point {
    int r, c;
    bool operator==(const Point& o) const { return r == o.r && c == o.c; }
};

class MazeGame {
private:
    int width, height; // Kích thước mê cung (nên chọn số lẻ)
    vector<vector<char>> grid;
    Point start, target;
    Point player;

    // Lưu độ dài đường đi để so sánh
    int bfs_path_len = 0;
    int dfs_path_len = 0;

    // Hàm đệ quy tạo mê cung chạy nội bộ
    void dfsGenerate(int r, int c);

public:
    // Hàm khởi tạo và thiết lập trò chơi
    MazeGame(int w = 21, int h = 21);

    void setDifficulty(int w, int h);
    void generate();
    void display(const vector<vector<char>>& currentGrid);
    void displayCurrent();
    void play();
    void solveBFS(bool showVisual);
    void solveDFS(bool showVisual);
    void compareAlgorithms();
};