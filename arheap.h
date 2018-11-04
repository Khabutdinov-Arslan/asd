using std::invalid_argument;
using std::out_of_range;
using std::logic_error;



template <typename T> class Heap{
private:
    Vector<T> nodes;
    void sift_up(int i){
        while (nodes[i] < nodes[(i - 1) / 2]){
            nodes.change(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }
    void sift_down(int i){
        int heap_size = nodes.get_size();
        while (2 * i + 1 < heap_size){
            int left = 2 * i + 1, right = 2 * i + 2;
            int j = left;
            if ((right < heap_size) && (nodes[right] < nodes[left])){
                j = right;
            }
            if (nodes[i] > nodes[j]){
                nodes.change(i, j);
                i = j;
            }else{
                break;
            }
        }
    }
public:
    Heap(){}
    bool is_empty(){
        return nodes.get_size() == 0;
    }
    T get_min(){
        if (is_empty()){
            throw std::logic_error("Can't get minimum from empty structure");
        }else{
            return nodes.get(0);
        }
    }
    T extract_min(){
        if (is_empty()){
            throw std::logic_error("Can't get minimum from empty structure");
        }else{
            T answer = nodes.get(0);
            nodes.change(0, nodes.get_size() - 1);
            nodes.pop_back();
            sift_down(0);
            return answer;
        }
    }
    void insert(T key){
        nodes.push_back(key);
        sift_up(nodes.get_size() - 1);
    }
    template<class Iterator>
    Heap(Iterator begin, Iterator end){
        for (Iterator i = begin; i != end; i++){
            nodes.push_back(*i);
        }
        for (int i = nodes.get_size() / 2; i >= 0; i--){
            sift_down(i);
        }
    }
};