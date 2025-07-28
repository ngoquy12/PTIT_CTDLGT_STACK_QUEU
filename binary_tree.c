#include <stdio.h>
#include <stdlib.h>

// Cấu trúc nút BST
typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// ================== HÀM XỬ LÝ CÂY ==================

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        printf("Đã thêm giá trị %d vào cây.\n", value);
        return createNode(value);
    }
    if (value == root->value) {
        printf("Giá trị đã tồn tại!\n");
    } else if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

Node* findMin(Node* node) {
    while (node->left != NULL) node = node->left;
    return node;
}

Node* delete(Node* root, int value) {
    if (root == NULL) {
        printf("Không tìm thấy giá trị để xóa.\n");
        return NULL;
    }
    if (value < root->value) {
        root->left = delete(root->left, value);
    } else if (value > root->value) {
        root->right = delete(root->right, value);
    } else {
        // Tìm thấy nút cần xóa
        if (root->left == NULL && root->right == NULL) {
            free(root);
            printf("Đã xóa giá trị %d khỏi cây.\n", value);
            return NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            printf("Đã xóa giá trị %d khỏi cây.\n", value);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            printf("Đã xóa giá trị %d khỏi cây.\n", value);
            return temp;
        } else {
            Node* successor = findMin(root->right);
            root->value = successor->value;
            root->right = delete(root->right, successor->value);
        }
    }
    return root;
}

void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);
}

int countLeaves(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int treeHeight(Node* root) {
    if (root == NULL) return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ================== MAIN ==================
void menu() {
    printf("\n——— BINARY SEARCH TREE MANAGER ———\n");
    printf("1. THÊM GIÁ TRỊ\n");
    printf("2. XÓA GIÁ TRỊ\n");
    printf("3. DUYỆT GIÁ TRỊ (Inorder)\n");
    printf("4. ĐẾM LÁ\n");
    printf("5. CHIỀU CAO\n");
    printf("6. THOÁT\n");
    printf("Chọn chức năng (1–6): ");
}

int main() {
    Node* root = NULL;
    int choice, x;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập giá trị cần thêm: ");
                scanf("%d", &x);
                root = insert(root, x);
                break;

            case 2:
                printf("Nhập giá trị cần xóa: ");
                scanf("%d", &x);
                root = delete(root, x);
                break;

            case 3:
                printf("Duyệt cây theo thứ tự giữa (Inorder): ");
                if (root == NULL) {
                    printf("(Cây rỗng)\n");
                } else {
                    inorder(root);
                    printf("\n");
                }
                break;

            case 4:
                printf("Số lượng lá trong cây: %d\n", countLeaves(root));
                break;

            case 5:
                printf("Chiều cao của cây: %d\n", treeHeight(root));
                break;

            case 6:
                printf("Đã thoát chương trình.\n");
                freeTree(root);
                break;

            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn 1–6.\n");
                break;
        }

    } while (choice != 6);

    return 0;
}
