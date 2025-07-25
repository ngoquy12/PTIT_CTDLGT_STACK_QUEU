#include <stdio.h>
#define MAX 100

// Khai báo cấu trúc dành cho Stack
typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

// Hàm khởi tạo Stack
void initialStack(Stack* s){
    s->top = -1;
}

// Hàm kiểm tra xem Stack có bị rỗng không
int isEmpty(Stack* s){
    return s->top == -1;
}

// Hàm kiểm tra xem Stack đã đầy chưa
int isFull(Stack* s){
    return s->top == MAX - 1;
}

// Hàm thêm phần tử vào Stack
void push(Stack* s, int value){
    // Kiểm tra xem Stack đã đầy chưa
    if (isFull(s)){
        printf("Ngan xep da day!");
        return;
    }

    // Thêm phần tử vào ngăn xếp
    s->items[++(s->top)] = value;

    printf("Them phan tu vao trong ngan xep thanh cong \n");
}

// Hàm lấy ra phần tử trên cùng của Stack - và sẽ xóa đi sau khi lấy
int pop(Stack* s){
    // Kiểm tra xem ngăn xếp có phần tử không?
    if (isEmpty(s)){
        printf("Ngan xep bi rong");
        return -1;
    }

    // Trả về phần tử nằm trên đỉnh và xóa đi
    return s->items[s->top--];
}

// Hàm lấy ra phần tử trên cùng của Stack - và sẽ không xóa đi sau khi lấy
int peek(Stack* s){
    // Kiểm tra xem ngăn xếp có phần tử không?
    if (isEmpty(s)){
        printf("Ngan xep bi rong");
        return -1;
    }

    // Trả về phần tử nằm trên đỉnh và không xóa đi
    return s->items[s->top];
}

// Hàm in ra các phần tử có trong ngăn xếp
void printStack(Stack* s){
    // Nếu ngăn xếp không có phần tử
    if (isEmpty(s)){
        printf("Ngan xep rong!");
        return;
    }
    printf("Cac phan tu co trong Stack: \n");
    for (int i = s->top; i >= 0 ; i--) {
        printf("%d ", s->items[i]);
    }
}

int main(void) {
    Stack* s;
    initialStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);

    printf("1. %d \n", pop(&s)); // 40
    printf("2. %d \n", peek(&s)); // 30
    printf("3. %d \n", peek(&s)); //

    printStack(&s);

    return 0;
}