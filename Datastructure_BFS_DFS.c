#include <stdio.h>
#include <stdbool.h>
#define ROWS 5
#define COLS 5

int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up

bool is_valid(int x, int y, int maze[ROWS][COLS], bool visited[ROWS][COLS]) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0 && !visited[x][y]);
}

bool bfs(int maze[ROWS][COLS], int start[2], int end[2], int path[ROWS * COLS][2], int *path_len) {
    int queue[ROWS * COLS][2];
    int front = 0, rear = 0;
    bool visited[ROWS][COLS] = {false};
    int parent[ROWS][COLS][2];

    queue[rear][0] = start[0];
    queue[rear][1] = start[1];
    rear++;
    visited[start[0]][start[1]] = true;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        if (x == end[0] && y == end[1]) {
            int px = x, py = y;
            *path_len = 0;
            while (!(px == start[0] && py == start[1])) {
                path[*path_len][0] = px;
                path[*path_len][1] = py;
                int temp_x = parent[px][py][0];
                int temp_y = parent[px][py][1];
                px = temp_x;
                py = temp_y;
                (*path_len)++;
            }
            path[*path_len][0] = start[0];
            path[*path_len][1] = start[1];
            (*path_len)++;
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int new_x = x + directions[i][0];
            int new_y = y + directions[i][1];

            if (is_valid(new_x, new_y, maze, visited)) {
                queue[rear][0] = new_x;
                queue[rear][1] = new_y;
                rear++;
                visited[new_x][new_y] = true;
                parent[new_x][new_y][0] = x;
                parent[new_x][new_y][1] = y;
            }
        }
    }
    return false;
}

void print_maze(int maze[ROWS][COLS], int path[ROWS * COLS][2], int path_len) {
    for (int i = 0; i < path_len; i++) {
        maze[path[i][0]][path[i][1]] = '*';
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == '*') {
                printf("* ");
            } else {
                printf("%d ", maze[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int maze[ROWS][COLS];
    int start[2], end[2];
    int path[ROWS * COLS][2];
    int path_len;

    printf("Enter the maze (5x5) row by row (0 for open path, 1 for wall):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    printf("Enter start coordinates (x y): ");
    scanf("%d %d", &start[0], &start[1]);
    printf("Enter end coordinates (x y): ");
    scanf("%d %d", &end[0], &end[1]);

    if (bfs(maze, start, end, path, &path_len)) {
        printf("Maze Solved Using BFS:\n");
        print_maze(maze, path, path_len);
    } else {
        printf("No path found.\n");
    }

    return 0;
}
