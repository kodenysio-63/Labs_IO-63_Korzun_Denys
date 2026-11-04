<div align = "center">
  
### Національний технічний університет України
### «Київський політехнічний інститут імені Ігоря Сікорського»
### Факультет інформатики та обчислювальної техніки
### Кафедра обчислювальної техніки
<br></br>
<br></br>
<br></br>
### Структури даних та алгоритми
### Лабораторна робота №3
"Cтеки та черги"
</div>
<br></br>
<br></br>

<div align = "right">
Виконав: студент групи ІО-63
  
Корзун Денис Олегович

Номер в групі: 10

Перевірив:
</div>
<div align = "center">
Київ — 2026
</div>

## 1) Мета:
Засвоєння теоретичного матеріалу та набуття практичних навичок реалізації й застосування абстрактних структур даних стек (LIFO — «останнім прийшов, першим вийшов») та черга (FIFO — «першим прийшов, першим вийшов»), а також порівняння двох способів їхньої реалізації — на основі масиву фіксованого розміру та на основі однозв'язного списку.
## 2) Завдання: 
### Умова:
Кожен варіант завдання визначає прикладну задачу (наприклад, перевірку збалансованості дужок, обчислення постфіксного виразу тощо) та структуру(и) даних, потрібну для її розв'язання (стек, чергу, або обидві).

Для розв'язання задачі написати дві програми, що реалізують ту саму структуру даних двома способами:

на основі одновимірного масиву фіксованого розміру (з окремими змінними/індексами для вершини стека або голови й хвоста черги);
на основі однозв'язного списку (динамічне виділення пам'яті: вузол зі значенням і вказівником на наступний вузол).
Прикладна логіка (сама задача варіанта) в обох програмах має бути однаковою — відрізнятися має лише внутрішня реалізація стека/черги.

Обидві реалізації мають надавати єдиний узгоджений набір функцій, наприклад для стека: push, pop, peek, is_empty, is_full; для черги: enqueue, dequeue, peek_front, is_empty, is_full. Прикладна логіка (main і функції задачі) має викликати ці функції однаково незалежно від того, яка реалізація підключена — тобто дві програми відрізняються лише файлом/блоком, де реалізовані самі функції структури даних.

Розмір масиву для масивної реалізації взяти самостійно, достатнім для тестових прикладів (наприклад, 50–100 елементів), і оформити як іменовану константу.

Масивна реалізація черги обов'язково має бути кільцевою (циклічною): після заповнення останньої комірки масиву черга повинна продовжувати використовувати комірки, звільнені операціями dequeue, починаючи знову з початку масиву, а не вважати масив вичерпаним.
### Варіант 10:
| № | Завдання |
|---|---|
| 10 | За допомогою двох стеків («Undo» і «Redo») реалізувати історію дій текстового редактора: кожна дія — символ, доданий до рядка; Undo знімає останню дію й переносить її у стек Redo, Redo — навпаки. Вивести стан рядка після заданої послідовності дій/Undo/Redo. |
## 3) Код:
### Завдання 1 (масив):
```
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
```

### Завдання 2 (список):
```
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
```
## 4) Тестування:
### Завдання 1:
1) <img width="1946" height="1236" alt="image" src="https://github.com/user-attachments/assets/667cd3ed-9911-4f7c-86ad-b33a8e92c4c0" />

2) <img width="1974" height="1548" alt="image" src="https://github.com/user-attachments/assets/13ddce7d-7903-4b21-ab46-3e703995ef96" />

3.1) <img width="1430" height="1444" alt="image" src="https://github.com/user-attachments/assets/8e6b13fd-8ad6-46ac-bb8b-2971c2be1ec8" />

3.2) <img width="1278" height="1376" alt="image" src="https://github.com/user-attachments/assets/d1303507-c158-48fd-bf55-2dbd0865516b" />

### Завдання 2:
1) <img width="1410" height="1074" alt="image" src="https://github.com/user-attachments/assets/7ecdcdc6-f76e-4c38-a8c6-4000c20c6068" />

2) <img width="1432" height="392" alt="image" src="https://github.com/user-attachments/assets/3d44a8cb-9ce7-4e1b-a2f6-1f7cdbc20051" />

## 5) Висновок:
