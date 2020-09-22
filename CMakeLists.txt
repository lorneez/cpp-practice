cmake_minimum_required(VERSION 3.17)
project(dailyprogrammer)

set(CMAKE_CXX_STANDARD 14)

add_executable(dailyprogrammer main.cpp smorse.cpp smorse.h decode.cpp decode.h filecalculator.cpp filecalculator.h mandelbrot.cpp mandelbrot.h threadpool.cpp threadpool.h job.cpp job.h jobqueue.cpp jobqueue.h fibjob.cpp fibjob.h imageconverter.cpp imageconverter.h)