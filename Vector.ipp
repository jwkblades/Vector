#include "Vector.h"

template<typename T> Vector<T>::Vector(void)
{
	mArray = NULL;
	mSize = 0;
	mNextIndex = 0;
	resize(100);
}

template<typename T> Vector<T>::~Vector(void)
{
	delete [] mArray;
	mArray = NULL;
	mSize = mNextIndex = 0;
}

template<typename T> void Vector<T>::append(const T& item)
{
	if (mSize == mNextIndex)
	{
		resize(mSize + 100);
	}

	mArray[mNextIndex] = item;
	mNextIndex++;
}

template<typename T> void Vector<T>::erase(const Vector<T>::iterator& location)
{
	std::size_t index = location.mIndex;

	for (; index < mNextIndex; index++)
	{
		mArray[index] = mArray[index + 1];
	}
	mNextIndex--;
}

template<typename T> void Vector<T>::erase(const Vector<T>::iterator& first, const Vector<T>::iterator& last)
{
	std::size_t index = first.mIndex;
	std::size_t takeFrom = last.mIndex;

	for (; takeFrom < mNextIndex; index++, takeFrom++)
	{
		mArray[index] = mArray[takeFrom];
	}
	mNextIndex -= (takeFrom - index);
}

template<typename T> typename Vector<T>::iterator Vector<T>::begin(void)
{
	Vector<T>::iterator iter(0, this);
	return iter;
}
template<typename T> typename Vector<T>::iterator Vector<T>::end(void)
{
	Vector<T>::iterator iter(mNextIndex, this);
	return iter;
}

template<typename T> T& Vector<T>::operator[](std::size_t index)
{
	if (index >= mNextIndex)
	{
		throw "Error: Index out of bounds.";
	}
	return mArray[index];
}
template<typename T> const T& Vector<T>::operator[](std::size_t index) const
{
	if (index >= mNextIndex)
	{
		throw "Error: Index out of bounds.";
	}
	return mArray[index];
}

template<typename T> void Vector<T>::resize(std::size_t newSize)
{
	if (newSize < mSize)
	{
		throw "Error: Can't shrink vector..."; // Left to the user.
	}

	T* newArray = new T[newSize];
	for (std::size_t index = 0; index < mNextIndex; index++)
	{
		newArray[index] = mArray[index];
	}
	mSize = newSize;

	delete [] mArray;
	mArray = newArray;
}

template<typename T> Vector<T>::iterator::iterator(std::size_t index, Vector<T>* parent)
{
	mValid = true;
	mVector = parent;
	mIndex = index;
}
template<typename T> Vector<T>::iterator::~iterator(void)
{
	mVector = NULL;
	mValid = false;
	mIndex = 0;
}

template<typename T> bool Vector<T>::iterator::operator==(const Vector<T>::iterator& other) const
{
	return mValid == other.mValid && mVector == other.mVector && mIndex == other.mIndex;
}
template<typename T> bool Vector<T>::iterator::operator!=(const Vector<T>::iterator& other) const
{
	return !((*this) == other);
}

template<typename T> const T& Vector<T>::iterator::operator->(void) const
{
	try
	{
		return (*mVector)[mIndex];
	}
	catch(...)
	{
		mValid = false;
		throw;
	}
}
template<typename T> T& Vector<T>::iterator::operator->(void)
{
	try
	{
		return (*mVector)[mIndex];
	}
	catch(...)
	{
		mValid = false;
		throw;
	}
}
template<typename T> const T& Vector<T>::iterator::operator*(void) const
{
	try
	{
		return (*mVector)[mIndex];
	}
	catch(...)
	{
		mValid = false;
		throw;
	}
}
template<typename T> T& Vector<T>::iterator::operator*(void)
{
	try
	{
		return (*mVector)[mIndex];
	}
	catch(...)
	{
		mValid = false;
		throw;
	}
}

template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator++(void)
{
	return (*this)++;
}
template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator++(int)
{
	mIndex++;
	return *this;
}

template<typename T> int Vector<T>::iterator::operator-(const Vector<T>::iterator& other) const
{
	return mIndex - other.mIndex;
}
template<typename T> bool Vector<T>::iterator::operator<(const Vector<T>::iterator& other) const
{
	return mIndex < other.mIndex;
}
template<typename T> typename Vector<T>::iterator Vector<T>::iterator::operator+(int offset) const
{
	return Vector<T>::iterator(mIndex + offset, mVector);
}
template<typename T> typename Vector<T>::iterator Vector<T>::iterator::operator-(int offset) const
{
	return Vector<T>::iterator(mIndex - offset, mVector);
}


template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator--(void)
{
	return (*this)--;
}
template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator--(int)
{
	mIndex--;
	return *this;
}

template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator+=(std::size_t offset)
{
	mIndex += offset;
	return *this;
}
template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator-=(std::size_t offset)
{
	mIndex -= offset;
	return *this;
}

template<typename T> typename Vector<T>::iterator& Vector<T>::iterator::operator=(const Vector<T>::iterator& src)
{
	if (this == &src)
	{
		return *this;
	}
	mValid = src.mValid;
	mIndex = src.mIndex;
	mVector = src.mVector;
	return *this;
}

