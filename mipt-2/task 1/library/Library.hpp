//
//  Library.hpp
//  library
//
//  Created by Andrey Danilov on 28.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#ifndef Library_hpp
#define Library_hpp
#include <string>
#include <vector>
using namespace std;
class Edition{
protected:
    vector<string> author_;
    string name_;
    string publisher_;
    int releaseYear_;
    int number_;
    int numberAvailable_;
public:
    Edition(vector<string> author, string name, string publisher, int releaseYear);
    vector<string> author() const;
    string name() const;
    string publisher() const;
    int releaseYear() const;
    int& number();
    int& numberAvailable();
    const int& number() const;
    const int& numberAvailable() const;
    //virtual bool isAvailable() const = 0;
    virtual string info() const = 0;
};

class Book : public Edition{
private:
    int pagesNumber_;
    string content_;
public:
    Book(vector<string> author, string name, string publisher, int releaseYear, int pagaesNumber, string content);
    Book(string author, string name, string publisher, int releaseYear, int pagesNumber, string content);
    int pagesNumber() const;
    string content() const;
    string info() const;
    bool isAvailable() const;
};

class Works : public Edition{
private:
    vector<Book*> books;
public:
    Works(string name, vector<Book*> books);
    void addBook(Book* book);
    void removeBook(int id);
    string info() const;
    bool isAvailable() const;
};

class Magazines : public Edition{
private:
    vector<Book*> magazines;
public:
    Magazines(string name, vector<Book*> books);
    void addMagazine(Book* book);
    void removeMagazine(int id);
    string info() const override;
    bool isAvailable() const;
};

class Library{
private:
    vector<Edition*> editions;
public:
    void addEdition(Edition* edition);
    void removeEdition(int id);
    void borrow(int id);
    void regain(int id);
    string info() const;
    int search(string key) const;
};
#endif /* Library_hpp */
