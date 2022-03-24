// https://www.acmicpc.net/problem/15552
// 첫 줄에 테스트케이스 T 주어졌을 때 A+B를 출력

// C++ 을 사용하는 경우
#include <iostream>
using namespace std;
int main(){
    cin.tie(NULL)->sync_with_stdio(false);

    long long t;
    cin >> t;

    int a, b;

    for(int i=0;i<t;i++){
        cin >> a >> b;
        cout << a+b<<'\n';
    }
}


// C#을 사용하는 경우
/*
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
public class Test
{
	public static void Main()
	{
		string c = Console.ReadLine();
		int C=int.Parse(c);
        
        StringBuilder abNumbers=new StringBuilder();
		//string s="";
		//string[] sList = new string[2];
		for(int i=0;i<C;i++){
			string[] sList=Console.ReadLine().Split(' ');
			abNumbers.Append(int.Parse(sList[0])+int.Parse(sList[1])+"\n");
		}
        Console.WriteLine(abNumbers.ToString());
	}
}
*/