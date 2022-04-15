// https://www.acmicpc.net/problem/10926

#include <iostream>

int main(){
    // 50을 넘지 않는다고해서 50을 넣으면 틀린다. 여유분을 두자.
    // 아마 \0(널문자) 가 들어간 것이 아닐까?
    char ids[100];
    std::cin>>ids;
    std::cout<<ids<<"??!";
}