#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


#include "Vector.h"

/**
 * Template specialization for for our custom int vector class (don't use this
 * for production code!) to give it the necessary items to work with std::sort.
 */
namespace std
{
	template<>
	struct iterator_traits<typename Vector<int>::iterator>
	{
	public:
		typedef int value_type;
		typedef int difference_type;
		typedef random_access_iterator_tag iterator_category;
	};
}

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

	myVector.erase(myVector.begin(), myVector.end());
	std::srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		myVector.append(std::rand());
	}

	cout << endl << "Sorting (randomized): " << endl;
	for (int& myInt : myVector)
	{
		cout << "Vector item: " << myInt << endl;
	}
	std::sort(myVector.begin(), myVector.end());
	cout << endl << "Sorted vector: " << endl;
	for (int& myInt : myVector)
	{
		cout << "Vector item: " << myInt << endl;
	}

	return 0;
}
