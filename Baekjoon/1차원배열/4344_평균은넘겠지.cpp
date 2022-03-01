#include <iostream>
using namespace std;
int main(){
    int c;
    cin>>c;

    double avg=0;
    int scores[1001];

    int n;
    for(int i=0;i<c;i++){
        avg=0;
        cin>>n;
        for(int j=0;j<n;j++){
            cin>>scores[j];
            avg+=scores[j];
        }
        avg /=n;
        int count=0;
        for(int j=0;j<n;j++){
            if(avg<scores[j])
                count++;
        }

        printf("%.3f%%\n",((float)count/n)*100);
    }
}