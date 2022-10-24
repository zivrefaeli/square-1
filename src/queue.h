void insert(Queue *queue, Piece *piece) {
    Node *p = malloc(sizeof(Node));

    p->piece = piece;
    p->next = queue->base;
    p->prev = NULL;

    if (queue->base == NULL) {
        queue->head = p;
    } else {
        queue->base->prev = p;
    }
    queue->base = p;
}

Piece *pop(Queue *queue) {
    if (queue->head == NULL) {
        return NULL;
    }
    Node *prev = queue->head->prev;
    Piece *piece = queue->head->piece;

    if (prev == NULL) {
        free(queue->head);
        queue->base = NULL;
        queue->head = NULL;
    } else {
        free(prev->next);
        prev->next = NULL;
        queue->head = prev;
    }
    return piece;
}

// O(n) time | O(1) space
// where n is the length of the queue
int size(Queue *queue) {
    int count = 0;
    Node *ptr = queue->base;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}

// O(n) time | O(1) space
// where n is the length of the queue
void free_queue(Queue *queue) {
    Node *ptr = queue->base, *next;
    while (ptr != NULL) {
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
}