# My Fault - 스스로 불러온 재앙
------------------
## System.Random 과 UnityEngine.Random
- UnityEngine.Random은 고유의 숫자 생성기를 사용함. 그리고 이것을 static memeber class로 넘겨주기에 새로 필요할 때 새로운 숫자 생성기를 만들지 않음
    - 글로벌 인스턴스를 사용하므로 서로 다른 랜덤 값이 영향을 줄 수 있다
    - UnityEngine.Random.InitState()값을 세팅할 때 시드값이 변화가 없으면 매번 똑같은 형식으로 나올 수 있음
- UnityEngine.Random은 새로운 random을 사용하려면 새로운 숫자 생성기를 만듦
    - 각각 인스턴스 형식으로 생성되었기에 서로 영향을 주지 않는다.