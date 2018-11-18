#include <cmath>

using std::log2;

template<typename T>
class FibonacciHeap {
public:
    struct Node {
        T value;
        Node *left, *right, *parent, *child;
        int degree;
        bool mark;

        Node() {}
    };

public:
    Node *root;
    int size;

    FibonacciHeap() {
        root = nullptr;
        size = 0;
    }

private:

    Node *create_node(T x) {
        Node *current = new Node();
        current->value = x;
        current->left = current;
        current->right = current;
        current->parent = nullptr;
        current->child = nullptr;
        current->degree = 0;
        current->mark = false;
        return current;
    }

    Node *merge_nodes(Node *l, Node *r) {
        if (l == nullptr) {
            return r;
        }
        if (r == nullptr) {
            return l;
        }
        if (l->value > r->value) {
            std::swap(l, r);
        }
        Node *lr = l->right, *rl = r->left;
        l->right = r;
        r->left = l;
        lr->left = rl;
        rl->right = lr;
        return l;
    }

    Node *insert_node(Node *x) {
        root = merge_nodes(root, x);
        size++;
    }

    void clear(Node *x) {
        if (x != nullptr) {
            Node *i = x;
            do {
                Node *j = i;
                i = i->right;
                clear(j->child);
                delete j;
            } while (i != x);
        }
    }

    void delete_from_list(Node *x) {
        if (x->right == x) {
            return;
        }
        Node *r = x->right;
        Node *l = x->left;
        l->right = r;
        r->left = l;
    }

    void add_child_node(Node *child_node, Node *parent_node) {
        delete_from_list(child_node);
        child_node->left = child_node->right = child_node;
        child_node->parent = parent_node;
        parent_node->child = merge_nodes(parent_node->child, child_node);
        parent_node->degree++;
        child_node->mark = false;
    }

    void cut(Node *x, Node *y) {
        delete_from_list(x);
        if (x->right == x) {
            y->child = nullptr;
        } else {
            y->child = x->right;
        }
        y->degree--;
        merge_nodes(root, x);
        x->parent = nullptr;
        x->mark = false;
    }

    void cascading_cut(Node *x) {
        Node *y = x->parent;
        if (y != nullptr) {
            if (x->mark == false) {
                x->mark = true;
            } else {
                cut(x, y);
                cascading_cut(y);
            }
        }
    }

    void delete_parents(Node *x) {
        if (x == nullptr) {
            return;
        }
        Node *y = x;
        do {
            y->parent = nullptr;
            y = y->right;
        } while (y != x);
    }

    void consolidate() {
        const int magic = int(log2(size) / log2(1.618));
        Node **temp_list = new Node *[magic + 1];
        for (int i = 0; i < magic + 1; i++) {
            temp_list[i] = nullptr;
        }
        Node *temp_root = root;
        bool flag = false;
        while (true) {
            int temp_degree = temp_root->degree;
            while (temp_list[temp_degree] != nullptr) {
                Node *temp_node = temp_list[temp_degree];
                if (temp_node == temp_root) {
                    flag = true;
                    break;
                }
                if (temp_root->value > temp_node->value) {
                    std::swap(temp_root, temp_node);
                }
                add_child_node(temp_node, temp_root);
                temp_list[temp_degree++] = nullptr;
            }
            if (flag) {
                break;
            }
            temp_list[temp_root->degree] = temp_root;
            temp_root = temp_root->right;
        }
        root = temp_root;
        Node *i = temp_root;
        do {
            if (i->value < root->value) {
                root = i;
            }
            i = i->right;
        } while (i != temp_root);
        delete[]temp_list;
    }


public:

    Node *insert(T value) {
        Node *singleton = create_node(value);
        insert_node(singleton);
        return singleton;
    }

    void decrease_node_key(Node *x, T new_value) {
        x->value = new_value;
        Node *y = x->parent;
        if ((y != nullptr) && (x->value < y->value)) {
            cut(x, y);
            cascading_cut(y);
        }
        if (x->value < root->value) {
            root = x;
        }
    }

    void merge(FibonacciHeap &other) {
        root = merge_nodes(root, other.root);
        size += other.size;
        other.root = nullptr;
        other.size = 0;
        delete[] other;
    }

    bool is_empty() {
        return size == 0;
    }

    T extract_min() {
        if (root == nullptr) {
            throw std::logic_error("Can't extract minimum from empty heap");
        }
        Node *min_node = root;
        T res = root->value;
        delete_parents(min_node->child);
        merge_nodes(min_node, min_node->child);
        delete_from_list(min_node);
        if (min_node == min_node->right) {
            root = nullptr;
        } else {
            root = min_node->right;
            consolidate();
        }
        size--;
        return res;
    }

    T get_min() {
        if (root == nullptr) {
            throw std::logic_error("Can't get minimum from empty heap");
        }
        return root->value;
    }


    ~FibonacciHeap() {
        clear(root);
    }
};

//template < T> using FibonacciHeap = FibonacciHeap<T>::node*;

template<class T> using Pointer = typename FibonacciHeap<T>::Node *;
