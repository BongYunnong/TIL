// https://www.acmicpc.net/problem/2558

#include <iostream>
int main(){
    int a,b;
    std::cin>>a>>b;
    std::cout<< a*(b%10)<<std::endl;
    std::cout<< a*(((b%100)-(b%10))/10)<<std::endl;
    std::cout<< a*(((b%1000)-(b%100))/100)<<std::endl;
    std::cout<< a*b<<std::endl;
}