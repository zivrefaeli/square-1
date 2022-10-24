#define TOP_SLICE '/'
#define BOTTOM_SLICE '\\'

char *get_color(Color color) {
    switch (color) {
        case YELLOW:
            return "Yellow";
        case WHITE:
            return "White";
        case RED:
            return "Red";
        case ORANGE:
            return "Orange";
        case GREEN:
            return "Green";
        case BLUE:
            return "Blue";
        default:
            return NULL;
    }
}

int get_length(Piece *p) {
    int length = 4;
    length += strlen(get_color(p->color));
    length += strlen(get_color(p->blocks[0]));

    if (p->value == 2) {
        length += strlen(get_color(p->blocks[1])) + 2;
    }
    return length;
}

// O(n) time | O(1) space
// where n is the length of the array
int max_index(int *arr, int size) {
    int max = arr[0], index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] >= max) {
            max = arr[i];
            index++;
        }
    }
    return index;
}

// O(n) time | O(1) space
// where n is the length of the array
void init_spaces(int *spaces, int maxi, int maxsize, int delta) {
    int i;
    for (i = maxi - 1; i >= 0; i--) {
        spaces[i] = spaces[i + 1] + delta;
    }
    for (i = maxi + 1; i < maxsize; i++) {
        spaces[i] = spaces[i - 1] - delta;
    }
}

// O(n) time | O(1) space
// where n is size
void print_spaces(int size) {
    for (int i = 0; i < size; i++) {
        printf(" ");
    }
}

void print_piece(Piece *p) {
    printf("{%s, %s", get_color(p->color), get_color(p->blocks[0]));
    if (p->value == 2) {
        printf(", %s", get_color(p->blocks[1]));
    }
    printf("}");
}

// O(n * m) time | O(1) space
// where n equals to max(length of left queue, length of right queue)
// and where m is the max item in spaces
void display_face(Face *face, int *spaces, char slice) {
    int index = 0;
    Node *l_ptr = face->left->head, *r_ptr = face->right->base;

    while (l_ptr != NULL) {
        print_spaces(spaces[index]);
        print_piece(l_ptr->piece);
        printf(" %c ", slice);

        if (r_ptr != NULL) {
            print_piece(r_ptr->piece);
            r_ptr = r_ptr->next;
        }
        printf("\n");

        l_ptr = l_ptr->prev;
        index++;
    }

    while (r_ptr != NULL) {
        print_spaces(spaces[index]);
        printf(" %c ", slice);
        print_piece(r_ptr->piece);
        printf("\n");

        r_ptr = r_ptr->next;
        index++;
    }
}

// O(n) time | O(1) space
// where n is the max item in spaces, the max of sizes is MAX_SUM - constant 
void print_face(Face *face, char slice) {
    const int delta = slice == TOP_SLICE ? 1 : -1;

    int lsize = size(face->left);
    int maxsize = size(face->right);
    if (lsize > maxsize) {
        maxsize = lsize;
    }

    // create array of pieces length
    int *l_pieces = calloc(maxsize, sizeof(int));
    Node *l_ptr = face->left->head;
    for (int i = 0; i < lsize; i++) {
        l_pieces[i] = get_length(l_ptr->piece);
        l_ptr = l_ptr->prev;
    }

    // create array of spaces
    int *spaces = calloc(maxsize, sizeof(int));
    int maxi = max_index(l_pieces, lsize), i;
    spaces[maxi] = l_pieces[maxi];
    init_spaces(spaces, maxi, maxsize, delta);

    // modify spaces relative to left pieces
    int min = 0;
    for (i = 0; i < maxsize; i++) {
        spaces[i] -= l_pieces[i];
        if (spaces[i] < min) {
            min = spaces[i];
        }
    }
    if (min < 0) {
        for (int i = 0; i < maxsize; i++) {
            spaces[i] -= min;
        }
    }

    // display result
    display_face(face, spaces, slice);
    free(l_pieces);
    free(spaces);
}

void print_middle_piece(MidPiece *p) {
    printf("{%d, %s}", p->value, get_color(p->color));
}

void print_middle(MidFace *mid) {
    printf("\n");
    print_middle_piece(mid->left);
    printf(" | ");
    print_middle_piece(mid->right);
    printf("\n\n");
}

// O(n) time | O(1) space
void print_cube(Cube *cube) {
    printf("\n");
    print_face(cube->top, TOP_SLICE);
    print_middle(cube->middle);
    print_face(cube->bottom, BOTTOM_SLICE);
    printf("\n");
}