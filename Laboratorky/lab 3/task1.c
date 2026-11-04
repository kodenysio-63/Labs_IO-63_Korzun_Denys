#include <stdio.h>

#define MAX_CAP 50 

typedef struct {
    char items[MAX_CAP];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
int is_empty(Stack *s) { return s->top == -1; }
int is_full(Stack *s) { return s->top == MAX_CAP - 1; }

void push(Stack *s, char c) {
    if (is_full(s)) {
        printf("Стек повний!\n");
        return;
    }
    s->items[++s->top] = c;
}

char pop(Stack *s) {
    if (is_empty(s)) {
        printf("Стек порожній!\n");
        return '\0';
    }
    return s->items[s->top--];
}

char peek(Stack *s) {
    return is_empty(s) ? '\0' : s->items[s->top];
}

void print_stack(Stack *s) {
    printf("Поточний рядок: \"");
    for (int i = 0; i <= s->top; i++) printf("%c", s->items[i]);
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