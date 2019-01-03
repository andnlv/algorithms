//
//  main.cpp
//  Lambda
//
//  Created by Andrey Danilov on 14.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
int main(int argc, char **argv){
    //1
    srand(int(time(NULL)));
    vector<int> a;
    generate_n(back_inserter(a), 1000, [](){
        return rand()%100;
    });
    //2
    vector<int> b;
    copy(a.begin(), a.end(), back_inserter(b));
    //3
    random_shuffle(b.begin(), b.end());
    //4
    sort(b.begin(), b.end(), [](int x1, int x2){
        return x2 < x1;
    });
    //5
    reverse(b.begin(), b.end());
    //6
    assert(b.begin() == min_element(b.begin(), b.end()));
    //7
    assert(b.rend() == max(b.rend(), b.rbegin()));
    //8
    vector<int> permutation;
    for(int i = 0; i < 1000; ++i)
        permutation.push_back(i);
    //9
    sort(permutation.begin(), permutation.end(), [&a](int x1, int x2){
        return a[x1] < a[x2];
    });
    //10
    vector<int> sorted;
    transform(permutation.begin(), permutation.end(), back_inserter(sorted), [&a](int i){
        return a[i];
    });
    //11
    assert(is_sorted(sorted.begin(), sorted.end()));
    //12
    assert(!(lexicographical_compare(sorted.begin(), sorted.end(), b.begin(), b.end()) ||
             lexicographical_compare(b.begin(), b.end(), sorted.begin(), sorted.end())));
    //13, 14
    vector<int> counts;
    generate_n(back_inserter(counts), 100, [&a, &b](){
        static int i = 0;
        long c = count(a.begin(), a.end(), i);
        assert(c == upper_bound(b.begin(), b.end(), i) - lower_bound(b.begin(), b.end(), i));
        ++i;
        return c;
    });
    //15
    int summ = 0;
    for_each(counts.begin(), counts.end(), [&summ](int x){
        summ += x;
    });
    assert(summ = 1000);
    //16
    for_each(b.begin(), b.end(), [](int x){
        cout << x << " ";
    });
    cout << "\n";
    return 0;
}