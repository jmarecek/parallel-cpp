add_executable(for_each for_each.cpp)
install(TARGETS for_each DESTINATION bin)

add_executable(for_each_n for_each_n.cpp)
install(TARGETS for_each_n DESTINATION bin)

add_executable(sort sort.cpp)
install(TARGETS sort DESTINATION bin)

add_executable(qsort qsort.cpp)
install(TARGETS qsort DESTINATION bin)

add_executable(qsort_not qsort_not.cpp)
install(TARGETS qsort_not DESTINATION bin)

add_executable(sort_heap sort_heap.cpp)
install(TARGETS sort_heap DESTINATION bin)

add_executable(merge merge.cpp)
install(TARGETS merge DESTINATION bin)

add_executable(merge_par merge_par.cpp)
install(TARGETS merge_par DESTINATION bin)

add_executable(accumulate accumulate.cpp)
install(TARGETS accumulate DESTINATION bin)

add_executable(accumulate_right accumulate_right.cpp)
install(TARGETS accumulate_right DESTINATION bin)

add_executable(reduce reduce.cpp)
install(TARGETS reduce DESTINATION bin)

add_executable(transform transform.cpp)
install(TARGETS transform DESTINATION bin)

add_executable(adjacent_difference adjacent_difference.cpp)
install(TARGETS adjacent_difference DESTINATION bin)