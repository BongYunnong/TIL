# Timeline


## 기초
- Timeline 애셋 필요
- Playable Director 컴포넌트를 추가해서 Timeline 적용
    - Animator도 생성되는데 지워도 된다 함

## Track
- Activation Track

- Animation Track
    - Animator가 있는 오브젝트를 변형 가능
    - 타임라인에 있는 클립과 컨트롤러의 클립 중복됨
        - 클립을 지우거나, 타임라인에서의 애니메이션 트랙을 사용하지 않는 것 권장
    - recording 혹은 animation clip 드래그앤 드롭
        - recording을 한 것은 Convert to clip track으로 변환 가능
        - 변환된 트랙은 Convert to infinite clip을 통해 반복 가능
        - 클립을 더블클릭하면 Animation tab에서 수정 가능
- Audio Track

- Control Track
    - 프리팹을 넣어주면 생성됨
    
- Signal Track
    - 사용할 오브젝트에 Signal Receiver 추가
    - Signal Track 추가하고 Signal Receiver 넣기
    - 우클릭 -> Add Signal Emitter -> Create Signal -> Action 추가하기
- Playable Track

- Cinemachine Track

## additional
- Clip blending
    - Ease In/ Ease Out
- Animation Extrapolation
    - 클립이 끝난 뒤
    1. Hold : 마지막 키프레임 유지
    2. Loop : 다시시작
    3. Ping Pong : 역재생->재생->역재생
    4. Continue : 클립에 바인딩 된 Source의 설정에 따라 hold 혹은 loop
- track offset
    1. Apply Transform Offsets : 애니메이션 트랙에서 월드 좌표계 기준으로 설정한 오프셋 값이 시작위치
    2. Apply Scene Offsets : Actor의 씬에서의 월드 좌표계 기준으로 설정한 오프셋값이 시작 위치
    3. Auto (deprecated) : 이전버전에서 로브된 파일을 호환하기 위한 설정
- Clip offset
    - 위치, 회전에 대한 offset
    - Match Offsets to previous/next Clip

## Signal
- 핀 아이콘을 누르면 시그널 등록 가능한 트랙 생성
    - 기본적으로 이 Timeline을 사용하고있는 Director의 Signal Receiver 사용
- 따로 Signal Track을 추가할 수도 있긴 하다. 하지만 바인딩이 필요
- Signal Receiver에 Add Reaction
- 단발성의 특수한 처리(씬 로드, 어플리케이션 등)에 적합하고, 플레이어나 오브젝트 자체에 대한 처리는 별로임
    - 시그널 수가 너무 많아지면 관리하기 힘듦 : 함수가 변형되면 난리날 수 있음
    - Custom Signal을 사용하지 않으면 동일한 아이콘을 사용하기에 구별하기 힘듦
    - -> 플레이어나 오브젝트 처리는 Custom Playables나 Custom Track, Clip을 제작하는 것이 좋다.

## Scripting
- Header : using UnityEngine.Playables;
``` C#
public PlayableDirector playableDirector;
void Start(){
    playableDirector.Play();
    playableDirector.Pause();
    playableDirector.Stop();
}
```

## Playables
- Playing a single clip on a GameObject
    ``` C#
    using UnityEngine;
    using UnityEngine.Experimental.Director;
    [RequireComponent(typeof(Animator))]
    public class PlayAnimation : MonoBehaviour{
        public AnimationClip clip;
        void Start(){
            var clipPlayable = new AnimationClipPlayable(clip);
            GetComponent<Animator>().Play(clipPlayable);
        }
    }
    ```
- Creating an animation blend tree
    ``` C#
    using UnityEngine;
    using UnityEngine.Experimental.Director;
    [RequireComponent(typeof(Animator))]
    public class MixAnimation : MonoBehaviour{
        public AnimationClip clip1;
        public AnimationClip clip2;

        private AnimationMixerPlayable m_Mixer;

        void Start(){
            m_Mixer = new AnimationMixerPlayable();
            m_Mixer.SetInputs(new[] {clip1, clip2});

            GetComponent<Animator>().Play(m_Mixer);
        }
        void Update(){
            float weight = (Time.time % 10)/10;
            m_Mixer.SetInputWeight(0, 1- weight);
            m_Mixer.SetInputWeight(1,, weight);
        }
    }
    ```
- Blending AnimatorController
    ``` C#
    using UnityEngine;
    using UnityEngine.Experimental.Director;
    [RequireComponent(typeof(Animator))]
    public class MixAnimation : MonoBehaviour{
        public AnimationClip clip;
        public RuntimeAnimatorController animController;
        AnimationMixerPlayable mixer;
        void Start(){
            var clipPlayable = new AnimationClipPlayable(clip);
            var controllerPlayable = new AnimatorControllerPlayable(animController);
            mixer = new AnimationMixerPlayable();
            mixer.SetInputs(new AnimationPlayable[] {clipPlayable, controllerPlayable});
            GetComponent<Animator>().Play(mixer);
        }
        void Update(){
            float weight = (Time.time % 10)/10;
            m_Mixer.SetInputWeight(0, 1- weight);
            m_Mixer.SetInputWeight(1,, weight);
        }
    }
    ```
- Controlling the timing of tree
    ``` C#
    using UnityEngine;
    using UnityEngine.Experimental.Director;
    [RequireComponent(typeof(Animator))]
    public class PlayWithTimeControl : MonoBehaviour{
        public AnimationClip clip;
        private Playable root;
        private const float speedFactor = 1f;
        void Start(){
            root = new AnimationClipPlayable(clip);
            GetComponent<Animator>().Play(root);
            root.state = PlayState.Paused;
        }
        void Update(){
            float horizontalInput = Input.GetAxis("Horizontal");
            root.time += horizontalInput * speedFactor * Time.deltaTime;
        }
    }
    ```
- Custom Playables
    ``` C#
    using UnityEngine.Playables;
    public class TimeDilationMixerBehaviour : PlayableBehaviour{
        readonly float defaultTimeScale = 1f;
        public override void ProcessFrame(Playable playable, FrameData info, object playerData){
            ...
        }
    }
    ```
- Default Playables
    - 공식 지원 애셋
    - https://assetstore.unity.com/packages/essentials/default-playables-95266
    - Playables Wizard : 커스텀 플레이어블을 쉽게 만들 수 있는 에디터

- Playables Wizard
    - 이름, 트랙 색상, 블렌드 타입, 바인딩 컴포넌트 선택, 변수 선택 등 필수적인 요소를 기반으로 빠르게 스크립트 제작
    - Window -> Timeline Playable Wizard...
    - Exposed References(씬에 존재), Behaviour Variables(값만 존재)는 클립에 바인딩되는 변수(참조, 값)
    - 스크립트
        1. ~Track.cs : 트랙 색상, 바인딩 타입 등
        2. ~Clip.cs : 클립 생성에 관여
        3. ~Behaviour.cs : 인스펙터 창에 나오는 변수들
        4. ~MixerBehaviour.cs : ProcessFrame()함수를 override하여 사용. 클립에 들어갈 때, 진행중일 때, 빠져나올 때, 블렌딩 될 때 등등의 처리 가능
        5. ~Drawer.cs(Editor) : 클립 에디터

- ProcessFrame()
    - Unity Play를 하지 않고 Timeline Play만 해도 함수가 호출됨
    ``` C#
    public override void ProcessFrame(Playable playable, FrameData info, object playerData){
        // 트랙에 존재하는 클립 개수
        int inputCount = playable.GetInputCount();
        int currentInputCount = 0;
        for(int i=0;i<inputCount;i++){
            float inputWeight = playable.GetInputWeight(i); // 0~1사이의 float값 -> 현재 재생중인 곳의 클립 여부 검사 가능
            if(inputWeight > 0f)
                currentInputCount++;
        }
        if(currentInputCount == 0)
        {
            // 클립이 없는 곳을 지나는 중
        }else if(currentInputCout == 1){
            //클립이 1개인 곳을 지나는 중
        }else{
            //클립이 2개 이상인 블렌딩되고 있는 곳을 지나는 중 
        }
    }
    ```


## 주의점
- 루트모션은 이동트랙과 중첩됨..
- 같은 Animator에서 하나는 clip, 하나는 recording으로 중첩해서 사용하면? 실제 Play와 Timeline Play의 결과가 달라진다.
    - 원인 : Offsets 설정들 간의 충돌
        - Apply Scene Offsets를 설정하고 Clip Transform Offsets가 조금이라도 들어있으면 이런 현상 생김


## 기본 마커
``` C#
public class SimpleMarker : UnityEngine.Timeline.Marker {}
```
- 기본 마커는 시각적 항목이라서 트리거 시 코드를 실행할 수 없음
- 하지만 스냅 포인트 또는 주석의 역할 가능
- 에디터 및 런타임의 타임라인 API를 통해서도 액세스 가능
    ``` C#
    public IEnumerable<IMarker> GetMarkers()
    ```
## Playable 알림
- PlayableGraph가 처리되는 동안 오브젝트에 알림을 보낼 수 있다.
- INotification인터페이스를 구현하는 notification 클래스를 생성
    ``` C#
    public class MyNotification:INotification{
        public PropertyName id {get;}
    }
    ```
- INotificationReceiver 인터페이스를 구현하는 receiver 클래스 생성
    ``` C#
    class ReceiverExample : INotificationReceiver{
        public void OnNotify(Playable origin, INotification notification, object context){
            if(notification != null){
                double time = origin.IsValid() ? origin.GetTime() : 0.0;
                Debug.LogFormat("Received notification of type {0} at time {1}", notification.GetType(), time);
            }
        }
    }
    ```
- AddNotificationReceiver 메서드를 사용
    - Playable Output에서 PushNotification 메서드 사용하여 새 알림 푸시 가능
    ``` C#
    public class ManualNotification : MonoBehaviour{
        PlayableGraph m_Graph;
        ReceiverExample m_Receiver;
        void Start(){
            m_Graph = PlayableGraph.Create("NotificationGraph");
            var output = ScriptPlayableOutput.Create(m_Graph,"NotificationOutput");
            // Create and Register a receiver
            m_Receiver = new ReceiverExample();
            output.AddNotificationReceiver(m_Receiver);

            // Push a notification on the output
            output.PushNotification(Playable.Null, new MyNotification());
            m_Graph.Play();
        }
    }
    ```
    - 주의점 : PushNotification은 호출되자마자 알림이 전송되는 것이 아니라 대기열에 올라가서 그래프가 완전히 처리될 때까지 대기열에 누적됨
        - LateUpdate 단계 바로 직전에 대기열에 있는 모든 알림이 그래프의 출력으로 전송되고, 모든 알림이 전송되면 대기열이 비워지고 새로운 프레임 시작
    - 그래프가 재생되면 OnNotify 메서드가 인수로 전송된 알림과 함께 m_Receiver 인스턴스에 호출됨
        ```
        Received notification of type MyNotification at time 0
        ```

## TimeNotificationBehaviour
- Playable Graph를 통해 원하는 시간에 알림 전송되도록 하기
- TimeNotificationBehaviour
    ``` C#
    public class ScheduleNotification : MonoBehaviour{
        PlayableGraph m_Graph;
        ReceiverExample m_Receiver;
        void Start(){
            m_Graph = PlayableGraph.Create("NotificationGraph");
            var output = ScriptableOutput.Create(m_Graph, "NotificationOutput");

            // Create and Register a receiver
            m_Receiver = new ReceiverExample();
            output.AddNotificationReceiver(m_Receiver);

            // Create a TimeNotificationBehaviour
            var timeNotificationPlayable = ScriptPlayable<TimeNotificationBehaviour>.Create(m_Graph);
            output.SetSourcePlayable(timeNotificationPlayable);

            // Add a notification on the time notification Behaviour
            var notificationBehaviour = timeNotificationPlayable.GetBehaviour();
            notificationBehaviour.AddNotification(2.0, new MyNotification());
            m_Graph.Play();
        }
    }
    ```
    ```
    Received notification of type MyNotification at time 2.00363647006452
    ```
    - 주의점 : AddNotification 메서드는 정확한 시간을 보장하지는 않음

## MarkerNotification
- 타임라인에서 적절한 PlayableGraph를 자동으로 생성하여 알림 처리
``` C#
public class NotificationMarker : Marker, INotification{
    public PropertyName id{get;}
}
```
- 알림을 받을 대상 식별
    - 마커가 타임라인 헤더 영역에 있는 경우, 현재 타임라인을 재생하는 PlayableDirector를 소유한 오브젝트가 알림을 받음
    - 마커가 트랙에 있는 경우 트랙에 바인딩된 오브젝트가 알림을 받음

## 커스텀 스타일
- 핀 아이콘을 원하는 이미지로 변경 가능
- 주석 마커(Annotation Marker)
    - Editor폴더 내 StyleSheets/Extensions폴더에 common.uss라는 파일 추가
        - USS(Unity Style Sheet, Unity 스타일 시트)
        ```
        Annotation{
            width:18px;
            height:18px;
            background-image : resource("Assets/5-Annotation/Editor/pencil.png");
        }
        ```
        ```
        [CustomStype("Annotation")]
        public class Annotation:Marker{
            [TextArea] public string annotation;
        }
        ```
## 클립 알림
``` C#
public class ClipNotificationBehaviour:PlayableBehaviour{
    double m_PreviousTime;
    public override void OnGraphStart(Playable playable){
        m_PreviousTime = 0;
    }
    public override void ProcessFrame(Playable playable, FrameData info, object playerData){
        if((int)m_PreviourTime < (int)playable.GetTime()){
            info.output.PushNotification(playable, nwe MyNotification());
        }
        m_PreviousTime = playable.GetTime();
    }
}
```
- 클립을 처리하는 매 초 알림 푸시
```
Received notification of type MyNotification at time 1.01593019999564
Received notification of type MyNotification at time 2.00227000191808
Received notification of type MyNotification at time 3.01137680560353
```

------------------------------
## Marker와 PlayerBridge
``` C#
using UnityEngine;
using UnityEngine.Playables;
using UnityEngine.Timeline;
public class Test_Marker : Marker, INotification{
    public GameObject testObject;
    public PropertyName id{get{return new PropertyName();}}
}
```
``` C#
using UnityEngine;
using UnityEngine.Playables;
public class Test_PlayerBridge : MonoBehaviour, INotificationReceiver{
    public GameObject youwant;
    public void OnNotify(Playable origin, INotification notification, object context){
        Test_Marker TM = notification as Test_Marker;
        // TM.testObject으로 여러가지 하기
    }
}
```