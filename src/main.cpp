#include"Sequence.hpp"
#include<iostream>
#include<vector>


int main(){
    int a[] = {1, 2, 3, 5};
    ListSequence<int> test = ListSequence<int>(a, 4);
    ArraySequence<int> testa = ArraySequence<int>(a, 4);

    auto ss = testa.map<float>([](int x){return x * 2.34;})->map<int>([](float x){ return int(x / 2) % 3; })->getLast();

    
    std::cout << ss << " ";

    //delete ss;
}