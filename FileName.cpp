#include "KB.h"
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <conio.h>

// Hàm khởi tạo
MazeGame::MazeGame(int w, int h) {
    setDifficulty(w, h);
}

// Chức năng 7: Điều chỉnh độ khó (Kích thước)
void MazeGame::setDifficulty(int w, int h) {

    width = (w % 2 == 0) ? w + 1 : w;
    height = (h % 2 == 0) ? h + 1 : h;
    generate();
}

// Chức năng 1: Tạo mê cung ngẫu nhiên bằng DFS (Recursive Backtracker)
void MazeGame::generate() {
    grid.assign(height, vector<char>(width, WALL_CHAR));
    srand(static_cast<unsigned int>(time(0)));

    // Bắt đầu đào đường từ ô (1, 1)
    dfsGenerate(1, 1);

    start = { 1, 1 };
    target = { height - 2, width - 2 };
    grid[start.r][start.c] = PATH_CHAR;
    grid[target.r][target.c] = PATH_CHAR;

    player = start;
    bfs_path_len = 0;
    dfs_path_len = 0;
}

// Hàm đào đường đệ quy DFS ngầm
void MazeGame::dfsGenerate(int r, int c) {
    grid[r][c] = PATH_CHAR;

    // 4 hướng di chuyển nhảy 2 bước: Trên, Dưới, Trái, Phải
    int dr[] = { -2, 2, 0, 0 };
    int dc[] = { 0, 0, -2, 2 };

    // Tráo ngẫu nhiên thứ tự các hướng đi
    int dirs[] = { 0, 1, 2, 3 };
    for (int i = 0; i < 4; i++) {
        int rIdx = rand() % 4;
        swap(dirs[i], dirs[rIdx]);
    }

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[dirs[i]];
        int nc = c + dc[dirs[i]];

        if (nr > 0 && nr < height - 1 && nc > 0 && nc < width - 1) {
            if (grid[nr][nc] == WALL_CHAR) {
                grid[r + dr[dirs[i]] / 2][c + dc[dirs[i]] / 2] = PATH_CHAR;
                dfsGenerate(nr, nc);
            }
        }
    }
}

// Chức năng 2: Hiển thị mê cung ASCII trên terminal
void MazeGame::display(const vector<vector<char>>& currentGrid) {
    system("cls"); // Xóa màn hình CLI
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (r == player.r && c == player.c) {
                cout << PLAYER_CHAR << " ";
            }
            else if (r == start.r && c == start.c) {
                cout << START_CHAR << " ";
            }
            else if (r == target.r && c == target.c) {
                cout << END_CHAR << " ";
            }
            else {
                if (currentGrid[r][c] == WALL_CHAR) {
                    cout << "##"; // Dùng ký tự kép để hiển thị vuông vắn hơn
                }
                else if (currentGrid[r][c] == ROUTE_BFS) {
                    cout << ". ";
                }
                else if (currentGrid[r][c] == ROUTE_DFS) {
                    cout << "* ";
                }
                else {
                    cout << "  ";
                }
            }
        }
        cout << "\n";
    }
}

void MazeGame::displayCurrent() {
    display(grid);
}

// Chức năng 3: Người chơi tự giải bằng phím W/A/S/D
void MazeGame::play() {
    player = start;
    while (!(player == target)) {
        displayCurrent();
        cout << "\n=== DIEU KHIEN ===================================\n";
        cout << "Dung W (Len), S (Xuong), A (Trai), D (Phai). Bam Q de thoat.\n";
        cout << "==================================================\n";

        char ch = _getch();
        if (ch == 'q' || ch == 'Q') return;

        int nr = player.r;
        int nc = player.c;
        if (ch == 'w' || ch == 'W') nr--;
        else if (ch == 's' || ch == 'S') nr++;
        else if (ch == 'a' || ch == 'A') nc--;
        else if (ch == 'd' || ch == 'D') nc++;

 
        if (nr >= 0 && nr < height && nc >= 0 && nc < width && grid[nr][nc] != WALL_CHAR) {
            player = { nr, nc };
        }
    }
    displayCurrent();
    cout << "\n[CHUC MUNG] Ban da tu giai va thoat khoi me cung thanh cong!\n";
    cout << "Nhan phim bat ky de tiep tuc...";
    _getch();
}

// Chức năng 4: Tự động giải bằng BFS (đường ngắn nhất)
void MazeGame::solveBFS(bool showVisual) {
    vector<vector<Point>> parent(height, vector<Point>(width, { -1, -1 }));
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    queue<Point> q;

    q.push(start);
    visited[start.r][start.c] = true;

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };
    bool found = false;

    while (!q.empty()) {
        Point curr = q.front();
        q.pop();

        if (curr == target) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                if (grid[nr][nc] != WALL_CHAR && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    parent[nr][nc] = curr;
                    q.push({ nr, nc });
                }
            }
        }
    }

    if (found) {
        vector<vector<char>> tempGrid = grid;
        Point curr = target;
        bfs_path_len = 0;
        while (!(curr == start)) {
            if (!(curr == target)) tempGrid[curr.r][curr.c] = ROUTE_BFS;
            curr = parent[curr.r][curr.c];
            bfs_path_len++;
        }
        if (showVisual) {
            player = start;
            display(tempGrid);
            cout << "\n[BFS SUCCESS] Tim thay duong di ngan nhat: " << bfs_path_len << " buoc (Ky hieu: .)\n";
            cout << "Nhan phim bat ky de quay lai...";
            _getch();
        }
    }
}

// Chức năng 5: Tự động giải bằng DFS (hiển thị hành trình tìm kiếm/backtrack)
void MazeGame::solveDFS(bool showVisual) {
    vector<vector<Point>> parent(height, vector<Point>(width, { -1, -1 }));
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    stack<Point> s;

    s.push(start);
    visited[start.r][start.c] = true;

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };
    bool found = false;

    while (!s.empty()) {
        Point curr = s.top();
        s.pop();

        if (curr == target) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];

            if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
                if (grid[nr][nc] != WALL_CHAR && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    parent[nr][nc] = curr;
                    s.push({ nr, nc });
                }
            }
        }
    }

    if (found) {
        vector<vector<char>> tempGrid = grid;
        Point curr = target;
        dfs_path_len = 0;
        while (!(curr == start)) {
            if (!(curr == target)) tempGrid[curr.r][curr.c] = ROUTE_DFS;
            curr = parent[curr.r][curr.c];
            dfs_path_len++;
        }
        if (showVisual) {
            player = start;
            display(tempGrid);
            cout << "\n[DFS SUCCESS] Tim thay duong giai bang DFS: " << dfs_path_len << " buoc (Ky hieu: *)\n";
            cout << "Nhan phim bat ky de quay lai...";
            _getch();
        }
    }
}

// Chức năng 6: So sánh: BFS vs DFS — đường nào ngắn hơn?
void MazeGame::compareAlgorithms() {
    solveBFS(false);
    solveDFS(false);

    system("cls");
    cout << "==================================================\n";
    cout << "         SO SANH THUAT TOAN: BFS VS DFS          \n";
    cout << "==================================================\n";
    cout << "1. Thuat toan BFS (Tim kiem theo chieu rong):\n";
    cout << "   - Chi phi duong di: " << bfs_path_len << " buoc.\n";
    cout << "   - Tinh toi uu: LUON dam bao tim ra duong ngan nhat.\n\n";

    cout << "2. Thuat toan DFS (Tim kiem theo chieu sau):\n";
    cout << "   - Chi phi duong di: " << dfs_path_len << " buoc.\n";
    cout << "   - Tinh toi uu: Khong dam bao ngan nhat vi di sau va phai luu vet quay lui.\n\n";

    cout << "--------------------------------------------------\n";
    cout << "=> KET LUAN: ";
    if (bfs_path_len < dfs_path_len) {
        cout << "BFS ngan hon DFS dung " << (dfs_path_len - bfs_path_len) << " buoc.\n";
    }
    else if (bfs_path_len == dfs_path_len) {
        cout << "Trong kich ban me cung nay, ca BFS va DFS ngau nhien cho ra cung do dai.\n";
    }
    else {
        cout << "Loi logic hoac do thi dac biet (Thuc te khong xay ra tren luoi o vuong khong trong so).\n";
    }
    cout << "==================================================\n";
    cout << "Nhan phim bat ky de ve Menu chinh...";
    _getch();
}