//�̱۸�ũ�帮��Ʈ 
//�ǵ� �߰�
//�ǵ� ����
//������
//��� ���� ���
//
//���� ���� : ����Ʈ��

//�� : ���ø� Ŭ������ ������Ͽ� ��� �Լ� ���Ǹ� �ؾ� �Ѵ�.
//���� Ŭ������ �Լ��� �������� ������ �ְ�, ���� �� ��ũ�� ���� �Լ��� ���� �Ǵµ�,
//���ø� Ŭ������ ������ �� ��üȭ�� �Ǳ� ������ ������ ����. - http://thrillfighter.tistory.com/199

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

	cout << "������ ���" << endl;
	list.printAllElement();

	cout << "������ ���" << endl;
	list.printReverseAllElement();

	List<char*> list2;

	list2.pushBack("���?");
	list2.printAllElement();
}