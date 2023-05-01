buffer<double> A{range{42}};

q.submit([&](handler &cgh) {
  accessor aA{A, cgh};
  cgh.parallel_for(range{42}, [=](id<1> idx) {
    aA[idx] = 0.0;
  });
});

host_accessor result{A};
for (int i = 0; i < 42; i++) {
  assert(result[i] == 0);
}