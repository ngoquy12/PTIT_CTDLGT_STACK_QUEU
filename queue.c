#include <stdio.h>
#include <stdlib.h>

// Khai báo cấu trúc Node
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Khai báo cấu trúc dành cho Queue
typedef struct Queue{
   Node* front;
   Node* rear;
} Queue;

// Khởi tạo hàng đợi
void initialQueue(Queue* q){
    q->front = q->rear = NULL;
}

// Kiểm tra hàng đợi có phần tử không?
int isEmpty(Queue* q){
    return q->front == NULL;
}

// Hàm tạo node mới
Node* createNode(int value){
    // Cấp phát bộ nhớ động
    Node* newNode = (Node*) malloc(sizeof (Node));

    if (!newNode){
        printf("Khong du bo nho de cap phat");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

// Thêm phần tử vào trong hàng đợi
void enqueue(Queue* q, int value){
    Node* newNode = createNode(value); /// 123453892393
    // Kiểm tra xem trong hàng đợn đã cso phần tử chưa
    if (isEmpty(q)){
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 	Lấy phần tử khỏi hàng đợi
int dequeue(Queue* q){
    // Nếu trong hàng đợi mà không có phần tử
    if (isEmpty(q)){
        printf("Hang doi rong!");
        return -1;
    }

    Node* temp  = q->front;
    int data = temp->data; // Dữ liệu của node
    q->front = temp->next;

    if (q->front == NULL){
        q->rear = NULL;
    }
    free(temp); // Giải phóng bộ nhớ

    return data;
}

// In tất cả phần tử trong queue
void printQueue(Queue* q){
    // Kiểm tra xem trong hàng đợi có phần tử không
    if (isEmpty(q)){
        printf("Hang doi rong");
        return;
    }

    Node* temp = q->front;

    while (temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

// Tính cho tôi kích thước của hàng đợi
int size(Queue* q){
    int count = 0;
    if (isEmpty(q)){
        return 0;
    }

    Node* temp = q->front;

    while (temp){
        count++;
        temp = temp->next;
    }

    return count;
}

int main(){
    Queue *q;
    initialQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);

    printQueue(&q);
    printf("\n");

    printf("So luong phan tu co trong hang doi la: %d", size(&q));

    return 0;
}