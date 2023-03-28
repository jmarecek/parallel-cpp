void odd-even-merge (std::vector<int>& vector_to_sort, int from, int to, int step) {
    auto new_step = step * 2;
    if (new_step < to - from) {
        odd-even-merge(vector_to_sort,from,to,new_step);
        odd-even-merge(vector_to_sort,from+step,to,new_step);
        for (int i=from+step; i<to-step; i += new_step) {
            compare_and_swap(vector_to_sort,i,i+step);
        }
    } else {
        compare_and_swap(vector_to_sort,from,from+step);
    }
}
