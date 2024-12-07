#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_LINE 130
#define NUMBER_OF_CARACTER 130
#define MAX_DEPTH 20000000

struct Position {
    int x;
    int y;
};

int array[30000][2];

// Prototypes des fonctions
void save_file_to_array(const char* filename, char (*buffer)[NUMBER_OF_CARACTER]);
struct Position return_position(char c, char (*buffer)[NUMBER_OF_CARACTER]);
int go_up(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);
int go_right(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);
int go_down(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);
int go_left(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);

bool find_up(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth);
bool find_right(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth);
bool find_down(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth);
bool find_left(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth);

bool is_unique(int x, int y, int counter);

int main() {
    const char* filename = "input.txt";
    char buffer[NUMBER_OF_LINE][NUMBER_OF_CARACTER];
    
    printf("Save file to array\n");
    save_file_to_array(filename, buffer);

   

    struct Position pos = return_position('^', buffer);

    printf("Calculate postion\n");
    int resultat = go_up(buffer, pos.x, pos.y, 0);

    printf("Resultat: %d\n", resultat);

    /*for(int i = 0; i < NUMBER_OF_LINE; i++) {
        for(int j = 0; j < NUMBER_OF_CARACTER; j++) {
            printf("%c", buffer[i][j]);
        }
        printf("\n");
    }*/
    

    
    return 0;
}


void save_file_to_array(const char* filename, char (*buffer)[NUMBER_OF_CARACTER]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    int c;
    int l_counter = 0;
    int c_counter = 0;

    while ((c = fgetc(file)) != EOF) {
        // Process each character here
        if(c == '\n') {
            l_counter++;
            c_counter = 0;
        }
        else {
            buffer[l_counter][c_counter] = (char)c;
            c_counter++;
        }
    }
    fclose(file);
}

struct Position return_position(char c, char (*buffer)[NUMBER_OF_CARACTER]) {
    for(int i = 0; i < NUMBER_OF_LINE; i++) {
        for(int j = 0; j < NUMBER_OF_CARACTER; j++) {
            if(buffer[i][j] == c) {
                buffer[i][j] = '.';
                struct Position pos;
                pos.x = i;
                pos.y = j;
                return pos;
            }
        }
    }
}

int go_up(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {

    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            /*printf("UP\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_right(buffer, x + 1, y, counter);
        }
        else{
            if(find_right(buffer, x, y, 0) && is_unique(x, y, counter)) {
            counter++;
            printf("LOOP found in UP counter = %d\n", counter);
            }

            if(buffer[x][y] == '.'){
                buffer[x][y] = 'U';
                x--;
            }
            else {
                x--;
            }
        }
        
    }
    return counter;
}

int go_right(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {
    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
           /* printf("RIGHT\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_down(buffer, x, y - 1, counter);
        }
        else{
            if(find_down(buffer, x, y, 0) && is_unique(x, y, counter)) {
            counter++;
            printf("LOOP found in RIGHT counter = %d\n", counter);
            }

            if(buffer[x][y] == '.'){
                buffer[x][y] = 'R';
                y++;
            }
            else {
                y++;
            }
        }
    }
    return counter;
}

int go_down(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {
    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
           /*printf("DOWN\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_left(buffer, x - 1, y, counter);
        }
        else{
            if(find_left(buffer, x, y, 0) && is_unique(x, y, counter)) {
            counter++;
            printf("LOOP found in DOWN counter = %d\n", counter);
            }

            if(buffer[x][y] == '.'){
                buffer[x][y] = 'D';
                x++;
            }
            else {
                x++;
            }
        }
    }
    return counter;
}

int go_left(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {
    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            /*printf("LEFT\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_up(buffer, x , y +1, counter);
        }
        else{
            if(find_up(buffer, x, y, 0) && is_unique(x, y, counter)) {
            counter++;
            printf("LOOP found in LEFT counter = %d\n", counter);
            }

            if(buffer[x][y] == '.'){
                buffer[x][y] = 'L';
                y--;
            }
            else {
                y--;
            }
        }
    }
    return counter;
}

bool find_up(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth) {
    if (depth > MAX_DEPTH) { // prevent infinite recursion
        return false;
    }

    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            return find_right(buffer, x + 1, y, depth + 1);
        }
        else if(buffer[x][y] == 'U') {
            return true;
        }
        else {
            x--;
        }
    }
    return false;
}

bool find_right(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth) {
   if (depth > MAX_DEPTH) { // prevent infinite recursion
        return false;
    }

    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            return find_down(buffer, x, y-1, depth + 1);
        }
        else if(buffer[x][y] == 'R') {
            return true;
        }
        else {
            y++;
        }
    }
    return false;
}

bool find_down(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth) {
    if (depth > MAX_DEPTH) { // prevent infinite recursion
        return false;
    }

    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            return find_left(buffer, x - 1, y, depth + 1);
        }
        else if(buffer[x][y] == 'D') {
            return true;
        }
        else {
            x++;
        }
    }
    return false;
}

bool find_left(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int depth) {
    if (depth > MAX_DEPTH) { // prevent infinite recursion
        return false;
    }

    while(x >= 0 && y >= 0 && x < NUMBER_OF_LINE && y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            return find_up(buffer, x, y +1, depth + 1);
        }
        else if(buffer[x][y] == 'L') {
            return true;
        }
        else {
            y--;
        }
    }
    return false;
}

bool is_unique(int x, int y, int counter) {
    for(int i = 0; i < counter; i++) {
        if(array[i][0] == x && array[i][1] == y) {
            return false;
        }
    }
    array[counter][0] = x;
    array[counter][1] = y;
    return true;
}