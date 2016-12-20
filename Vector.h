#ifndef __VECTOR_H
#define __VECTOR_H

#include <cstdlib>

template<typename T>
class Vector
{
public:
	Vector(void);
	~Vector(void);

	void append(const T& item);


	class iterator
	{
	public:
		iterator(std::size_t index = 0, Vector<T>* parent = NULL);
		~iterator(void);

		bool operator==(const Vector<T>::iterator& other) const;
		bool operator!=(const Vector<T>::iterator& other) const;

		const T& operator->(void) const;
		T& operator->(void);
		const T& operator*(void) const;
		T& operator*(void);

		Vector<T>::iterator& operator++(void);
		Vector<T>::iterator& operator++(int);
		Vector<T>::iterator& operator+=(std::size_t offset);
		Vector<T>::iterator& operator--(void);
		Vector<T>::iterator& operator--(int);
		Vector<T>::iterator& operator-=(std::size_t offset);
		Vector<T>::iterator& operator=(const Vector<T>::iterator& src);
	private:
		friend class Vector<T>;
		void invalidate(void) const;

		mutable bool mValid;
		Vector<T>* mVector;
		std::size_t mIndex;
	};

	void erase(const Vector<T>::iterator& location);
	void erase(const Vector<T>::iterator& first, const Vector<T>::iterator& last);

	Vector<T>::iterator begin(void);
	Vector<T>::iterator end(void);

	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;

private:

	void resize(std::size_t newSize);

	T* mArray;
	std::size_t mSize;
	std::size_t mNextIndex;
};

#include "Vector.ipp"

#endif
