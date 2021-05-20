//
// Created by Lorne Zhang on 11/25/20.
//

#include "PrimeSum.h"
#include <iostream>

PrimeSum::PrimeSum(int n) {
    this->num = n;
}

bool checkPrime(int n) {
    for(int i=2; i<n; i++) {
        if(n%i == 0) return false;
    }
    return true;
}

void PrimeSum::printPrimes() {
    if(this->num == 0 || num == 1) return;
    for(int i=2; i<num; i++) {
        if(checkPrime(i)) {
            std::cout << i << std::endl;
        }
    }
}

void PrimeSum::printSum() {
    int sum = 0;
    if(num == 0 || num == 1) return;
    for(int i=2; i<num; i++) {
        if(checkPrime(i)) {
            sum += i;
        }
    }
    std::cout << sum << std::endl;
}