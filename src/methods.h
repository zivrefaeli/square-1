/* queue.h methods */

void insert(Queue *queue, Piece *piece);
Piece *pop(Queue *queue);
int size(Queue *queue);
void free_queue(Queue *queue);

/* print.h methods */

char *get_color(Color color);
int get_length(Piece *p);
int max_index(int *arr, int size);
void init_spaces(int *spaces, int maxi, int maxsize, int delta);
void print_spaces(int size);
void print_piece(Piece *p);
void display_face(Face *face, int *spaces, char slice);
void print_face(Face *face, char slice);
void print_cube(Cube *cube);

/* cube.h methods */

Piece *init_face(Face *ptr, int is_bottom);
void slice(Cube *cube);
int count_pieces(Queue *queue, int delta);
void switch_queues(Face *face);
int *is_valid_rotate(Face *face, int delta);
int is_valid_delta(int delta);
Result *rotate_face(Face *face, int delta, char *name);
void implement_rotate(Face *face, int *result);
void rotate(Cube *cube, int top, int bottom);
void free_cube(Cube *cube);