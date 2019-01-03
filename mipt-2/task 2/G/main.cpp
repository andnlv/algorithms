//
//  main.cpp
//  G
//
//  Created by Andrey Danilov on 17.04.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
struct P{
    long x;
    long y;
    long id;
};

class length{
private:
    long a;
    long b;
public:
    length(const P &p1, const P &p2){
        P p;
        p.x = abs(p1.x-p2.x);
        p.y = abs(p1.y-p2.y);
        a = abs(p.x-p.y);
        b = p.x > p.y ? p.x - a : p.y - a;
    }
    bool operator < (const length &l) const{
        if(a >= l.a){
            if(b >= l.b){
                return false;
            }
            return (a - l.a)*(a - l.a) < 2*(l.b-b)*(l.b-b);
        }
        if(b <= l.b){
            return true;
        }
        return (a - l.a)*(a - l.a) > 2*(l.b-b)*(l.b-b);
    }
};

P find_farest(P p, const vector<P> &v){
    int l = 0;
    int r = (int)v.size()-1;
    while(r > l+1){
        int newl = l + round((r - l)/3.);
        int newr = r - round((r - l)/3.);
        if(length(p, v[newl]) < length(p, v[newr])){
            l = newl;
        }
        else{
            r = newr;
        }
    }
    if(length(p, v[r]) < length(p, v[l])){
        return v[l];
    }
    return v[r];
}

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    vector<P> v;
    P p;
    for(int i = 0; i < n; ++i){
        cin >> p.x >> p.y;
        p.id = i+1;
        v.push_back(p);
    }
    sort(v.begin(), v.end(), [](P p1, P p2){return (p1.y < p2.y) || (p1.y == p2.y && p1.x > p2.x);});
    vector<P> ch;
    ch.push_back(v[0]);
    ch.push_back(v[1]);
    for(int i = 2; i < n; ++i){
        while(ch.size() >= 2 && (ch[ch.size()-1].x-ch[ch.size()-2].x)*(v[i].y-ch[ch.size()-1].y)-
              (ch[ch.size()-1].y-ch[ch.size()-2].y)*(v[i].x-ch[ch.size()-1].x) < 0){
            ch.pop_back();
        }
        ch.push_back(v[i]);
    }
    for(int i = n-2; i >= 0; --i){
        while(ch.size() >= 2 && (ch[ch.size()-1].x-ch[ch.size()-2].x)*(v[i].y-ch[ch.size()-1].y)-
              (ch[ch.size()-1].y-ch[ch.size()-2].y)*(v[i].x-ch[ch.size()-1].x) < 0){
            ch.pop_back();
        }
        ch.push_back(v[i]);
    }
    ch.pop_back();
    length maxL(ch[0], ch[0]);
    P maxP1, maxP2;
    for(auto &i : ch){
        P p = find_farest(i, ch);
        if(maxL < length(i, p)){
            maxL = length(i, p);
            maxP1 = i;
            maxP2 = p;
        }
    }
    cout << maxP1.id << " " << maxP2.id;
    return 0;
}
