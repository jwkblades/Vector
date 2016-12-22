#ifndef __VECTOR_H
#define __VECTOR_H

#include <cstdlib>
#include <iterator>

/**
 * An example vector class for learning purposes.
 * DON'T USE THIS FOR PRODUCTION!
 *
 * Some of the functionality common in vectors has been left up to the user to
 * implement:
 * size - Return the current size of the vector (number of elements actually
 *     stored in the vector).
 * capacity - Return the total number of elements the vector can currently
 *     hold.
 * empty - Return true if there are no elements stored in the vector currently.
 */
template<typename T>
class Vector
{
public:
	/**
	 * Create a vector, by default we set it to 100 items large.
	 */
	Vector(void);
	/**
	 * Clean up the vector's resource.
	 */
	~Vector(void);

	/**
	 * Add an item to the end of the vector. This may result in the vector being
	 * resized (larger) to be able to fit all the elements.
	 *
	 * @param item The item to be added to the end of the vector.
	 */
	void append(const T& item);


	/**
	 * An iterator class for vectors.
	 *
	 * NOTE: Iterator validation and invalidation isn't really done (it is
	 *       something that is left to the exercise of the user). But basically,
	 *       when an item is inserted _before_ an iterator, that iterator is
	 *       invalidated because it is now referencing a different element than it
	 *       was previous. Also if an iterator is at an index that is removed, or
	 *       after an index that is removed, it should also be invalidated.
	 */
	class iterator
	{
	public:
		/**
		 * Construct an iterator. It needs to know its index _and_ the vector that it
		 * belongs to.
		 */
		iterator(std::size_t index = 0, Vector<T>* parent = NULL);
		/**
		 * Destructor.
		 */
		~iterator(void);

		/**
		 * Is this iterator equivalent to another one?
		 *
		 * @param other The iterator to compare against.
		 * @returns True if the iterators are equivalent, false otherwise.
		 */
		bool operator==(const Vector<T>::iterator& other) const;
		/**
		 * Is this iterator different from another one?
		 *
		 * @param other The iterator to compare against.
		 * @returns True if the iterators are different, false otherwise.
		 */
		bool operator!=(const Vector<T>::iterator& other) const;

		/**
		 * Access the element the iterator is currently on.
		 *
		 * @returns The element the iterator is on.
		 */
		const T& operator->(void) const;
		T& operator->(void);
		const T& operator*(void) const;
		T& operator*(void);

		/**
		 * Some hacked together functions to fill in the gaps that we missing to work
		 * with std::sort.
		 */
		int operator-(const Vector<T>::iterator& other) const;
		bool operator<(const Vector<T>::iterator& other) const;
		Vector<T>::iterator operator+(int offset) const;
		Vector<T>::iterator operator-(int offset) const;

		/**
		 * Move to the next item in the vector.
		 *
		 * @returns The iterator after it has moved.
		 */
		Vector<T>::iterator& operator++(void);
		Vector<T>::iterator& operator++(int);

		/**
		 * Move the iterator forward X spaces.
		 *
		 * @param offset The number of spaces to move forward.
		 * @returns The iterator after it has moved.
		 */
		Vector<T>::iterator& operator+=(std::size_t offset);
		/**
		 * Move to the previous item in the vector.
		 *
		 * @returns The iterator after it has moved.
		 */
		Vector<T>::iterator& operator--(void);
		Vector<T>::iterator& operator--(int);
		/**
		 * Move the iterator backward X spaces.
		 *
		 * @param offset The number of spaces to move backwards.
		 * @returns The iterator after it has moved.
		 */
		Vector<T>::iterator& operator-=(std::size_t offset);
		/**
		 * Assign one iterator to another.
		 *
		 * @param src The source iterator to assign this one to.
		 * @returns The iterator after it has been updates.
		 */
		Vector<T>::iterator& operator=(const Vector<T>::iterator& src);
	private:
		friend class Vector<T>;

		/**
		 * Function for Vector<T> to call to be able to invalidate an iterator 
		 * without having to go in and access its internal values.
		 *
		 * NOTE: Iterators don't currently do much (or anything) with the mValid
		 *       boolean, this is something I have left to the user to complete.
		 */
		void invalidate(void) const;

		mutable bool mValid;
		Vector<T>* mVector;
		std::size_t mIndex;
	};


	/**
	 * Erase one or more elements in a vector.
	 *
	 * @param location The item to remove from the vector.
	 */
	void erase(const Vector<T>::iterator& location);
	/**
	 * Erase one or more elements in a vector.
	 *
	 * @param first The first element to remove from the vector.
	 * @param last One past the last element in the vector to be removed. Yes,
	 *     this isn't the best variable name...
	 */
	void erase(const Vector<T>::iterator& first, const Vector<T>::iterator& last);

	/**
	 * Retrieve an iterator to the beginning of the vector.
	 */
	Vector<T>::iterator begin(void);
	/**
	 * Retrieve an iterator to the end of the vector.
	 */
	Vector<T>::iterator end(void);

	/**
	 * Random access an item in the vector.
	 *
	 * @param index The index in the vector to access.
	 * @returns The item in the vector at the specified location.
	 */
	T& operator[](std::size_t index);
	const T& operator[](std::size_t index) const;

private:

	/**
	 * Resize the vector.
	 *
	 * NOTE: This function _will not_ reduce the size of a vector. It will instead
	 *       throw an exception in that case.
	 * NOTE: This doesn't invalidate vectors.
	 * NOTE: For a small period of time, this function actually winds up over
	 *       doubling the memory usage of the vector. Moving from one memory
	 *       location to the other could be made more efficiently using memcpy or
	 *       the like and taking part of the kernel optimizations available. This
	 *       is left as an exercise to the user.
	 *
	 * @param newSize The desired size of the vector (size being number of
	 *     elements it can support) after the resize happens.
	 */
	void resize(std::size_t newSize);

	T* mArray;
	std::size_t mSize;
	std::size_t mNextIndex;
};



#include "Vector.ipp"

#endif
