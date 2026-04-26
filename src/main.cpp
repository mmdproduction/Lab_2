#include"Sequence.hpp"
#include<iostream>
#include<vector>


int main(){
    int a[] = {1, 2, 3, 5};
    ListSequence<int> test = ListSequence<int>(a, 4);
    ArraySequence<int> testa = ArraySequence<int>(a, 4);

    auto ss = testa.filter([](int x){return (x % 2) == 0; });
    for(const auto& elem : *ss){
        std::cout << elem << " ";
    }
    std::cout << ss->getLength();

    delete ss;
}