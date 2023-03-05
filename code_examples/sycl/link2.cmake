set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsycl -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS " -fsycl -lmkl_sycl -lmkl_intel_ilp64 -lmkl_sequential -lmkl_core")