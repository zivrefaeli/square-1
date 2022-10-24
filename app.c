#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/objects.h"
#include "src/methods.h"
#include "src/queue.h"
#include "src/print.h"
#include "src/cube.h"

/*
Goals:
    -> Create the Square-1 cube using C language    | DONE
    -> Add the ability to rotate/slice the cube     | DONE
    -> Create random scramble generator             | -
    -> Create Square-1 cube solver                  | -

TODO:
    - README.md file
*/

int main() {
    /* Initialize Cube */
    Queue q1 = {NULL, NULL};
    Queue q2 = {NULL, NULL};
    Queue q3 = {NULL, NULL};
    Queue q4 = {NULL, NULL};
    MidPiece mleft = {1, RED};
    MidPiece mright = {2, RED};

    Face f1 = {&q1, &q2};
    Face f2 = {&q3, &q4};
    MidFace middle = {&mleft, &mright};

    Piece *top_pieces = init_face(&f1, 0);
    Piece *bottom_pieces = init_face(&f2, 1);
    Cube cube = {&f1, &f2, &middle};

    /* Manipulate Cube */
    Cube *square1 = &cube;

    int moves[][2] = {
        {-3, 0}, {0, 3}, {0, -3}, {0, 3}, {2, 0}, {0, 2}, 
        {-2, 0}, {4, 0}, {0, -2}, {0, 2}, {-1, 4}, {0, -3}
    };
    int length = sizeof(moves) / sizeof(int[2]);

    slice(square1);
    for (int i = 0; i < length; i++) {
        rotate(square1, moves[i][0], moves[i][1]);
        slice(square1);
    }
    rotate(square1, 0, 3);
    print_cube(square1);

    /* Free Cube */
    free_cube(square1);
    free(top_pieces);
    free(bottom_pieces);

    return 0;
}