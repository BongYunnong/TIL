# Today I Learn

하루하루 배웠던 것들을 정리해보자.

아래는 마크다운 문법을 정리한 것이다.

This is an H1
=============

This is an H2
-------------

# This is a H1
## This is a H2
### This is a H3
#### This is a H4
##### This is a H5
###### This is a H6

> This is a first blockquote
>> This is a second blockqoute
>>> This is a third blockquote
- this can get new mark down element


1. 첫번째
2. 두번째
3. 세번째

* 순서없는 첫번째
    * 순서 없는 두번째
        * 순서 없는 세번째

+ 순서없는 첫번째
    + 순서 없는 두번째
        + 순서 없는 세번째

- 순서없는 첫번째
    - 순서 없는 두번째
        - 순서 없는 세번째


* 순서없는 첫번째
    + 순서 없는 두번째
        - 순서 없는 세번째


This is a normal paragrpah:

    This is a code block.

end code block.

<pre>
<code>
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
</code>
</pre>

```
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
```


```java
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
```

* * *

***

*****

- - -

---------------------------------------


[link keyword][id]

[id]: URL "Optional Title here"

// code
Link: [Google][googlelink]

[googlelink]: https://google.com "Go google"

---------------------------------------

사용문법: [Title](link)
적용예: [Google](https://google.com, "google link")

---------------------------------------
일반적인 URL 혹은 이메일주소인 경우 적절한 형식으로 링크를 형성한다.

* 외부링크: <http://example.com/>
* 이메일링크: <address@example.com>

---------------------------------------
*single asterisks*
_single underscores_
**double asterisks**
__double underscores__
~~cancelline~~

---------------------------------------
![Alt text](/path/to/img.jpg)
![Alt text](/path/to/img.jpg "Optional title")

* 줄 바꿈을 하기 위해서는 문장 마지막에서 3칸이상을 띄어쓰기해야 한다. 
이렇게

* 줄 바꿈을 하기 위해서는 문장 마지막에서 3칸이상을 띄어쓰기해야 한다.___\\ 띄어쓰기
이렇게


-------------------------

|                  | 수학                        | 평가              |  
|:--- | ---: | :---: |  
| 철수             | 90            | 참잘했어요. |  
| 영희           | 50            | 분발하세요. |


-------------------
$$f(x)= if x < x_{min} : (x/x_{min})^a$$  
$$otherwise : 0$$  
$$P(w)=U(x/2)(7/5)/Z$$  
$$p_{\theta}(x) = \int p_{\theta}(2z)p_{\theta}(y\mid k)dz$$  
$$x = argmax_k((x_t-x_u+x_v)^T*x_m)/(||x_b-x_k+x_l||)$$  