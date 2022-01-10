# 미디어수학 #2

![미디어수학02](https://user-images.githubusercontent.com/11372675/148756725-475b3a99-8b38-4f9f-8fba-a3716d2e2f25.png)
- 벡터는 덧셈과 곱셈, 내적이 가능하다.
    - 곱셈의 경우에는 벡터 * 상수로 가능
    - 벡터의 사칙연산은 같은 dimension이어야만 한다.
- 내적
    - v $\cdot$ w = v<sub>1</sub>*w<sub>1</sub>+ v<sub>2</sub>*w<sub>2</sub>
    - 내적의 결과값은 실수이다.
    - 내적은 두 벡터가 이루는 각과 연관되어있다.
    - v $\cdot$ w = ||v|| $\cdot$ ||w|| * cos $\theta$
    - 교환법칙 불가
    - 앞 매트릭스의 열과 뒤 매트릭스의 행 수가 같아야 연산 가능

- ! row vector, column vector는 표현의 차이이다.

- Identity Matrix
    - I $\cdot$ A = A $\cdot$ I = A
    - 어떠한 매트릭스와 곱했을 때 자신이 되는 매트릭스 
    - diagonal 축만 1이고 나머지는 0

![미디어수학02주차_1](https://user-images.githubusercontent.com/11372675/148756781-6dba655e-7e27-435f-94bf-95da0b76e616.png)

- Inverse Matrix
    - A $\cdot$ A<sup>-1</sup> = I 인 매트릭스
    - Square Matrix는 Inverse Matrix가 있다.
    - 모든 Matrix에 Inverse Matrix가 있지는 않음

![미디어수학02주차_2](https://user-images.githubusercontent.com/11372675/148757774-d5e36845-4332-4cd8-a459-4b578ca09a14.png)

- System of Linear Equation
    - x-2y = 1
    - 2x+y = 7
$ A = \begin{pmatrix}
\ 1 & -2\\
\ 2 & 1\\
\end{pmatrix}$
$ V = \begin{pmatrix}
\ x \\
\ y \\
\end{pmatrix}$
$\ A \cdot V = \begin{pmatrix}
\ 1 \\
\ 7 \\
\end{pmatrix}$

- L U Factorization
    - 어떠한 Matrix를 소거방법으로 Upper Matrix와 Lower Matrix의 곱으로 표현 가능
        - Upper Matrix와 Lower Matrix는 Triangle Matrix임
        - 굳이 왜?
            - 미지수를 구하기 쉬워짐
            - 1차 방정식 -> 2차 방정식 ...
    - 항상 되는 것은 아님
        - 조건 : 우선 Inverse Matrix가 있어야 함