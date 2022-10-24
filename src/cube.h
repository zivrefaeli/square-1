#define MAX_SUM 6
#define TOP "Top"
#define BOTTOM "Bottom"
#define DELTA_ERROR "Error: delta is out of range [-6, 6]\n"
#define ROTATE_ERROR "Error: can't rotate cube in current state\n"

Piece *init_face(Face *ptr, int is_bottom) {
    Piece *pieces = calloc(FACE_SIZE, sizeof(Piece));
    Color color = YELLOW;
    Color colors[] = {RED, GREEN, ORANGE, BLUE, RED};
    if (is_bottom) {
        color = WHITE;
        colors[0] = ORANGE;
        colors[2] = RED;
        colors[4] = ORANGE;
    }

    int index = 0, j;
    for (int i = 0; i < FACE_SIZE; i++) {
        j = is_bottom ? index : i / 2;

        if (i % 2 == is_bottom) {
            pieces[i] = (Piece){1, color, {colors[j]}};
        } else {
            pieces[i] = (Piece){2, color, {colors[j], colors[j + 1]}};
            index++;
        }

        insert(i >= QUEUE_SIZE ? ptr->left : ptr->right, &pieces[i]);
    }
    return pieces;
}

void slice(Cube *cube) {
    Queue *temp;
    temp = cube->top->right;
    cube->top->right = cube->bottom->right;
    cube->bottom->right = temp;

    MidPiece *r = cube->middle->right;
    if (r->color == RED) {
        r->color = ORANGE;
    } else {
        r->color = RED;
    }
    r->value = 3 - r->value;
    printf("/\n");
}

// O(1) time | O(1) space
// the max amount of nodes' pieces sums up to delta is MAX_SUM - constant
int count_pieces(Queue *queue, int delta) {
    int sum = 0, count = 0;

    Node *ptr = queue->head;
    while (sum < delta) {
        sum += ptr->piece->value;
        ptr = ptr->prev;
        count++;
    }

    if (sum == delta) {
        return count;
    }
    return 0;
}

void switch_queues(Face *face) {
    Queue *temp = face->right;
    face->right = face->left;
    face->left = temp;
}

int *is_valid_rotate(Face *face, int delta) {
    int neg_delta = delta < 0;
    if (neg_delta) {
        switch_queues(face);
        delta += MAX_SUM;
    }

    int l_count = count_pieces(face->left, delta);
    int r_count = count_pieces(face->right, delta);

    if (l_count && r_count) {
        int *arr = calloc(2, sizeof(int));
        arr[0] = l_count;
        arr[1] = r_count;
        return arr;
    }
    if (neg_delta) {
        switch_queues(face);
    }
    return NULL;
}

int is_valid_delta(int delta) {
    return -MAX_SUM <= delta && delta <= MAX_SUM;
}

Result *rotate_face(Face *face, int delta, char *name) {
    Result *result = malloc(sizeof(Result));
    result->valid = 0;
    result->ptr = NULL;

    if (!is_valid_delta(delta)) {
        printf("%s %s", name, DELTA_ERROR);
        return result;
    }

    switch (delta) {
        case MAX_SUM:
        case -MAX_SUM:
            switch_queues(face);
        case 0:
            result->valid = 1;
            break;
        default:
            int *ptr = is_valid_rotate(face, delta);
            if (ptr == NULL) {
                printf("%s %s", name, ROTATE_ERROR);
            } else {
                result->valid = 1;
                result->ptr = ptr;
            }
    }
    return result;
}

void implement_rotate(Face *face, int *result) {
    int i;
    for (i = 0; i < result[0]; i++) {
        insert(face->right, pop(face->left));
    }
    for (i = 0; i < result[1]; i++) {
        insert(face->left, pop(face->right));
    }
}

void rotate(Cube *cube, int top, int bottom) {
    Result *top_result = rotate_face(cube->top, top, TOP);
    Result *bottom_result = rotate_face(cube->bottom, bottom, BOTTOM);

    if (top_result->valid && bottom_result->valid) {
        if (top_result->ptr != NULL) {
            implement_rotate(cube->top, top_result->ptr);
        }
        if (bottom_result->ptr != NULL) {
            implement_rotate(cube->bottom, bottom_result->ptr);
        }
        printf("(%d, %d)\n", top, bottom);
    }

    free(top_result);
    free(bottom_result);
}

// O(n) time | O(1) space
void free_cube(Cube *cube) {
    free_queue(cube->top->left);
    free_queue(cube->top->right);
    free_queue(cube->bottom->left);
    free_queue(cube->bottom->right);
}