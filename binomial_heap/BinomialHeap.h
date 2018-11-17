using std::max;
using std::swap;

template<typename T>
class BinomialHeap {
private:
    Vector<BinomialHeap<T> *> nodes;
    T value;
    int degree;
    BinomialHeap<T> *parent;
    int minimum_position = -1;

    void update_minimum() {
        minimum_position = -1;
        if (nodes.get_size() == 0) {
            minimum_position = -1;
        } else {
            for (int i = 0; i < nodes.get_size(); i++) {
                if ((minimum_position == -1) || (nodes[i]->value < nodes[minimum_position]->value)) {
                    minimum_position = i;
                }
            }
        }
    }

public:
    int size;

    BinomialHeap() : parent(NULL), size(0) {}

    BinomialHeap(T x) : value(x), degree(0), parent(NULL), size(0) {}

    void merge(BinomialHeap<T> *other) {
        Vector<BinomialHeap<T> *> carry;
        int i = 0, j = 0;
        while ((i < size) && (j < other->size)) {
            if (nodes[i]->degree < other->nodes[j]->degree) {
                carry.push_back(nodes[i]);
                i++;
            } else {
                carry.push_back(other->nodes[j]);
                j++;
            }
        }
        while (i < nodes.get_size()) {
            carry.push_back(nodes[i]);
            i++;
        }
        while (j < other->nodes.get_size()) {
            carry.push_back(other->nodes[j]);
            j++;
        }
        nodes.clear();
        for (int k = 0; k < carry.get_size(); k++) {
            if ((k < carry.get_size() - 1) && (carry[k]->degree == carry[k + 1]->degree)) {
                BinomialHeap<T> *current_node, *next_node;
                if (carry[k]->value < carry[k + 1]->value) {
                    current_node = carry[k];
                    next_node = carry[k + 1];
                } else {
                    current_node = carry[k + 1];
                    next_node = carry[k];
                }
                next_node->parent = current_node;
                current_node->nodes.push_back(next_node);
                current_node->degree = max(current_node->degree, next_node->degree + 1);
                carry[k + 1] = current_node;
            } else {
                if ((k < carry.get_size() - 1) && (carry[k]->degree > carry[k + 1]->degree)) {
                    swap(carry[k], carry[k + 1]);
                    k--;
                } else {
                    nodes.push_back(carry[k]);
                }
            }
        }
        size = nodes.get_size();
        update_minimum();
    }

    T get_min() {
        if (nodes.get_size() == 0) {
            throw std::logic_error("Can't get minimum from an empty heap");
        }
        int minimum_value = nodes[minimum_position]->value;
        return minimum_value;
    }

    T extract_min() {
        if (nodes.get_size() == 0) {
            throw std::logic_error("Can't extract minimum from an empty heap");
        }
        T minimum_value = nodes[minimum_position]->value;
        for (int i = minimum_position; i < nodes.get_size() - 1; i++) {
            swap(nodes[i], nodes[i + 1]);
        }
        BinomialHeap<T> *temp = new BinomialHeap<T>();
        temp->nodes = nodes[nodes.get_size() - 1]->nodes;
        nodes.pop_back();
        merge(temp);
        size = nodes.get_size();
        update_minimum();
        return minimum_value;
    }

    void insert(T value) {
        BinomialHeap<T> *singleton = new BinomialHeap<T>();
        singleton->nodes.push_back(new BinomialHeap<T>(value));
        merge(singleton);
        update_minimum();
    }

    bool is_empty() {
        return nodes.get_size() > 0;
    }

    ~BinomialHeap() {
        delete parent;
    }
};