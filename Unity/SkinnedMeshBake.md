# Skinned Mesh Bake로 잔상 만들기

## Skinned Mesh Renderer
- 블렌더같은 모델링 툴에서 리깅을 한 후에 FBX로 export해서 유니티에 import해보면 SkinnedMeshRenderer라는 컴포넌트가 추가되어있다.
- skinned mesh renderer는 mesh renderer와는 다르게 rigging된 메쉬를 render할 수 있다.
- 이 컴포넌트에는 다양한 멤버 변수, 함수가 존재한다.
- 그 중에서 잔상을 만드는 데에 필요한 것은 BakeMesh라는 함수이다.

## BakeMesh
- 말 그대로 skinnedMeshRenderer의 타겟 메쉬를 Bake해서 다른 메쉬에 넘겨주겠다는 것이다.
``` C#
Mesh tmpMesh = new Mesh();
SMR.BakeMesh(tmpMesh);
```
- 위의 코드는 SMR의 타겟 메쉬를 구워서 tmpMesh에 할당하는 코드이다.

## mesh와 sharedmesh
- 이번에 새로 알게된 것은 mesh는 기본적으로 인스턴스화하지 않는다는 것이다.
- mesh와 sharedmesh의 차이점이 인스턴스와 shared의 차이라고 생각을 했는데, 내가 짠 코드 중 현재 index의 메쉬를 다음 index의 메쉬 필터에 차례차례 넘겨주는 코드에서 내 의도대로 작동하지 않는 것을 확인할 수 있었다.
- 글이 2011년도 글이라서 지금은 정확하지는 않지만, mesh는 obsolete하기에, sharedmesh의 역할을 한다고 한다.
- 그렇게 생각하면 말이 되는 것이, 첫 번째의 mesh는 바로 구워서 적용이 되었고, 그 이후의 mesh들은 다 index에 따라 전달받지 않고 모두 첫 번째의 mesh를 이어받았기 때문이다.
- 그래서 내가 생각한 방식은 mesh의 vertices와 triangles를 copy하는 방식이었다.
- 말하자면 메모리를 참조하는 것이 아니라 깊은 복사를 하는 것이었다.
- 그러자 내 의도대로 Motion Trail이 작동하기 시작했다.

## 꾸미기
- 그냥 잔상이 남는 것 까지는 되었지만 이대로는 별로 멋이 없었다.
- 그래서 뒤쪽 잔상일수록 alpha값을 index에 비례하게 낮춰주었다.
- 추가로 ShaderGraph로 Fresnel effect를 적용한 매터리얼을 생성해 HDR컬러를 적용할 수 있게 exposed했다.
- 스크립트에서 alpha값과 마찬가지로 parameter Name을 통해 alpha,front Color, front inner color, back color, back inner color를 설정할 수 있었다.

- 추가적으로 Trail의 Count와 Trail 사이의 Gap을 지정할 수 있게 만들었다.