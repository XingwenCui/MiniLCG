cmake_minimum_required(VERSION 3.24)
project(MiniLCG)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(minisat)
add_subdirectory(minicpp)

add_executable(MiniLCG main.cpp domain.h Solver.h Solver.cpp domain.cpp reason.cpp reason.h reason.h reason.h IntVar.cpp IntVar.h)


target_link_libraries(MiniLCG
                    minisat-lib-static
                    copl)
target_include_directories(MiniLCG
                    PRIVATE ${CMAKE_SOURCE_DIR}/minisat
                    PRIVATE ${CMAKE_SOURCE_DIR}/minicpp)

add_executable(SatTest SatTets.cpp)
target_link_libraries(SatTest
        minisat-lib-static
        copl)
target_include_directories(SatTest
        PRIVATE ${CMAKE_SOURCE_DIR}/minisat
        PRIVATE ${CMAKE_SOURCE_DIR}/minicpp)
#target_link_libraries(MiniLCG miniCPP.h)
#target_link_libraries(MiniLCG PRIVATE ${CMAKE_SOURCE_DIR}/minicpp)