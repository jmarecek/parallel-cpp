void matrix_multiply(
        const MyMatrix<double>& a,
        const MyMatrix<double>& b,
        MyMatrix<std::atomic<double>>& c
) {
    auto start = boost:make_counting_iterator(0);
    auto end = boost:make_counting_iterator(a.rows() * b.cols() * a.cols());
    auto i_stride = b.cols() * a.cols(); auto j_stride = a.cols();
    std::for_each(
            std::par_unseq, start, end,
            [&](int idxs) {
                auto i = idxs / i_stride;
                auto j = (idxs % i_stride) / j_stride;
                auto k = idxs % j_stride;
                c(i, j) += a(i, k) * b(k, j);
            }
    ) ;
}