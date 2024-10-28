cmake_minimum_required(VERSION 3.29)
project(ObligatorioEDA2)

set(CMAKE_CXX_STANDARD 14)

include_directories(cmake-build-debug)
include_directories(funciones)
include_directories(models)
include_directories(tads)

add_executable(ObligatorioEDA2
    funciones/enteros.cpp
    funciones/io.cpp
    models/Book.cpp
    models/Command.cpp
    tads/AVL.cpp
    tads/HashTableOpenAddressing.cpp
    tads/List.h
    tads/ListImp.cpp
    tads/Table.h
    ejercicio1
    ejercicio1.cpp
    ejercicio10.cpp
    ejercicio2
    ejercicio2.cpp
    ejercicio3.cpp
    ejercicio4.cpp
    ejercicio5.cpp
    ejercicio6.cpp
    ejercicio7.cpp
    ejercicio8.cpp
    ejercicio9.cpp
        models/Item.cpp
        tads/Heap.h
        tads/HeapSort.cpp)
