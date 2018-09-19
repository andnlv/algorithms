//
//  RandomTester.cpp
//  Aho-Corasik
//
//  Created by Andrey Danilov on 11.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "RandomTester.hpp"

void randomTest(int n, int l1, int l2, int k, size_t randomSeed){
    string str;
    string pattern;
    for(int i = 0; i < n; ++i){
        stringstream stream;
        generate_random(stream, l1, l2, k);
        check(stream);
        //compare(stream);
    }
}

void check(stringstream &stream){
    stringstream input;
    input << stream.str();
    string myAnswer = algorithm(input);
    input.clear();
    input << stream.str();
    string correctAnswer = countAnswer(stream);
    if(myAnswer != correctAnswer)
        cout << stream.str() << "\ncorrect:" << correctAnswer << "\nmine:" << myAnswer << "\n\n";
}

void compare(stringstream &stream){
    stringstream input;
    input << stream.str();
    string onlineAnswer = algorithm(input);
    input.clear();
    input << stream.str();
    string correctAnswer = algorithm(input);
    if(onlineAnswer != correctAnswer)
        cout << stream.str() << "online:" << onlineAnswer << "\nmine:" << correctAnswer << "\n\n";
}

void generate_random(stringstream& stream, int l1, int l2, int k, size_t seed){
    srand(int(seed));
    stream.clear();
    for(int i = 0; i < l2; ++i){
        bool typeOfC = random()%4 == 1;
        if(typeOfC)
            stream << '?';
        else
            stream << char('a' + random()%k);
    }
    stream << '\n';
    for(int i = 0; i < l1; ++i){
        stream << char('a' + random()%k);
    }
    stream << '\n';
}

string countAnswer(stringstream &stream){
    stringstream out;
    string pattern, str;
    stream >> pattern >> str;
    for(int i = 0; i <= str.length()-pattern.length(); ++i){
        bool ok = true;
        for(int j = 0; ok && j < pattern.length(); ++j)
            if(pattern[j] != '?' && pattern[j] != str[i+j])
                ok = false;
        if(ok)
            out << i << " ";
    }
    return out.str();
}