add_executable(omp_atomic1 atomic1.cpp)
install(TARGETS omp_atomic1 DESTINATION bin)

add_executable(omp_barrier1 barrier1.cpp)
install(TARGETS omp_barrier1 DESTINATION bin)

add_executable(omp_barrier2 barrier2.cpp)
install(TARGETS omp_barrier2 DESTINATION bin)

add_executable(omp_critical1 critical1.cpp)
install(TARGETS omp_critical1 DESTINATION bin)

add_executable(omp_for_each1 for_each1.cpp)
install(TARGETS omp_for_each1 DESTINATION bin)

add_executable(omp_for_each2 for_each2.cpp)
install(TARGETS omp_for_each2 DESTINATION bin)

add_executable(omp_mutex1 mutex1.cpp)
install(TARGETS omp_mutex1 DESTINATION bin)

add_executable(omp_mutex2 mutex2.cpp)
install(TARGETS omp_mutex2 DESTINATION bin)

add_executable(omp_parallel2 parallel2.cpp)
install(TARGETS omp_parallel2 DESTINATION bin)

add_executable(omp_section1 section1.cpp)
install(TARGETS omp_section1 DESTINATION bin)

add_executable(omp_section2 section2.cpp)
install(TARGETS omp_section2 DESTINATION bin)

add_executable(omp_task1 task1.cpp)
install(TARGETS omp_task1 DESTINATION bin)
