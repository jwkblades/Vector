#include <iostream>
using namespace std;

#include "Vector.h"

int main(void)
{
	Vector<int> myVector;

	for (int i = 0; i < 10; i++)
	{
		myVector.append(i);
	}

	cout << endl << "Initial vector: " << endl;
	for (int& myInt : myVector)
	{
		cout << "Vector item: " << myInt << endl;
	}

	Vector<int>::iterator first = myVector.begin();
	for (int i = 0; i < 3; i++, first++);

	Vector<int>::iterator second = first;
	for (int i = 0; i < 3; i++, second++);

	myVector.erase(first, second);

	cout << endl << "After removing items: " << endl;
	for (int& myInt : myVector)
	{
		cout << "Vector item: " << myInt << endl;
	}

	for (int i = 10; i < 1001; i++)
	{
		myVector.append(i);
	}

	first = myVector.begin();
	second = first;
	first += 5;
	second += 990;
	myVector.erase(first, second);
	
	for (int& myInt : myVector)
	{
		cout << "Vector item: " << myInt << endl;
	}

	return 0;
}
