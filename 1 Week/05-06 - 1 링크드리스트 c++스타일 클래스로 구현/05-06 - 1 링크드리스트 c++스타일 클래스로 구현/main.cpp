//싱글링크드리스트 
//맨뒤 추가
//맨뒤 삭제
//뒤집기
//모든 원소 출력
//
//개인 공부 : 이진트리

//팁 : 템플릿 클래스는 헤더파일에 멤버 함수 정의를 해야 한다.
//보통 클래스는 함수의 원형만을 가지고 있고, 실행 시 링크를 통해 함수가 실행 되는데,
//템플릿 클래스는 컴파일 시 구체화가 되기 때문에 오류가 난다. - http://thrillfighter.tistory.com/199

#include <iostream>
#include "List.h"

using namespace std;

void main()
{
	List<int> list;
	
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(5);
	list.pushBack(6);
	list.pushBack(7);
	list.pushBack(8);
	list.pushFront(100);
	//list.popBack();
	//list.popFront();
	list.insert(9, 123111);
	list.erase(2);

	cout << "정방향 출력" << endl;
	list.printAllElement();

	cout << "역방향 출력" << endl;
	list.printReverseAllElement();

	List<char*> list2;

	list2.pushBack("헬로?");
	list2.printAllElement();
}