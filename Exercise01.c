#include <stdio.h>
#include <string.h>
#define MAX_CHARACTER 1000

// Hàm hiển thị menu chức năng
void showMenu(){
    printf("\n");
    printf("=== MENU UNDO & REDO ===\n");
    printf("1. INSERT X\n");
    printf("2. UNDO\n");
    printf("3. REDO\n");
    printf("4. DISPLAY\n");
    printf("5. EXIT\n");
    printf("\n");
}

// Khai báo cấu trúc danh cho Operation Tiến trình)
typedef struct Operation {
    char action; // Đại diện cho hành động
    char value; // Chuỗi nguười dùng nhập
} Operation;

// Khai báo cấu trúc dành cho Stack
typedef struct Stack {
    Operation data[MAX_CHARACTER];
    int top;
} Stack;

// Một số thao tác với Stack
// 1. Thao tác khởi tạo Stack
void initialStack(Stack *s){
    s->top = -1;
}

// 2. Thao tác kiểm tra Stack rỗng hay không?
int isEmpty(Stack *s){
    return s->top == -1;
}

// 3. Thao tác kiểm tra xem Stack đã đầy chưa
int isFull(Stack *s){
    return s->top == MAX_CHARACTER - 1;
}

// 4. Thao tác thêm phần tử vào trong Stack
void push(Stack *s, Operation op){
    if (!isFull(s)){
        // Thêm phần tử vào trong ngăn xếp
        s->data[++s->top] = op;
    }
}

// 5. Thao tác lấy phần tử trên cùng của Stack
Operation pop(Stack *s){
    if (!isEmpty(s)){
       return s->data[s->top--];
    }
}

// 6. Hàm xóa giá trị của Stack trước khi INSERT mới
void clearStack(Stack *s){
    s->top = -1;
}

// 7. Thao tác INSERT (Thêm ký tự x vào cuối văn bản)
void insertChar(char text[], char x, int *length, Stack* undoStack){
    // Kiểm tra xem trong mảng ký tự còn đủ bộ nhớ không?
    if (*length < MAX_CHARACTER){
        text[(*length)++] = x; // Thêm phần tử vào trong text

        // Khai báo thao tác
        Operation op = {'I', x};

        // Push phần tử vào undoStack
        push(undoStack, op);
    }
}

// 8. Thao tác UNDO (Hoàn tác thao tác gần nhất (xóa ký tự cuối chuỗi))
void undo(char text[], int *length, Stack *undoStack, Stack *redoStack){
    // Logic: Xóa ký tự cuối chuỗi
    if (!isEmpty(undoStack)){
        Operation op = pop(undoStack); // Lấy ra ký tự cuối

        // Thêm ký tự vừa xóa vào trong redoStack
        if (op.action == 'I' && *length > 0){
            // Giam length đi 1
            (*length)--;
            push(redoStack, op);
        }
    } else {
        printf("Khong co thao tac nao hoan tat");
        return;
    }
}

// 9. Thao tác REDO (Khôi phục thao tác vừa UNDO)
void redo(char text[], int *length, Stack *undoStack, Stack *redoStack){
    if (!isEmpty(redoStack)){
        // Lấy ra ký tự lưu trữ trong redoStack
        Operation op = pop(redoStack);

        if (op.action == 'I'){
            insertChar(text, op.value, length, undoStack);
        }
    } else {
        printf("Khong có thao tac nao de khoi phuc");
        return;
    }
}

// 10 . Thao tác in ra chuỗi hiện tại
void showText(char text[], int length){
    printf("Length %d", length);
    if (length == 0){
        printf("Chuoi rong!");
        return;
    }

    for (int i = 0; i < length; i++) {
        printf("%c", text[i]);
    }
    printf("\n");
}

int main(){
    int choice;
    char text[MAX_CHARACTER];
    int length = 0;
    char x[MAX_CHARACTER];
    Stack undoStack, redoStack;
    // Khởi tạo 2 Stack
    initialStack(&undoStack);
    initialStack(&redoStack);

    do {
        showMenu();
        printf("Vui long nhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Vui long nhap ky tu: ");
                fgets(x, sizeof (x), stdin);
                x[strcspn(x, "\n")] = '\0';

                for (int i = 0; x[i] != '\0'; i++) {
                    insertChar(text, x[i], &length, &undoStack);
                }
                break;
            case 2:
                undo(text, &length, &undoStack, &redoStack);
                break;
            case 3:
                redo(text, &length, &undoStack, &redoStack);
                break;
            case 4:
                showText(text, length);
                break;
            case 5:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
                break;
        }

    } while (choice != 5);

    return 0;
}