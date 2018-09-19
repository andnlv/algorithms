//
//  Algorithm.cpp
//  Convertions_SPZ
//
//  Created by Andrey Danilov on 16.12.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Algorithm.hpp"

std::vector<int> s_to_p(const std::string& s){
    std::vector<int> p(s.size(), 0);
    for(int i = 1; i < p.size(); ++i){
        p[i] = p[i-1];
        while(p[i] > 0 && s[p[i]] != s[i])
            p[i] = p[p[i]-1];
        if(s[p[i]] == s[i])
            ++p[i];
    }
    return p;
}

std::string p_to_s(const std::vector<int> &p){
    std::string s;
    s.resize(p.size());
    s[0] = 'a';
    for(int i = 1; i < p.size(); ++i){
        if(p[i] != 0)
            s[i] = s[p[i]-1];
        else{
            s[i] = 'a'-1;
            int j;
            do{
                ++s[i];
                j = p[i-1];
                while(j > 0 && s[j] != s[i])
                    j = p[j-1];
                if(s[j] == s[i])
                    ++j;
            }
            while(j != 0);
        }
    }
    return s;
}

std::vector<int> s_to_z(const std::string& s){
    std::vector<int> z (s.length(), 0);
    for(int i = 1, l = 0, r = 0; i < s.length(); ++i) {
        if(i <= r)
            z[i] = std::min (r - i + 1, z[i-l]);
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]])
            ++z[i];
        if(i + z[i] - 1 > r){
            l = i;
            r = i + z[i] - 1;
        }
    }
    z[0] = (int) s.length();
    return z;
}

std::string z_to_s(const std::vector<int> &z){
    std::set<char> banned_letters;
    std::string s;
    s.resize(z.size());
    int r = 0;
    s[0] = 'a';
    for(int i = 1; r < z.size()-1; ++i){
        if(z[i] == 0 && i > r){
            char prev_letter = 'a';
            for(auto it = banned_letters.begin(); ;++it){
                if(it == banned_letters.end()){
                    s[i] = prev_letter + 1;
                    break;
                }
                if(*it - prev_letter > 1){
                    s[i] = *it - 1;
                    break;
                }
                prev_letter = *it;
            }
            ++r;
            banned_letters.clear();
        }
        if(z[i] != 0 && i + z[i] - 1 > r){
            for(int j = r + 1; j <= i + z[i] - 1; ++j)
                s[j] = s[j - i];
            r = i + z[i] - 1;
            banned_letters.clear();
        }
        if(r == i + z[i] - 1)
            banned_letters.insert(s[z[i]]);
    }
    return s;
}

std::vector<int> z_to_p(const std::vector<int>& z){
    return s_to_p(z_to_s(z));
}

std::vector<int> p_to_z(const std::vector<int> &p){
    return s_to_z(p_to_s(p));
}

std::string gen_str(int length, int n){
    std::string s;
    s.resize(length);
    for(int i = 0; i < length; ++i)
        s[i] = 'a' + rand()%n;
    return s;
}

void s_to_p(){
    std::string s;
    std::cin >> s;
    std::vector<int> p = s_to_p(s);
    for(int i = 0; i < p.size(); ++i)
        std::cout << p[i] << " ";
    std::cout << "\n";
    
}

void s_to_z(){
    std::string s;
    std::cin >> s;
    std::vector<int> z = s_to_z(s);
    for(int i = 0; i < z.size(); ++i)
        std::cout << z[i] << " ";
    std::cout << "\n";
    
}

void p_to_s(){
    std::vector<int> p;
    std::stringstream in;
    std::string str;
    getline(std::cin, str);
    in << str;
    while(!in.eof()){
        int d;
        in >> d;
        if(in.fail())
            break;
        p.push_back(d);
    }
    std::cout << p_to_s(p);
    std::cout << "\n";
}

void z_to_s(){
    std::vector<int> z;
    std::stringstream in;
    std::string str;
    getline(std::cin, str);
    in << str;
    while(!in.eof()){
        int d;
        in >> d;
        if(in.fail())
            break;
        z.push_back(d);
    }
    std::cout << z_to_s(z);
    std::cout << "\n";
}

void z_to_p(){
    std::vector<int> z;
    std::stringstream in;
    std::string str;
    getline(std::cin, str);
    in << str;
    while(!in.eof()){
        int d;
        in >> d;
        if(in.fail())
            break;
        z.push_back(d);
    }
    std::vector<int> p(z_to_p(z));
    for(int i = 0; i < z.size(); ++i)
        std::cout << p[i] << " ";
    std::cout << "\n";
}

void p_to_z(){
    std::vector<int> p;
    std::stringstream in;
    std::string str;
    getline(std::cin, str);
    in << str;
    while(!in.eof()){
        int d;
        in >> d;
        if(in.fail())
            break;
        p.push_back(d);
    }
    std::vector<int> z(p_to_z(p));
    for(int i = 0; i < z.size(); ++i)
        std::cout << z[i] << " ";
    std::cout << "\n";
}