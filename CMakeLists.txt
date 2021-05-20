cmake_minimum_required(VERSION 3.17)
project(dailyprogrammer)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_code main.cpp Morse/decode.cpp Morse/smorse.cpp MultiThreading/fibjob.cpp MultiThreading/job.cpp MultiThreading/jobqueue.cpp MultiThreading/threadpool.cpp Project1/PrimeSum.cpp Mandelbrot/mandelbrot.cpp ImageConverter/imageconverter.cpp FileCalculator/filecalculator.cpp Project1/Matrix2D.cpp Project1/Matrix2D.h Project2/vector/MatrixVector.cpp Project2/vector/MatrixVector.h Project2/template/ListNode.h Project2/template/LinkedList.h Project2/hashmap/HashMapGame.cpp Project2/hashmap/HashMapGame.h Project2/hashset/HashSetGame.cpp Project2/hashset/HashSetGame.h)
