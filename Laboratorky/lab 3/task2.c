#include <stdio.h>
#include <stdlib.h> 

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void init(Stack *s) { s->top = NULL; }
int is_empty(Stack *s) { return s->top == NULL; }
int is_full(Stack *s) { return 0; } 

void push(Stack *s, char c) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Нестача пам'яті!\n");
        return;
    }
    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(Stack *s) {
    if (is_empty(s)) {
        printf("Стек порожній!\n");
        return '\0';
    }
    Node *temp = s->top;
    char val = temp->data;
    s->top = s->top->next;
    free(temp); 
    return val;
}

char peek(Stack *s) {
    return is_empty(s) ? '\0' : s->top->data;
}

void print_nodes(Node *node) {
    if (!node) return;
    print_nodes(node->next);
    printf("%c", node->data);
}

void print_stack(Stack *s) {
    printf("Поточний рядок: \"");
    print_nodes(s->top);
    printf("\"\n");
}

int main() {
    Stack undo, redo;
    init(&undo);
    init(&redo);

    char c;
    printf("Вводьте символи (1 - Undo, 2 - Redo, 0 - вихід):\n");

    while (scanf(" %c", &c) == 1 && c != '0') {
        if (c == '1') {
            if (!is_empty(&undo)) push(&redo, pop(&undo));
            else pop(&undo);
        } 
        else if (c == '2') {
            if (!is_empty(&redo)) push(&undo, pop(&redo));
            else pop(&redo);
        } 
        else {
            push(&undo, c);
            while (!is_empty(&redo)) pop(&redo);
        }
        print_stack(&undo);
    }

    return 0;
}