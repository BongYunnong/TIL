#include <iostream>

int main(){
    // float은 32비트(4바이트) 자료형
    // double은 64비트(8바이트) 자료형
    // 오차가 10^-9이하여야 하기에 double을 사용해야한다.
    // float은 오차 범위가 약 10^-7, double은 10^-15라 한다.
    double a;
    double b;

    /*
    // scanf 사용 방식
    // double의 입력은 %lf이다.
    // long double은 %Lf이다.
    scanf("%lf %lf",&a, &b);1 
    // 기본적으로 lf는 소수점 6자리까지 출력하기에,
    // 오차범위를10^-9로 줄이려면 넉넉하게 %.10lf 이상이 되어야한다.
    printf("%.10lf",a/b);
    */

    // std 사용 방식
    // std::fixed -> 소수점 아래로 고정
    // std::cout.precision(n); -> 실수 전체 자리수 중 n 까지 표현
    //  소수점 부분만이 아니라 실수 전체 자리수이다.
    //  소수점 부분만 생각하기 위해서는 std::fixed가 필요하다.
    // 고정 소수점 표기를 해제하는 것은 std::cout.unsetf(ios::fixed);이다.
    std::cout.precision(10);
    std::cout<<std::fixed;
    std::cin>>a>>b;
    std::cout<<a/b;
}