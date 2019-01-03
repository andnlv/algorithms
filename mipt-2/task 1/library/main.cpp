//
//  main.cpp
//  library
//
//  Created by Andrey Danilov on 28.03.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
// Book(vector<string> author, string name, string publisher, int releaseYear, int pagaesNumber, string contenet);


#include <iostream>
#include "Library.hpp"
int main(int argc, const char * argv[]) {
    Library myLib;
    Book* books[5];
    books[0] = new Book("Pushkin", "Onegin", "dom knigi", 1827, 255, "Once upon a time...");
    books[1] = new Book("Dostoevskiy", "Crime and Punishment", "dom knigi", 1887, 345, "Once upon a time...");
    books[2] = new Book("Tolkien", "Lord of the Rings. Part 1", "book shop", 1903, 175, "Once upon a time...");
    books[3] = new Book("Tolkien", "Lord of the Rings. Part 2", "book shop", 1904, 175, "Once upon a time...");
    books[4] = new Book("Tolkien", "Lord of the Rings. Part 3", "book shop", 1905, 175, "Once upon a time...");
    
    Works* lotr = new Works("Lord Of The Ring", vector<Book*>({books[2], books[3], books[4]}));
    
    myLib.addEdition(books[0]);
    myLib.addEdition(lotr);
    myLib.addEdition(books[1]);
    cout << myLib.info();
    for(int i = 0; i < 5; ++i) delete books[i];
    delete lotr;
    return 0;
}
