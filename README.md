# 🎮 CLI Maze Game - Trò Chơi Mê Cung Trên Terminal

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

Một trò chơi mê cung giao diện dòng lệnh (CLI) được viết bằng **C++**. Dự án sử dụng thuật toán cải tiến để tự động tạo mê cung ngẫu nhiên không trùng lặp, hỗ trợ người chơi tự giải hoặc xem máy tự động giải thông qua các thuật toán tìm kiếm phổ biến như **BFS** và **DFS**.

---

## ✨ Các Tính Năng Nổi Bật

| Chức năng | Thuật toán sử dụng | Chi tiết |
| :--- | :--- | :--- |
| **🔨 Tạo mê cung** | `Recursive Backtracker` (DFS) | Đảm bảo mỗi mê cung sinh ra là **duy nhất**, hoàn hảo (không có vòng lặp vô hạn) và luôn có đường thoát. |
| **🕹️ Chế độ chơi** | Nhập liệu thời gian thực (`_getch`) | Di chuyển mượt mà bằng cụm phím quen thuộc `W` `A` `S` `D`. |
| **🔍 Tự động giải (BFS)**| `Breadth-First Search` | Tìm kiếm theo chiều rộng, **luôn đảm bảo** tìm ra con đường ngắn nhất đi tới đích. |
| **🌲 Tự động giải (DFS)**| `Depth-First Search` | Tìm kiếm theo chiều sâu, khám phá mê cung bằng cơ chế lưu vết nâng cao. |
| **📊 Bảng so sánh** | Thống kê số bước chân | Đối sánh trực quan hiệu năng, số bước đi giữa hai thuật toán BFS và DFS trên cùng một kịch bản lưới. |
| **⚙️ Tùy chỉnh độ khó**| Thuật toán căn chỉnh số lẻ | Tự do thay đổi kích thước chiều rộng/chiều cao của mê cung trực tiếp từ menu. |

---

## 📸 Giao Diện Ký Tự (ASCII Art) Dự Kiến

Khi khởi chạy, bản đồ mê cung sẽ hiển thị vuông vắn nhờ sử dụng kỹ thuật ký tự kép (`##` làm tường, `P` là người chơi, `.` hoặc `*` là đường đi tự giải):

```text
## ## ## ## ## ## ## ## ## ## ##
## P        ##          ##    ##
## ## ##    ##    ## ## ##    ##
##          ##    ##          ##
##    ## ## ##    ## ## ## ## ##
##    ##          ## .  .  .  ##
## ## ## ## ##    ## . ## ## ##
##                ## .  .  .  ##
## ## ## ## ## ## ## ## ## . ##
##                         .  E
## ## ## ## ## ## ## ## ## ## ##


Để hiểu cách máy tính nhìn nhận mê cung, chúng ta phải chuyển dịch bài toán từ các ô vuông trực quan sang Lý thuyết đồ thị (Graph Theory). Mô hình hóa Đồ thị Lưới (Grid Graph)Mê cung bản chất là một đồ thị vô hướng, không trọng số $G = (V, E)$, trong đó:$V$ (Tập các đỉnh): Là các ô đường đi trống (Path cells). Với kích thước lưới $W \times H$, số đỉnh tối đa trong lòng mê cung là $|V| = \frac{W-1}{2} \times \frac{H-1}{2}$.$E$ (Tập các cạnh): Đại diện cho các đoạn tường được phá bỏ, kết nối hai ô trống cạnh nhau. Mỗi đỉnh có bậc tối đa là 4 ($\text{deg}(v) \le 4$). Bản chất toán học của "Mê cung hoàn hảo" (Perfect Maze)Thuật toán Recursive Backtracker thực chất là một thuật toán tìm Cây bao trùm (Spanning Tree) ngẫu nhiên. Một mê cung được gọi là "hoàn hảo" khi và chỉ khi đồ thị $G$ thỏa mãn các tính chất của một cấu trúc Cây (Tree):Tính liên thông (Connected): Luôn tồn tại đường đi giữa hai đỉnh bất kỳ. Điều này đảm bảo người chơi đứng ở đâu cũng có thể đi tới đích.Không có chu trình (Acyclic): Không có vòng lặp vô hạn, không có đảo đá biệt lập.Số cạnh tối ưu: Tổng số cạnh luôn tuân thủ nghiêm ngặt công thức $|E| = |V| - 1$.Khi bạn chạy BFS hay DFS để giải một mê cung hoàn hảo, bản chất là bạn đang duyệt trên một cây. Đường đi từ gốc Start đến lá Target là duy nhất.

