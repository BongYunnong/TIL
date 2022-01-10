# My Fault - 스스로 불러온 재앙
## C++ Delay
- C++로 delay를 어떻게 사용할 수 있을까 검색해봤는데 아래와 같은 코드가 있었다.
    ```
        FTimerHandle waitHandle;
        GetWorld()->GetTimerManager().SetTimer(waitHandle, FTimerDelegate::CreateLambda([&]() {
            //UpdateAmmo(addCount);
            //GetWorld()->GetTimerManager().ClearTimer(waitHandle);
        }), tmpWaitTime, false);
    ```
    - 해석을 해보면, tmpWaitTime만큼의 delay 후에 Lambda식 안에 있는 코드들을 delegate로 실행을 하되, loop하지는 않는다는 것이다.
    - 이렇게만 보면 내가 찾던 것이었는데, 문제는 매개변수가 제대로 들어가지 않았다. 나는 분명 addCount에 1을 넣었는데 Log를 찍어보면 6230(예시) 이런 숫자들이 찍혔다. 마치 range를 벗어나서 생기는 것 같았다.
- 그래서 다른 방법을 찾아봤는데, 그것은 다음과 같다.
    ```
        FTimerHandle waitHandle;
        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &APrototypeCharacter::UpdateAmmo, addCount);
        GetWorld()->GetTimerManager().SetTimer(waitHandle, TimerDelegate, waitTime, false);
    ```
    - 위와의 차이점은 Delegate를 선언을 해준 뒤 사용한다는 것인데, 이렇게 하면 매개변수를 전달해줬을 때 제대로 찍히는 것을 확인했다.
    - 그런데 문제점은 하나의 함수만 사용이 가능하다는 것이었다.
        - Delegate니까 나중에 더하면 되나? -> +=이걸로 해보니 안된다.
## Blueprint For Loop with Delay
- C++로 delay주는 것을 실패하고 그냥 블루프린트로 구현하려했다.
- 그런데 블루프린트에도 문제가 있었는데 그냥 for loop의 body에 delay를 주면 그걸 무시하고 Completed로 갔다.
- 이것을 해결하는 방법은 매크로를 새로 만드는 방법이었다.
![image](https://user-images.githubusercontent.com/11372675/148753799-d2657431-c3a7-4af0-9cbd-fd2f5b1ecef5.png)