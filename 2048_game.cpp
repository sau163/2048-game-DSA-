#include <bits/stdc++.h>
using namespace std;

int gameBoard[4][4];

int dirRow[] = {1, 0, -1, 0};  
int dirCol[] = {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPositions() {
    int occupied = 1, x, y;
    while (occupied) {
        x = rand() % 4;
        y = rand() % 4;
        if (gameBoard[x][y] == 0) {
            occupied = 0; 
        }
    }
    return make_pair(x, y); 
}


void addpiece() {
    pair<int, int> pos = generateUnoccupiedPositions();
    gameBoard[pos.first][pos.second] = 2;
}

void newGame() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gameBoard[i][j] = 0;
        }
    }
    addpiece(); 
}

void UI() {
    system("cls");  
    cout << "Game Board:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoard[i][j] == 0) {
                cout << setw(4) << "."; 
            } else {
                cout << setw(4) << gameBoard[i][j];  
            }
        }
        cout << endl;  
    }
    cout << "Commands: n: NEW GAME, w: UP, s: DOWN, d: LEFT, a: RIGHT, q: QUIT\n";
}

bool canMove(int row, int column, int nextRow, int nextColumn) {
    if (nextRow < 0 || nextRow >= 4 || nextColumn < 0 || nextColumn >= 4 ||
        (gameBoard[row][column] != gameBoard[nextRow][nextColumn] && gameBoard[nextRow][nextColumn] != 0))
        return false;
    return true;
}

void applyMovement(int direction) {
    int startRow = 0, startCol = 0, rowStep = 1, colStep = 1;
    if (direction == 0) {
        startRow = 3;
        rowStep = -1;
    }
    if (direction == 1) { 
        startCol = 3;
        colStep = -1;
    }

    // bool movePossible, canAddPiece = false;
    // do {
    //     movePossible = false;
    //     for (int i = startRow; i >= 0 && i < 4; i += rowStep) {
    //         for (int j = startCol; j >= 0 && j < 4; j += colStep) {
    //             int nextI = i + dirRow[direction], nextJ = j + dirCol[direction];
    //             if (gameBoard[i][j] && canMove(i, j, nextI, nextJ)) {
    //                 gameBoard[nextI][nextJ] += gameBoard[i][j];
    //                 gameBoard[i][j] = 0;
    //                 movePossible = canAddPiece = true;
    //             }
    //         }
    //     }
    // } while (movePossible);

    bool merged[4][4] = {};
    bool canAddPiece = false;

    for (int i = startRow; i >= 0 && i < 4; i += rowStep) {
        for (int j = startCol; j >= 0 && j < 4; j += colStep) {
            if (gameBoard[i][j] == 0) continue;
            int nextI = i + dirRow[direction], nextJ = j + dirCol[direction];

            while (nextI >= 0 && nextI < 4 && nextJ >= 0 && nextJ < 4 && gameBoard[nextI][nextJ] == 0) {
                gameBoard[nextI][nextJ] = gameBoard[i][j];
                gameBoard[i][j] = 0;
                i = nextI; 
                j = nextJ;
                nextI += dirRow[direction];
                nextJ += dirCol[direction];
                canAddPiece = true;
            }

            if (nextI >= 0 && nextI < 4 && nextJ >= 0 && nextJ < 4 &&
                gameBoard[nextI][nextJ] == gameBoard[i][j] && !merged[nextI][nextJ]) {
                gameBoard[nextI][nextJ] *= 2;
                gameBoard[i][j] = 0;
                merged[nextI][nextJ] = true;
                canAddPiece = true;
            }
        }
    }

    if (canAddPiece) {
        addpiece(); 
    }
}

int main() {
    srand(time(0));
    char commandDirection[128] = {};
    commandDirection['s'] = 0;  
    commandDirection['d'] = 1;  
    commandDirection['w'] = 2;  
    commandDirection['a'] = 3; 

    newGame();  
    while (true) {
        UI();  
        char command;
        cin >> command;

        if (command == 'n') {
            newGame();  
        } else if (command == 'q') {
            break;
        } else if (static_cast<int>(commandDirection[command]) >= 0 && static_cast<int>(commandDirection[command]) <= 3) {
            int currentDir = static_cast<int>(commandDirection[command]);
            applyMovement(currentDir);  
        } else {
            cout << "Invalid command. Try again.\n";
        }
    }
    return 0;
}
