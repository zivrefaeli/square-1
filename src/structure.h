#define FACE_SIZE 8
#define QUEUE_SIZE 4

typedef enum {
    YELLOW = 'Y',
    WHITE = 'W',
    RED = 'R',
    ORANGE = 'O',
    GREEN = 'G',
    BLUE = 'B'
} Color;

typedef struct {
    int value;
    Color color;
    Color blocks[2];
} Piece;

typedef struct {
    int value;
    Color color;
} MidPiece;

typedef struct node {
    Piece *piece;
    struct node *next;
    struct node *prev;
} Node;

typedef struct {
    Node *base;
    Node *head;
} Queue;

typedef struct {
    Queue *left;
    Queue *right;
} Face;

typedef struct {
    MidPiece *left;
    MidPiece *right;
} MidFace;

typedef struct {
    Face *top;
    Face *bottom;
    MidFace *middle;
} Cube;