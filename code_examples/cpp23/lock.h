void thread_operation(){
    std::lock(mutex1,mutex2);
     ...
    complicated_task();
     ...
    mutex1.unlock();
    mutex2.unlock();
}