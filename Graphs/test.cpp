#include "min_heap_map.h"

int main() {
    MinHeapMap min_heap;
    min_heap.add(1, 10);
    min_heap.add(2, 31);
    min_heap.add(3, 100);
    min_heap.add(4, 41);
    min_heap.add(5, 51);
    min_heap.add(6, 16);
    min_heap.add(7, 44);

    std::cout<<"Min is" << min_heap.extract_min().first << "\n";

    std::cout<<"Heap contains 9->" << min_heap.contains(9) << "\n";

    std::cout<<"Heap contains 5->" << min_heap.contains(5) << "\n";

    min_heap.decrease(4, 25);

    min_heap.print();

    return 0;
}