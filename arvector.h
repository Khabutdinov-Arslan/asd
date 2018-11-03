using std::invalid_argument;
using std::out_of_range;
using std::logic_error;
using std::swap;

template<typename T>
class Vector {
private:
    int last = 0, size = 1;
    T *current_array = nullptr;

    void widen() {
        T *new_array = new T[size * 2];
        for (int i = 0; i < last; i++) {
            new_array[i] = current_array[i];
        }
        size *= 2;
        delete[] current_array;
        current_array = new_array;
    }

    void shrink() {
        T *new_array = new T[size / 2];
        for (int i = 0; i < last; i++) {
            new_array[i] = current_array[i];
        }
        size /= 2;
        delete[] current_array;
        current_array = new_array;
    }

public:
    Vector() : last(0), size(1), current_array(new T[1]) {}

    T get(int index) {
        if (index < last) {
            return current_array[index];
        } else {
            throw out_of_range("Index exceeds range");
        }
    }

    void push_back(T element) {
        if (last == size) {
            widen();
        }
        current_array[last] = element;
        last++;
    }

    void pop_back() {
        if (last == 0) {
            throw logic_error("Can't delete from empty structure");
        }
        if (last * 2 < size) {
            shrink();
        }
        last--;
    }

    int get_size() {
        return last;
    }

    void change(int i, int j) {
        if ((i < last) && (j < last)) {
            swap(current_array[i], current_array[j]);
        } else {
            throw out_of_range("One of indexes exceeds range");
        }
    }

    ~Vector() {
        delete[] current_array;
    }

    const T operator[](int index) {
        return this->get(index);
    }
};