Minimum Multiplication
=================

Minimum Multiplication
--------------------
--------------------
- Problem : Determining the minimum number of elementary multiplications needed to multiply n matrices and an order that produces that minimum number.
    - Input : the number of matrices n, array of integers d[0...n], d[i-1]Xd[o] is the dimension of the ith matrix
    - Output : minmult, the minimum number of elementary multiplications needed to multiply the n matrices. 2d array P
- Instance
    - A(20X2) * B(2X30) * C(30X12) * D(12X8)
    - output : 1232
    - A(B(CD)) 30 * 12 * 8 +  2 * 30 * 8   + 20 * 2 * 8  = 3680
    - (AB)(CD) 20 * 2 * 30 +  30 * 12 * 8  + 20 * 30 * 8 = 8880
    - A((BC)D) 2 * 30 * 12 +  2 * 12 * 8   + 20 * 2 * 8  = 1232
    - ((AB)C)D 20 * 2 * 30 +  20 * 30 * 12 + 20 * 12 * 8 = 10320
    - (A(BC))D 2 * 30 * 12 +  20 * 2 * 12  + 20 * 12 * 8 = 3120
    

```C++
int minmul(int n, const int d[], index P[][]){
    index i,j,k,diagonal;
    int M[1...n][1...n];
    for(i = 1; i<= m ; i++){
        M[i][i]= 0;
        
    }
}
```