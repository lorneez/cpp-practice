#include <fstream>

#include "Morse/smorse.h"
#include "Morse/decode.h"
#include "FileCalculator/filecalculator.h"
#include "Mandelbrot/mandelbrot.h"
#include "MultiThreading/fibjob.h"
#include "ImageConverter/imageconverter.h"
#include "Project1/PrimeSum.h"
#include "Project1/Matrix2D.h"
#include "Project2/vector/MatrixVector.h"
#include "Project2/template/LinkedList.h"
#include "Project2/hashmap/HashMapGame.h"
#include "Project2/hashset/HashSetGame.h"
#include "Project4/ListFilesAndDirectories.h"

/**
 * Test for decode smorse
 */
void RunDecode() {
    Smorse s("lorne");
    s.ShowText();
    Decode d(".-.. --- .-. -. . .-..");
    d.ShowText();
}

/**
 * Test for file calculator
 */
void RunFileCalculator() {
    FileCalculator f;

    // f.CalculateRecursively("/Users/lorneez/");
    // 9370110329 Bytes!

    // f.CalculateUsingThreadLoop("/Users/lorneez/");
    // 16485208216 Bytes!

    // f.CalculateUsingMultiThreading("/Users/lorneez/");
    // 29587857974 Bytes!

    f.Show();
}

/**
 * Test for mandelbrot
 */
void RunMandelbrot() {
    Mandelbrot m(1000, 1000);
    m.Display();
}

/**
 * Test for thread pool
 */
void RunFibThreadPool() {
    FibJob f(1);
    for(int i=1; i<20; i++) {
        f.fibmain(i);
    }
}

/**
 * Test for image converter
 */
void RunImageConverted() {
    ImageConverter i("../Cyan.bmp", "../test.txt");
    i.run();
}

/**
 * Test for prime sum
 */
void RunPrimeSum() {
    PrimeSum p(1000);
    p.printPrimes();
    p.printSum();
}

/**
 * Test for matrix 2d
 */
void RunMatrix2D() {
    Matrix2D a(5,5);
    a.print();
    Matrix2D b(5,5);
    b.print();
    Matrix2D c = a.multiply(b);
    c.print();
}

/**
 * Test for matrix vector
 */
void RunVector() {
    MatrixVector m(1,std::vector<int>{1});
    m.test();
}

/**
 * Test for matrix vector
 */
void RunListNode() {
    LinkedList<int> integer_list;
    for(int i=0; i<10; i++) {
        integer_list.add(i);
    }
    integer_list.print();
}

/**
 * Test for hash map game
 */
void RunHashMapGame() {
    HashMapGame game;
    game.run();
}

/**
 * Test for hash set game
 */
void RunHashSetGame() {
    HashSetGame game;
    game.run();
}

/**
 * Project 3
 */


template <typename Iterator>
void ProcessIterator(Iterator begin, Iterator end, ostream& stream) {
    while(begin != end) {
        stream << *begin;
        begin ++;
    }

}

template <typename Iterator>
void ProcessIteratorMap(Iterator begin, Iterator end, ostream& stream) {
    while(begin != end) {
        stream << begin->second;
        begin ++;
    }

}


/**
 * Test for iterator stream processor
 */
void RunIteratorStreamProcessor() {
    // make three objects
    std::vector<int> v{1,2,3};
    std::unordered_set<int> s{4,5,6};
    std::map<int, int> m;
    m.insert(std::pair<int,int>(7,7));
    m.insert(std::pair<int,int>(8,8));
    m.insert(std::pair<int,int>(9,9));

    // make file stream
    std::ofstream f;
    f.open(("iterator_stream_test.txt"));
    f << "hi";

    // process iterators with file stream
    ProcessIterator(v.begin(), v.end(), f);
    ProcessIterator(s.begin(), s.end(), f);
    ProcessIteratorMap(m.begin(), m.end(), f);
    f.close();

    // process iterators with cout
    ProcessIterator(v.begin(), v.end(), std::cout);
    ProcessIterator(s.begin(), s.end(), std::cout);
    ProcessIteratorMap(m.begin(), m.end(), std::cout);
}

/**
 * Project 4
 */
void RunLS() {
    ListFilesAndDirectories a;
    a.Show("/Users/lorneez");
}

int main() {
    // RunDecode();
    // RunMandelbrot();
    // RunFileCalculator();
    // RunFibThreadPool();
    // RunImageConverted();

    // Project 1
    // RunPrimeSum();
    // RunMatrix2D();

    // Project 2
    // RunVector();
    // RunListNode();
    // RunHashMapGame();
    // RunHashSetGame();

    // Project 3
    // RunIteratorStreamProcessor();

    // Project 4
    RunLS();

    return 0;
}