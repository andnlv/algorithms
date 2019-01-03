//
//  Library.cpp
//  library
//
//  Created by Andrey Danilov on 28.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include "Library.hpp"

Edition::Edition(vector<string> author, string name, string publisher, int releaseYear){
    author_ = author;
    name_ = name;
    publisher_ = publisher;
    releaseYear_ = releaseYear;
    number_ = numberAvailable_ = 0;
}

vector<string> Edition:: author() const{
    return author_;
}

string Edition:: name() const{
    return name_;
}

string Edition:: publisher() const{
    return publisher_;
}

int Edition:: releaseYear() const{
    return releaseYear_;
}

int& Edition:: numberAvailable(){
    return numberAvailable_;
}

int& Edition:: number(){
    return number_;
}

const int& Edition:: numberAvailable() const{
    return numberAvailable_;
}

const int& Edition:: number() const{
    return number_;
}

Book:: Book(vector<string> author, string name, string publisher, int releaseYear, int pagesNumber, string content)
:Edition(author, name, publisher, releaseYear)
{
    pagesNumber_ = pagesNumber;
    content_ = content;
}

int Book:: pagesNumber() const{
    return pagesNumber_;
}
string Book:: content() const{
    return content_;
}
string Book:: info() const{
    string authors;
    for(auto i : author_){
        authors += i + ", ";
    }
    return "The book " + name() + " written by " + authors + " in " + to_string(releaseYear()) + ", published by " + publisher();
}

Book:: Book(string author, string name, string publisher, int releaseYear, int pagesNumber, string content)
: Book(vector<string>({author}), name, publisher, releaseYear, pagesNumber, content){};


bool Book:: isAvailable() const{
    return numberAvailable() > 0;
}

Works:: Works(string name, vector<Book*> newBooks):
Edition(vector<string>(), name, "'", 1000000)
{
    for(auto i : newBooks){
        addBook(i);
    }
}

void Works:: addBook(Book *book){
    if(publisher() == "'"){
        publisher_ = book->publisher();
    }
    else if(publisher() != book->publisher())
        publisher() = "";
    for(auto i : book->author()){
        if(count(author_.begin(), author_.end(), i) == 0){
            author_.push_back(i);
        }
    }
    if(book->releaseYear() < releaseYear())
        releaseYear_ = book->releaseYear();
    books.push_back(book);
}

void Works:: removeBook(int id){
    if(id >= books.size()) return;
    books.erase(books.begin()+id);
    vector<Book*> oldBooks = books;
    books.clear();
    author_.clear();
    releaseYear_ = 1000000;
    publisher_ = "'";
    for(auto i : oldBooks){
        addBook(i);
    }
}

string Works:: info() const{
    string authors;
    for(auto i : author_){
        authors += i + ", ";
    }
    string result = "Works " + name() +  " contain " + to_string(books.size()) + " books, written by " + authors + "since " + to_string(releaseYear()) + ":\n";
    for(int i = 0; i < books.size(); ++i){
        result += "   " + to_string(i) +  ") " + books[i]->info() + "\n";
    }
    result.pop_back();
    return result;
}

bool Works:: isAvailable() const{
    return all_of(books.begin(), books.end(), [](Book *book){return book->isAvailable();});
}

Magazines:: Magazines(string name, vector<Book*> newBooks):
Edition(vector<string>(), name, "'", 1000000)
{
    for(auto i : newBooks){
        addMagazine(i);
    }
}

void Magazines:: addMagazine(Book *book){
    if(publisher() == "'"){
        publisher_ = book->publisher();
    }
    else if(publisher() != book->publisher())
        publisher() = "";
    for(auto i : book->author()){
        if(count(author_.begin(), author_.end(), i) == 0){
            author_.push_back(i);
        }
    }
    if(book->releaseYear() < releaseYear())
        releaseYear_ = book->releaseYear();
    magazines.push_back(book);
}

void Magazines:: removeMagazine(int id){
    if(id >= magazines.size()) return;
    magazines.erase(magazines.begin()+id);
    vector<Book*> oldMagazines = magazines;
    magazines.clear();
    author_.clear();
    releaseYear_ = 1000000;
    publisher_ = "'";
    for(auto i : oldMagazines){
        addMagazine(i);
    }
}

string Magazines:: info() const{
    string authors;
    for(auto i : author_){
        authors += i + ", ";
    }
    string result = "Magazines " + name() + ":\n";
    for(int i = 0; i < magazines.size(); ++i){
        result += "   " + to_string(i) +  ") " + magazines[i]->name() + ", " + to_string(releaseYear()) + "\n";
    }
    return result;
}

bool Magazines:: isAvailable() const{
    return all_of(magazines.begin(), magazines.end(), [](Book *book){return book->isAvailable();});
}

void Library:: addEdition(Edition* edition){
    auto it = find(editions.begin(), editions.end(), edition);
    if(it == editions.end()){
        editions.push_back(edition);
        editions.back()->number() = editions.back()->numberAvailable() = 1;
    }
    else{
        ++(*it)->number();
        ++(*it)->numberAvailable();
    }
}

void Library::removeEdition(int id){
    if(id < editions.size()){
        if(editions[id]->number() == 1)
            editions.erase(editions.begin()+id);
        else
            --(editions[id]->number());
    }
}

void Library:: borrow(int id){
    if(id < editions.size()){
        --editions[id]->numberAvailable();
    }
}

void Library:: regain(int id){
    if(id < editions.size()){
        ++editions[id]->numberAvailable();
    }
}

string Library:: info() const{
    string result = "Library contain:\n";
    for(int i = 0; i < editions.size(); ++i){
        result += to_string(i) + ") " + editions[i]->info() + "\n";
    }
    return result;
}

int Library::search(string key) const{
    for(int i = 0; i < editions.size(); ++i){
        if(editions[i]->name() == key || count(editions[i]->author().begin(), editions[i]->author().end(), key) > 0){
            return i;
        }
    }
    return -1;
}



