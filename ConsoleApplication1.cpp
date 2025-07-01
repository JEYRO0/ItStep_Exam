#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else 
    system("clear");
#endif
}
using namespace std;

const int COLS = 10;
const int ROWS = 10;

void Show_me(char massive[ROWS][COLS]) {

    cout << "   ";
    for (int j = 0; j < COLS; j++) {
        cout << char('A' + j) << "  ";
    }
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        if (i + 1 < 10) cout << i + 1 << "  ";
        else cout << i + 1 << " ";
        for (int j = 0; j < COLS; j++) {
            cout << massive[i][j] << "  ";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
}


bool Place_Ship(int& count, int max, int size, char s, char massive[ROWS][COLS]) {
    if (count >= max) {
        cout << "Ви вже розмістили всі кораблі цього типу." << endl;
        return false;
    }

    int row;
    char b;
    char direction;
    int col;
    clearScreen();
    Show_me(massive);
    cout << "Введіть координати початку розташування корабля (" << size << " клітини), (літера і номер): ";
    cin >> b >> row;

    cout << "Виберіть напрям (H - горизонтально, V - вертикально): ";
    cin >> direction;

    if (b >= 'A' && b <= 'J') col = b - 'A';
    else if (b >= 'a' && b <= 'j') col = b - 'a';
    else {
        cout << "Неправильна літера колонки." << endl;
        return false;
    }

    if (row < 1 || row > 10) {
        cout << "Неправильний номер рядка." << endl;
        return false;
    }

    row--;

    if (direction != 'H' && direction != 'h' && direction != 'V' && direction != 'v') {
        cout << "Неправильний напрям." << endl;
        return false;
    }

    if (direction == 'H' || direction == 'h') {
        if (col + size > COLS) {
            cout << "Корабель не вміщується по горизонталі." << endl;
            return false;
        }


        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= size; j++) {
                int checkRow = row + i;
                int checkCol = col + j;
                if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS) {
                    if (massive[checkRow][checkCol] != '.') {
                        cout << "Одна з клітин поруч із кораблем зайнята." << endl;
                        return false;
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            massive[row][col + i] = s;
        }
    }
    else {
        if (row + size > ROWS) {
            cout << "Корабель не вміщується по вертикалі." << endl;
            return false;
        }

        for (int i = -1; i <= size; i++) {
            for (int j = -1; j <= 1; j++) {
                int checkRow = row + i;
                int checkCol = col + j;
                if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS) {
                    if (massive[checkRow][checkCol] != '.') {
                        cout << "Одна з клітин поруч із кораблем зайнята." << endl;
                        return false;
                    }
                }
            }
        }

        for (int i = 0; i < size; i++) {
            massive[row + i][col] = s;
        }
    }

    cout << "Корабель успішно розміщено!" << endl;
    count++;
    return true;
}



bool Enemy_Ship(int& count, int max, int size, char s, char massive[ROWS][COLS]) {
    if (count >= max) {
        return false;
    }

    int attempts = 100000;

    while (attempts--) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        char direction = (rand() % 2 == 0) ? 'H' : 'V';

        bool canPlace = true;

        if (direction == 'H') {
            if (col + size > COLS) {
                continue;
            }

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= size; j++) {
                    int checkRow = row + i;
                    int checkCol = col + j;

                    if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS) {
                        if (massive[checkRow][checkCol] != '.') {
                            canPlace = false;
                            break;
                        }
                    }
                }
                if (!canPlace) break;
            }

            if (!canPlace) continue;

            for (int i = 0; i < size; i++) {
                massive[row][col + i] = s;
            }
        }
        else {
            if (row + size > ROWS) {
                continue;
            }

            for (int i = -1; i <= size; i++) {
                for (int j = -1; j <= 1; j++) {
                    int checkRow = row + i;
                    int checkCol = col + j;

                    if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS) {
                        if (massive[checkRow][checkCol] != '.') {
                            canPlace = false;
                            break;
                        }
                    }
                }
                if (!canPlace) break;
            }

            if (!canPlace) continue;

            for (int i = 0; i < size; i++) {
                massive[row + i][col] = s;
            }
        }

        count++;
        return true;
    }

    return false;
}


void Place_Enemy_Ships(char massive[ROWS][COLS]) {
    srand(time(0));

    int lincorn = 0, kreyser = 0, esminec = 0, sub = 0;

    while (lincorn < 1) {
        Enemy_Ship(lincorn, 1, 4, 'L', massive);
    }
    while (kreyser < 2) {
        Enemy_Ship(kreyser, 2, 3, 'K', massive);
    }
    while (esminec < 3) {
        Enemy_Ship(esminec, 3, 2, 'E', massive);
    }
    while (sub < 4) {
        Enemy_Ship(sub, 4, 1, 'S', massive);
    }
}

void Battle(char massive1[ROWS][COLS], char massive2[ROWS][COLS], char massive3[ROWS][COLS], char massive4[ROWS][COLS]) {

    const int totalEnemyCells = 20;
    const int totalPlayerCells = 20;
    int playerHits = 0;
    int enemyHits = 0;

    while (playerHits < totalEnemyCells && enemyHits < totalPlayerCells) {

        Show_me(massive3);
        cout << "Ваш хід! Введіть координати для атаки (літера і номер): ";

        char b;
        int row;
        cin >> b >> row;

        int col;
        if (b >= 'A' && b <= 'J') col = b - 'A';
        else if (b >= 'a' && b <= 'j') col = b - 'a';
        else {
            cout << "Невірна літера колонки." << endl;
            continue;
        }

        if (row < 1 || row > 10) {
            cout << "Невірний номер рядка." << endl;
            continue;
        }

        row--;

        if (massive3[row][col] == 'X' || massive3[row][col] == 'O') {
            cout << "Ви вже стріляли в ці координати!" << endl;
            continue;
        }

        if (massive2[row][col] != '.') {
            cout << "Влучили! Ви поранили корабель суперника!" << endl;
            massive3[row][col] = 'X';
            Show_me(massive3);
            playerHits++;
        }
        else {
            cout << "Промах" << endl;
            massive3[row][col] = 'O';
            Show_me(massive3);
        }

        if (playerHits >= totalEnemyCells) {
            cout << "Вітаю! Ви знищили всі кораблі суперника!" << endl;
            return;
        }

        clearScreen();
        cout << "Хід суперника..." << endl;
        Sleep(2000);

        int enemyRow, enemyCol;
        while (true) {
            enemyRow = rand() % ROWS;
            enemyCol = rand() % COLS;

            if (massive4[enemyRow][enemyCol] == 'X' || massive4[enemyRow][enemyCol] == 'O') {
                continue;
            }

            break;
        }

        if (massive1[enemyRow][enemyCol] != '.') {
            cout << "Суперник влучив по вашим координатам: " << char('A' + enemyCol) << enemyRow + 1 << endl;
            massive4[enemyRow][enemyCol] = 'X';
            Show_me(massive4);
            enemyHits++;
        }
        else {
            cout << "Суперник промахнувся по координатам: " << char('A' + enemyCol) << enemyRow + 1 << endl;
            massive4[enemyRow][enemyCol] = 'O';
            Show_me(massive4);
        }

        if (enemyHits >= totalPlayerCells) {
            cout << "суперник знищив всі ваші кораблі. Ви програли." << endl;
            return;
        }
    }
}



int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    char massive[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            massive[i][j] = '.';
        }
    }
    char massive2[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            massive2[i][j] = '.';
        }
    }

    char massive3[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            massive3[i][j] = '.';
        }
    }

    char massive4[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            massive4[i][j] = '.';
        }
    }

    int choice = 0;
    int lincorn = 0, kreyser = 0, esminec = 0, sub = 0;
    int totalPlaced = 0;

    while (totalPlaced < 10) {
        Show_me(massive);
        cout << "Доступні кораблі: " << endl;
        cout << "1. Лінкор (4 клітини) - 1 шт." << endl;
        cout << "2. Крейсер (3 клітини) - 2 шт." << endl;
        cout << "3. Есмінець (2 клітини) - 3 шт." << endl;
        cout << "4. Субмарина (1 клітина) - 4 шт." << endl;
        cout << "Введіть свій вибір (1-4): ";

        cin >> choice;
        clearScreen();

        bool placed = false;
        if (choice == 1) {
            placed = Place_Ship(lincorn, 1, 4, 'L', massive);
        }
        else if (choice == 2) {
            placed = Place_Ship(kreyser, 2, 3, 'K', massive);
        }
        else if (choice == 3) {
            placed = Place_Ship(esminec, 3, 2, 'E', massive);
        }
        else if (choice == 4) {
            placed = Place_Ship(sub, 4, 1, 'S', massive);
        }
        else {
            cout << "Невірний вибір." << endl;
        }

        if (placed) totalPlaced++;

    }

    cout << "Всі кораблі успішно розміщено" << endl;
    Show_me(massive);
    Sleep(2000);
    cout << "Суперник розташовує свої кораблі..." << endl;
    Sleep(2000);
    Place_Enemy_Ships(massive2);
    cout << "Суперник розташував свої кораблі" << endl;
    Show_me(massive3);
    Battle(massive, massive2, massive3, massive4);






    return 0;
}