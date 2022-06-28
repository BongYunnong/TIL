#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<time.h>
using namespace std;

int main(){
    time_t timer;
    struct tm t;
    char buf[80];
    timer = time(NULL);
    t= *localtime(&timer);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &t); 
    cout<<buf;
}