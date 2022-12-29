#include <iostream>

class Node {
public:
    Node *right;
    Node *left;
    int height;
    int value;

    Node() {
        right = nullptr;
        left = nullptr;
        height = 1;
    }

    Node(int x) {
        right = nullptr;
        left = nullptr;
        height = 1;
        value = x;
    }
};

void fixHeight(Node *a) {

    int l = 0;
    int r = 0;
    if (a->left != nullptr) {
        l = a->left->height;
    }
    if (a->right != nullptr) {
        r = a->right->height;
    }
    a->height = std::max(r, l) + 1;
}

void rotateL(Node *a) {
    std::swap(a->value, a->right->value);
    Node *b = a->right;
    Node *A = a->left;
    Node *B = b->left;
    Node *C = b->right;

    a->left = b;
    a->right = C;
    b->left = A;
    b->right = B;

    fixHeight(b);
    fixHeight(a);
}

void rotateR(Node *a) {
    std::swap(a->value, a->left->value);
    Node *b = a->left;
    Node *A = b->left;
    Node *B = b->right;
    Node *C = a->right;

    a->right = b;
    a->left = A;
    b->left = B;
    b->right = C;

    fixHeight(b);
    fixHeight(a);
}

int height(Node *a) {
    if (a == nullptr)
        return 0;
    return a->height;
}


Node *balance(Node *a) {
    if (a == nullptr) {
        return nullptr;
    }
    fixHeight(a);
    int diff = height(a->left) - height(a->right);
    if (diff == -2) {
        diff = height(a->right->left) - height(a->right->right);
        if (diff > 0) {
            rotateR(a->right);
        }
        rotateL(a);
    } else if (diff == 2) {
        diff = height(a->left->left) - height(a->left->right);
        if (diff < 0) {
            rotateL(a->left);
        }
        rotateR(a);
    }
    return a;
}

Node *find(Node *st, int x) {
    if (st == nullptr || st->value == x)
        return st;

    if (x < st->value) {
        return find(st->left, x);
    } else {
        return find(st->right, x);
    }
}

Node *insert(Node *st, int x) {
    if (st == nullptr) {
        return new Node(x);
    } else if (st->value < x) {
        st->right = insert(st->right, x);
    } else if (st->value > x) {
        st->left = insert(st->left, x);
    }
    return balance(st);
}

Node *remove(Node *st, int x) {
    if (st == nullptr) {
        return nullptr;
    }
    if (st->value < x) {
        st->right = remove(st->right, x);
    } else if (st->value > x) {
        st->left = remove(st->left, x);
    } else if (st->right != nullptr && st->left != nullptr) {
        Node *temp = st->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }//поиск минимального после узла
        st->value = temp->value;
        st->right = remove(st->right, temp->value);
    } else {
        if (st->left != nullptr) {
            st = st->left;
        } else if (st->right != nullptr) {
            st = st->right;
        } else {
            st = nullptr;
        }
    }
    return balance(st);
}

int main() {
    int n;
    std::cin >> n;

    Node st;
    Node *first = &st;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (i == 0) {
            first->value = x;
        } else {
            first = insert(first, x);
        }
    }

    remove(first, 6);
    remove(first, 5);


    std::cout << "hell";

    return 0;
}
