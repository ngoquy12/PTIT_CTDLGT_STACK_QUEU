#include <stdio.h>
#include <string.h>

#define MAX_TEXT 10000
#define MAX_STACK 1000

// Cấu trúc Operation
typedef struct {
    char action;
    char value;
} Operation;

// Cấu trúc Stack
typedef struct {
    Operation data[MAX_STACK];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_STACK - 1;
}

void push(Stack *s, Operation op) {
    if (!isFull(s)) {
        s->data[++s->top] = op;
    }
}

Operation pop(Stack *s) {
    Operation dummy = {'X', '\0'};
    if (!isEmpty(s)) {
        return s->data[s->top--];
    }
    return dummy;
}

void clearStack(Stack *s) {
    s->top = -1;
}

void insertChar(char text[], int *textLen, char x, Stack *undoStack) {
    if (*textLen < MAX_TEXT) {
        text[(*textLen)++] = x;
        Operation op = {'I', x};
        push(undoStack, op);
    }
}

void undo(char text[], int *textLen, Stack *undoStack, Stack *redoStack) {
    if (!isEmpty(undoStack)) {
        Operation op = pop(undoStack);
        if (op.action == 'I' && *textLen > 0) {
            (*textLen)--; // remove last char
            push(redoStack, op);
        }
    } else {
        printf("Khong co thao tac nao de hoan tac.\n");
    }
}

void redo(char text[], int *textLen, Stack *redoStack, Stack *undoStack) {
    if (!isEmpty(redoStack)) {
        Operation op = pop(redoStack);
        if (op.action == 'I') {
            insertChar(text, textLen, op.value, undoStack);
        }
    } else {
        printf("Khong co thao tac nao de khoi phuc.\n");
    }
}

void showText(char text[], int textLen) {
    if (textLen == 0) {
        printf("Stack rong\n");
    } else {
        for (int i = 0; i < textLen; i++) {
            printf("%c", text[i]);
        }
        printf("\n");
    }
}

void menu() {
    printf("\n");
    printf("=== MENU ===\n");
    printf("1. INSERT x\n");
    printf("2. UNDO\n");
    printf("3. REDO\n");
    printf("4. DISPLAY\n");
    printf("5. EXIT");
    printf("\n");
}

int main() {
    char text[MAX_TEXT];
    int textLen = 0;
    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    int choice;
    char x;

    do {
        menu();
        printf("Vui long nhap lua chon: ");
        scanf("%d", &choice);
        getchar(); // loại bỏ ký tự newline sau scanf

        switch (choice) {
            case 1:
                char buffer[100];
                printf("Nhap chuoi ky tu can INSERT: ");
                fgets(buffer, sizeof(buffer), stdin);

                // Xóa ký tự newline nếu có
                buffer[strcspn(buffer, "\n")] = '\0';

                for (int i = 0; buffer[i] != '\0'; i++) {
                    insertChar(text, &textLen, buffer[i], &undoStack);
                }
                clearStack(&redoStack);
                break;

            case 2:
                undo(text, &textLen, &undoStack, &redoStack);
                break;

            case 3:
                redo(text, &textLen, &redoStack, &undoStack);
                break;

            case 4:
                printf("Van ban hien tai: ");
                showText(text, textLen);
                break;

            case 5:
                printf("Đa thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long nhap từ 1 den 5.\n");
                break;
        }

    } while (choice != 5);

    return 0;
}
