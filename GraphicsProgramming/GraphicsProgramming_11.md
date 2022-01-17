# 그래픽스 프로그래밍 #11 - 3D Model
## 간단한 3D 모델 Class
- 3D 객체를 정의하는 요소들
    - 버텍스 속성(지오메트리 관련)
        - 3차원 위치, 2차원 텍스처 좌표, 3차원 노말, 인덱스
    - 재질 속성
        - Diffuse 텍스처, Specular 텍스처, Shininess
        - 기본 Ambient, Diffuse, Specular 컬러(텍스처가 없을 경우 사용함)
    - OpenGL 오브젝트
        - VAO,VBO,EBO
- 3D 객체와 관련된 절차
    1. 버텍스 속성 값 하드코딩하기
    2. VAO, VBO, EBO, texture 오브젝트 생성하기(glGen...함수들)
    3. 텍스처 이미지 로드하기(stbi_load)
    4. 버퍼에 값 복사해서 채워 넣기(ex. glBufferData)
    5. 이미지 데이터 OpenGL 텍스처로 연결하고 설정(glTexImage2D)
    6. 버텍스 속성 연결하기(glVertexAttribPointer)
    7. Uniform 설정하기(glUniform...함수들)
    8. 쉐이더 프로그램 사용해서 그리기(ex. glDrawArrays)
    - 1~6 : startup, 7~8 : render
- 단순한 클래스 변수와 메소드
    - 변수
        ``` C++
        public:
            std::vector<vmath::vec3>vPositions;
            std::vector<vmath::vec3>vTexCoords;
            std::vector<vmath::vec3>vNormals;
            std::vector<GLuint>vIndices;
            GLUint diffuseMap, specularMap;
            float shininess;
            vmath::vec3 defaultAmbient,defaultDiffuse,defaultSpecular;
        private:
            GLuint VAO;
            // 원래는 VAO 하나만 썼는데, position,texcoord,normal이렇게 3개로 나누어서 관리
            GLuint VBO_positions, VBO_texCoords,VBO_normals;
            GLuint EBO;
            bool useDiffuseMap, useSpecularMap;
        ```
        ``` C++
        public:
            void Init(); // OpenGL 오브젝트 생성
            void setupMesh(); // 버텍스 속성들을 입력 받아 저장
            void setupIndices(); // 인덱스들을 입력 받아 저장
            bool loadDiffuseMap(); // Diffuse텍스처 맵 설정
            bool loadSpecularMap(); //Specular 텍스처 맵 설정
            void draw(); // 모델 그리기
        private:
            void prepareBuffers(); // OpenGL 버퍼 채우기
            void loadTextureFile(); // 이미지 파일로 부터 텍스처 생성
        ```
- obj 파일 포맷
    - 점 위치를 하드코딩하는 것도 엄청 어려움
    - 더 복잡하고 멋진 객체는?(모델링 소프트웨어 활용)
        - Blender,3ds max, maya
    - open source임
    - 텍스트로 되어있음
        - 열어보면 v, vt, vn 이런 것들로 구성되어있음
    - 구성
        - vertex Positions
            - // V X Y Z
            - v 0.437500 0.164063 0.765625
        - Vertex Texture Coordinates
            - //vt U V
            - vt 0.376478 0.613349
        - Vertex Normals
            - // vn X Y Z
            - vn 0.073672 -0.594989 0.800317
        - Face Indices
            - // f v1 v2 v3
            - f 63 65 61
            - // f v1/vt1 v2/vt2 v3/vt3
            - f 63/7 65/2 61/1
            - // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
            - f 63/7/7 65/2/2 61/1/1
            - // f v1//vn1 v2//vn2 v3//vn3
            - f 63//7 65//2 61//1
        - 더 많은 정보들
            - vetex color
            - point line
            - free form curve/surface
            - group 정보
            - material
            - etc...