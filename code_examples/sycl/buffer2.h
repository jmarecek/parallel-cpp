auto shared = malloc_shared<double>(42, q);

q.submit([&](handler& cgh){
  cgh.parallel_for(range{42}, [=](id<1> tid){
    shared[i] = 0.0;
  }
});