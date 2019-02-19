//������ ����.
//1. �Է� : �����ϸ� �Է�â ��.
//2. ���� : �����ϸ� ����Ʈ�� �߰�, ��ȣ�� �Է��ϸ� ����. ���� �Ǹ� ���� ��, �ȵǸ� ���� ��.
//3. ��� : ��ü ���. �̸��� ���� ���.
//4. �˻� : �̸��� �Է��ϸ� �ִ��� �˷���. ������ ���ݰ� �̸���, ������ �����ϴ� ��.

//��) �����̸� �Է� �����ϸ� ���� �Է� ����.
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
		cout << "�۾��� ����" << endl;
		cout << "1. �Է�\n2. ����\n3. ���\n4. �˻�" << endl;
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
			cout << "�߸� �Է�." << endl;
			break;
		}
		_getch();
	}
}

void input()
{
	string inputName;
	int inputPrice;

	cout << "�̸� : ";
	cin >> inputName;
	cout << "���� : ";
	cin >> inputPrice;

	_map.insert(make_pair(inputName, inputPrice));
	cout << "�Է� ��." << endl;
}

void print()
{
	if (_map.size() == 0)
	{
		cout << "������ ����" << endl;
		return;
	}

	int i = 1;
	for (_mapIter = _map.begin(); _mapIter != _map.end(); _mapIter++, i++)
	{
		cout << i << ". " << _mapIter->first << " - " << _mapIter->second << "��" << endl;
	}
}

void del()
{
	if (_map.size() == 0)
	{
		return;
	}

	string delName;

	cout << "������ �̸� : " << endl;
	cin >> delName;

	if (_map.find(delName) != _map.end())
	{
		_map.erase(delName);
		cout << "���� �Ϸ�." << endl;
	}
	else
	{
		cout << "������ �̸��� ����." << endl;
	}

	return;

	int delNum;
	cout << "���� ��ȣ : ";
	cin >> delNum;

	if (delNum > _map.size() || delNum < 1)
	{
		cout << "�߸� �Է�." << endl;
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
	
	cout << "������" << endl;
}

void find()
{
	string inputName;
	cout << "�˻� �� �̸� : ";
	cin >> inputName;

	if ((_mapIter = _map.find(inputName)) != _map.end())
	{
		cout << "�˻� �̸� : " << _mapIter->first << ", �� : " << _mapIter->second << endl;
	}
	else
	{
		cout << "�˻��� ���� ����." << endl;
	}
}