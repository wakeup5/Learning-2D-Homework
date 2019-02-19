//맵으로 구현.
//1. 입력 : 선택하면 입력창 뜸.
//2. 삭제 : 선택하면 리스트가 뜨고, 번호를 입력하면 삭제. 삭제 되면 삭제 됨, 안되면 실패 함.
//3. 출력 : 전체 출력. 이름과 가격 출력.
//4. 검색 : 이름을 입력하면 있는지 알려줌. 있으면 가격과 이름이, 없으면 없습니다 뜸.

//예) 과일이름 입력 선택하면 과일 입력 가능.
#include <map>
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

void input();
void print();
void del();
void find();

map<string, int> _map;
map<string, int>::iterator _mapIter;

void main()
{
	int inputNum;
	
	while (true)
	{
		system("cls");
		cout << "작업을 선택" << endl;
		cout << "1. 입력\n2. 삭제\n3. 출력\n4. 검색" << endl;
		cin >> inputNum;

		switch (inputNum)
		{
		case 1:
			input();
			break;
		case 2:
			print();
			del();
			break;
		case 3:
			print();
			break;
		case 4:
			find();
			break;
		default:
			cout << "잘못 입력." << endl;
			break;
		}
		_getch();
	}
}

void input()
{
	string inputName;
	int inputPrice;

	cout << "이름 : ";
	cin >> inputName;
	cout << "가격 : ";
	cin >> inputPrice;

	_map.insert(make_pair(inputName, inputPrice));
	cout << "입력 됨." << endl;
}

void print()
{
	if (_map.size() == 0)
	{
		cout << "데이터 없음" << endl;
		return;
	}

	int i = 1;
	for (_mapIter = _map.begin(); _mapIter != _map.end(); _mapIter++, i++)
	{
		cout << i << ". " << _mapIter->first << " - " << _mapIter->second << "원" << endl;
	}
}

void del()
{
	if (_map.size() == 0)
	{
		return;
	}

	string delName;

	cout << "삭제할 이름 : " << endl;
	cin >> delName;

	if (_map.find(delName) != _map.end())
	{
		_map.erase(delName);
		cout << "삭제 완료." << endl;
	}
	else
	{
		cout << "삭제할 이름이 없다." << endl;
	}

	return;

	int delNum;
	cout << "삭제 번호 : ";
	cin >> delNum;

	if (delNum > _map.size() || delNum < 1)
	{
		cout << "잘못 입력." << endl;
		return;
	}

	int i = 1;
	for (_mapIter = _map.begin(); _mapIter != _map.end(); _mapIter++, i++)
	{
		if (i == delNum){
			_map.erase(_mapIter->first);
			break;
		}
	}
	
	cout << "삭제됨" << endl;
}

void find()
{
	string inputName;
	cout << "검색 할 이름 : ";
	cin >> inputName;

	if ((_mapIter = _map.find(inputName)) != _map.end())
	{
		cout << "검색 이름 : " << _mapIter->first << ", 값 : " << _mapIter->second << endl;
	}
	else
	{
		cout << "검색된 내용 없음." << endl;
	}
}