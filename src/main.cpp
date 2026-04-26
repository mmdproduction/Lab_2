#include"Sequence.hpp"
#include<iostream>
#include<vector>


int main(){
    int a[] = {1, 2, 3, 5};
    ListSequence<int> test = ListSequence<int>(a, 4);
    ArraySequence<int> testa = ArraySequence<int>(a, 4);

    auto ss = testa.where([](int x){return (x % 2) == 0; })->map<int>([](int x){return x * 100; })->concat(*(test.map<int>([](int x){return x * 3; })))->concat(testa)->concat(test)->where([](int x){return (x % 2) == 0; })->map<int>([](int x){return x * 100; });
    for(const auto& elem : *ss){
        std::cout << elem << " ";
    }
    
    std::cout << ss->getLength() << std::endl;
    delete ss;

    auto red = testa.reduce([](int avg, int x){ return avg + x; }, 0);
    
    std::cout << red;
}