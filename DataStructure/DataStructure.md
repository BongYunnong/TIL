- 자료구조란?
    - 사전적 의미 : 자료의 집합으로 각 원소들이 논리적으로 정의된 규칙에 의해 나열되며 자료에 대한 처리를 효츌적으로 수행할 수 있도록 자료를 구분하여 표현한 것.
    - 목적 : 자료를 저장, 관리를 더 효율적으로 하기 위함으로 실행시간의 단축(시간복잡도)와 메모리 용량의 절약(공간복잡도)을 목적으로 자료구조를 선택

- 자료구조는 크게 선형구조와 비선형 구조로 나뉜다.
    - 선형구조 : 순차 리스트(선형 리스트), 연결 리스트, 스택, 큐 , Deque
    - 비선형 구조 : 트리, 그래프
- 선형 리스트
    - 배열이라고 보면 됨
    - 연속적인 주소에 저장된다.
    - 접근이 빠르고, 삽입 및 삭제가 느리다.
    - 기억 공간 효율이 좋음(locality?)
    - index를 통해 자료를 읽어온다.
        - index에서 요소를 읽어내는 속도는 동일하기에(Random Access) 매우 빠름
        - 하지만 어떠한 값이 어떤 주소에 있는지는 하나씩 다 찾아봐야함(Searching)
    - 삽입 및 삭제가 느리다
        - 어떠한 값을 맨 마지막에 넣는 것은 length를 알기에 매우 쉬움
        - 하지만 중간에 넣고싶다면? 자리를 만들기 위해 그 지점 이후의 값들을 다 밀어내야함
        - 배열의 공간이 다 사용중이라면? 새로운 더 넒은 공간을 만들어서 값들을 다 복사한 뒤 삽입해야한다.
- 연결 리스트
    - 노드의 포인터 부분을 연결한 리스트
    - 접근이 느림, 삽입 및 삭제가 빠름
    - 기억 공간 효율 별로임
    - 길이가 변해야 한다면 연결 리스트를 쓰는 것이 좋음
    - 단순 연결 리스트, 이중 연결 리스트가 있음
    - 단방향 연결 리스트
        - 한 쪽으로만 이동이 가능
        
        ```cpp
        class Node{
        	int data;
        	Node next = null;
        	Node(int d){
        		this.data = d;
        	}
        	void append(int d){
        		Node end = new Node(d);
        		Node n = this;
        		//연결 리스트의 마지막까지 찾는다.
        		while(n.next != null){
        			n = n.next;
        		}
        		n.next= end;
        	}
        	void delete(int d){
        		Node n = this;
        		while(n.next != null){
        			//먼저 다음 node를 보고, 그것이 내가 찾던 것이라면 그 다음 노드를 가리킨다.
        			if(n.next.data == d){
        				n.next = n.next.next;
        			}else{
        				n = n.next;
        			}
        		}
        		// next를 보고 지우게 되면 첫 번째 노드는 못 지우는 것 아닌가?
        		// linked list자체가 next를 통해 찾는 것이라 못 지우는 것이 맞음
        	}
        	void retrieve(){
        		Node n = this;
        		while(n.next != null){
        			print(n.data+"->");
        			n= n.next;
        		}
        		print(n.data);
        	}
        }
        ```
        
        ```cpp
        class LinkedList{
        	class Node{
        		int data;
        		Node next= null;
        	}
        	Node header;
        	LinkedList(){
        		header = new Node();
        	}
        	void append(int d){
        		Node end = new Node();
        		end.data = d;
        		Node n = header;
        		while(n.next != null){
        			n = n.next;
        		}
        		n.next= end;
        	}
        	void delete(int d){
        		Node n = header;
        		while(n.next != null){
        			if(n.next.data == d){
        				n.next = n.next.next;
        			}else{
        				n = n.next;
        			}
        		}
        	}
        	void retrieve(){
        		Node n = header.next;
        		while(n.next != null){
        			print(n.data+"->");
        			n= n.next;
        		}
        		print(n.data);
        	}
        }
        ```
        
    - 양방향 연결 리스트
        - 앞 뒤로 이동이 가능
        - 아무래도 메모리를 잡아먹기 때문에 단방향 연결 리스트로 해결하면 그냥 단방향을 쓰자

- 큐와 스택은 추상적인, 일종의 규칙이다.ADT(Abstract Data Type)

- 큐
    - 한 방향에서는 삽입만, 다른 방향에서는 삭제만 이루어진다.
    - FIFO(First in First out)

- 스택
    - 삽입, 삭제가 한 방향으로만 이루어짐
    - LIFO(Last in  First out)

- 데크(Deque)
    - 양쪽 방향에서 삽입, 삭제가 이루어진다.
    - 스택과 큐가 합쳐짐
    
- 그래프
    - 노드와 간선으로 이뤄진 자료구조
    - cycle이 존재할 수 있다.
    - 구성 : vertex, edge
    - directed graph, undirected graph

- 트리
    - 그래프의 한 종류(Directed Acyclic Graph)
    - 노드와 간선으로 이루어진 사이클 없는 자료구조
    - 구성 : 노드, root(최상위 노드), leaf(단말노드), degree(자식의 개수), depth(루트 노드로부터의 거리), size(모든 노드의 개수), height(깊이 중 최댓값)
    - 트리의 크기가 N일 때, 간선의 개수는 N-1
    - 이진트리: 자식 노드를 최대 2개 가지는 트리
        - 완전 이진트리 : 왼쪽 자식 노드부터 채워져 마지막 레벨을 제외하고는 모든 자식 노드가 채워짐
        - 포화 이진트리 : 모든 노드가 0 혹은 2개의 자식 노드를 가지며 모든 리프 노드의 레벨이 같은 트리
        - 편향 이진트리 : 모든 노드가 한 방향으로만 편향된 트리
        - 힙 : 우선순위 큐를 위해 만들어진 자료구조
            - 최소 힙 : 부모 노드의 키 값이 자식 노드의 키 값보다 작거나 같은 완전 이진 트리
            - 최대 힙 : 부모 노드의 키 값이 자식 노드의 키 값보다 크거나 같은 완전 이진 트리
        - 이진 탐색 트리(Binary Search Tree)
            - 이진 탐색이 동작할 수 있도록 고안된 효율적인 탐색이 가능한 자료구조
            - 왼쪽 자식 노드 < 부모 노드 < 오른쪽 자식 노드
            - 어떠한 값을 찾기 위해서는 찾고자 하는 값이 노드보다 큰 지, 아닌지 확인
            - 트리 순회 방법
                - 전위 순회(Pre-Order Traverse) : 루트를 먼저 방문
                - 중위 순회(In-Order Traverse) : 왼쪽 자식을 방문한 뒤에 루트 방문
                - 후위 순회(Post-Order Traverse) : 오른쪽 자식을 방문한 뒤에 루트를 방문
            
            ```cpp
            class Node{
            	Node(self, data, left_node, right_node){
            		self.data = data;
            		self.left_node = left_node;
            		self.right_node = right_node;
            }
            void preOrder(node){
            	print(node.data+"->");
            	if(node.left_node != null)
            		preOrder(tree[node.left_node])
            	if(node.right_node != null)
            		preOrder(tree[node.right_node])
            }
            void inOrder(node){
            	if(node.left_node != null)
            		inOrder(tree[node.left_node])
            	print(node.data+"->");
            	if(node.right_node != null)
            		inOrder(tree[node.right_node])
            }
            void postOrder(node){
            	if(node.left_node != null)
            		postOrder(tree[node.left_node])
            	if(node.right_node != null)
            		postOrder(tree[node.right_node])
            	print(node.data+"->");
            }	
            ```
            

---

- 해쉬 테이블
    - 선형 검색이 너무 느리기 때문에<O(n)> key값으로 value를 찾음<O(1)>
    - 삽입, 삭제도 O(1)임
    - 해쉬 안에는 array로 구성되어있는데 어떻게 더 빠른가?
        - Hash Function → key를 input으로 넣으면 index를 output. 이 값으로 array에 접근해서 value에 접근한다.
        - Collision(해시 충돌) → 다른 key를 넣었는데 같은 output이 나왔을 때.
            - 충돌한 index안에 새로운 array를 만드는 방법 → 이때 선형 검색
        - 항상 O(1)인 것은 아님
- 우선순위 큐
    - 우선순위가 가장 높은 데이터를 먼저 삭제하는 자료구조
    - 리스트 구현
        - 삽입 시간 : O(1), 삭제 시간:O(N)
    - 힙 구현
        - 삽입 시간 : O(logN), 삭제 시간:O(logN)
        - 최소 힙, 최대힙으로 정렬한 뒤 루트 노드를 제거
        - Min Heapify() : 부모보다 자신의 값이 더 작을 경우 위치 교체
        - Max Heapify() : 부모보다 자신의 값이 더 클 경우 위치 교체
        - 원소를 제거할 때는 가장 마지막 노드가 루트 노드의 위치에 오도록 함
    
    ```cpp
    void heapSort(vector<int>& arr){
    	priority_queue<int> h;
    	for(int i=0;i<arr.size();i++){
    		h.push(-arr[i]);
    	}
    	while(!h.empty()){
    		printf("%d\n",-h.top());
    		h.pop();
    	}
    }
    ```
    
- C#에서 key와 value를 사용해서 자료구조를 저장하는 타입은 2가지가 있다.
- 해시테이블
    - Non-Generic, Key와 Value 모두 Object를 입력받는다.(모든 데이터 타입 처리 가능)
    - 박싱, 언박싱을 사용한다.
- 딕셔너리
    - Generic, Key와 Value 모두 Strong Type을 입력받는다.(선언 시 타입 입력 필요)
    - 박싱, 언박싱이 없음