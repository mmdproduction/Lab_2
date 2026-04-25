#include"Sequence.hpp"
#include<iostream>
#include<vector>


int main(){
    int a[] = {1, 2, 3, 5};
    ListSequence<int> test = ListSequence<int>(a, 4);
    ArraySequence<int> testa = ArraySequence<int>(a, 4);

    auto sub_1 = testa.getSubsequence(1, 3);

    auto con = testa.concat(test)->concat(*sub_1);


    for(const auto& elem : *con){
        std::cout << elem << " ";
    }

    delete con;
}