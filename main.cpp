#include <iostream>
#include "Trie.h"
int main() {
    Trie*t = new Trie();
    t->add("hello");
    std::cout<<t->contains("hello")<<" "<<t->getSize()<<" "<<t->isPrefix("h0");

    return 0;
}
