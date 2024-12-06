#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_LINE 130
#define NUMBER_OF_CARACTER 130

struct Position {
    int x;
    int y;
};

// Prototypes des fonctions
void save_file_to_array(const char* filename, char (*buffer)[NUMBER_OF_CARACTER]);
struct Position return_position(char c, char (*buffer)[NUMBER_OF_CARACTER]);
int go_up(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);
int go_right(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);
int go_down(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);
int go_left(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter);


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
                struct Position pos;
                pos.x = i;
                pos.y = j;
                return pos;
            }
        }
    }
}

int go_up(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {

    while(x >= 0 || y >= 0 || x < NUMBER_OF_LINE || y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            counter++;
            /*printf("UP\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_right(buffer, x + 1, y, counter);
        }
        else if(counter == 174){
            printf("Going up position x: %d, y: %d", x, y);
        }
        x--;
    }
    printf("counter returned in UP : %d\n", counter);
    return counter;
}

int go_right(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {
    while(x >= 0 || y >= 0 || x < NUMBER_OF_LINE || y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            counter++;
            /*printf("RIGHT\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_down(buffer, x, y - 1, counter);
        }
        y++;
    }
    printf("counter returned in RIGHT : %d\n", counter);
    return counter;
}

int go_down(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {
    while(x >= 0 || y >= 0 || x < NUMBER_OF_LINE || y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            counter++;
            /*printf("DOWN\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter)*/;
            return go_left(buffer, x - 1, y, counter);
        }
        x++;
    }
    printf("counter returned in DOWN : %d\n", counter);
    return counter;
}

int go_left(char (*buffer)[NUMBER_OF_CARACTER], int x, int y, int counter) {
    while(x >= 0 || y >= 0 || x < NUMBER_OF_LINE || y < NUMBER_OF_CARACTER) {
        if(buffer[x][y] == '#') {
            counter++;
            /*printf("LEFT\n");
            printf("# reached at x: %d y: %d\n", x, y);
            printf("counter: %d\n", counter);*/
            return go_up(buffer, x , y +1, counter);
        }
        y--;
    }
    printf("counter returned in LEFT : %d\n", counter);
    return counter;
}