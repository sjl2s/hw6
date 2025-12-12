#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0}; 
        int len = k.length();
        int end = len - 1;

        for (int i = 4; i >= 0; i--) {
            if (end < 0) {
                break;
            }
            int start = end - 5;
            if (start < 0) {
                start = 0;
            }

            unsigned long long sub = 0;
            for (int j = start; j <= end; j++) { //base 36 conversion
                sub = sub * 36 + letterDigitToNumber(k[j]);
            }
            w[i] = sub;
            end -= 6;
        }

        unsigned long long hash = 0;
        for (int i = 0; i < 5; i++) {
            hash += (rValues[i] * w[i]);
        }

        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'A' && letter <= 'Z') { //upper to lower
            letter = letter + 32;
        }
        if (letter >= '0' && letter <= '9') {
            return letter - '0' + 26;
        } else {
            return letter - 'a';
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
