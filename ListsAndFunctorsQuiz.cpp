#include <iostream>
#include <string>

using namespace std;

// what kind of structure is a list? Note that this is also the first implementation
template<class T>
class List
{
private:
	int size;
	int max_capacity;
	T *container;

	int translate(int position) const
	{
		return position - 1;
	}

public:
	List(int max_capacity = 500)
	{
		this->max_capacity = max_capacity;
		size = 0;
		container = new T[max_capacity];
	}
	~List()
	{
		delete[] container;
	}

	// isEmpty - checks if the container is empty
	bool isEmpty() const
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	// isFull - checks if the container is full
	bool isFull() const
	{
		if (size == max_capacity)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// getLength - returns the length of the container
	int getLength()
	{
		return size;
	}

	// insert - inerts the provided data into the specified position
	void insert(int position, T data)
	{
		// moving the data, starting from the end of the container, one position to the right
		for (int i = size; i >= position; i--)
		{
			container[translate(i + 1)] = container[translate(i)];
		}
		
		// placing the new data into the position
		container[translate(position)] = data;

		size++;
	}

	// remove - removes the data at the specified position
	T remove(int position)
	{
		T removedData = container[translate(position)];

		// start at the position that you remove from,
		for (int i = position; i <= size; i++)
		{
			// set the position that you removed from, to the thing that is to the right of it, or one index over
			container[translate(i)] = container[translate(i + 1)];
		}
		size--;

		return removedData;
	}

	// replace - replaces the data at the specified position 
	T replace(int position, T data)
	{
		T replacedData = container[translate(position)];

		container[translate(position)] = data;

		return replacedData;
	}

	// retrieve - retrieves the data at the specified position
	T retrieve(int position)
	{
		return container[translate(position)];
	}

	// swap - swaps values at the two specified positions
	void swap(int firstPosition, int secondPosition)
	{
		if (firstPosition == secondPosition)
		{
			return;
		}

		T temp = container[translate(firstPosition)];
		container[translate(firstPosition)] = container[translate(secondPosition)];
		container[translate(secondPosition)] = temp;
	}
};

// second implementation, we have changed the isFull function, and added a replaceContainer function, that we use in the insert function
template<class T>
class ListImplementationTwo
{
private:
	int size;
	int max_capacity;
	T *container;

	int translate(int position) const
	{
		return position - 1;
	}

public:
	ListImplementationTwo(int max_capacity = 500)
	{
		this->max_capacity = max_capacity;
		size = 0;
		container = new T[max_capacity];
	}
	~ListImplementationTwo()
	{
		delete[] container;
	}

	// isEmpty - checks if the container is empty
	bool isEmpty() const
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	// isFull - checks if the container is full
	bool isFull() const
	{
		return false;
	}

	// getLength - returns the length of the container, here for the second implementation, isFull just returns false
	int getLength()
	{
		return size;
	}

	// replaceContainer - creates a new conatiner with double the size
	void replaceContainer()
	{
		// making a new container with double the capacity
		T *newContainer = new T[2 * max_capacity];

		for (int i = 0; i <= size; i++)
		{
			newContainer[i] = container[i];
		}

		max_capacity = 2 * max_capacity;

		delete[] container;

		container = newContainer;
	}

	// insert - inerts the provided data into the specified position, for the second implementation, the container can be replaced, if it is full
	void insert(int position, T data)
	{
		if (size == max_capacity)
		{
			replaceContainer();
		}

		// moving the data, starting from the end of the container, one position to the right
		for (int i = size; i >= position; i--)
		{
			container[translate(i + 1)] = container[translate(i)];
		}

		// placing the new data into the position
		container[translate(position)] = data;

		size++;
	}

	// remove - removes the data at the specified position
	T remove(int position)
	{
		T removedData = container[translate(position)];

		// start at the position that you remove from,
		for (int i = position; i <= size; i++)
		{
			// set the position that you removed from, to the thing that is to the right of it, or one index over
			container[translate(i)] = container[translate(i + 1)];
		}
		size--;

		return removedData;
	}

	// replace - replaces the data at the specified position 
	T replace(int position, T data)
	{
		T replacedData = container[translate(position)];

		container[translate(position)] = data;

		return replacedData;
	}

	// retrieve - retrieves the data at the specified position
	T retrieve(int position)
	{
		return container[translate(position)];
	}

	// swap - swaps values at the two specified positions
	void swap(int firstPosition, int secondPosition)
	{
		if (firstPosition == secondPosition)
		{
			return;
		}

		T temp = container[translate(firstPosition)];
		container[translate(firstPosition)] = container[translate(secondPosition)];
		container[translate(secondPosition)] = temp;
	}
};

// ordered list without functors
template<class T>
class OrderedList
{
private:
	List<T> container;
	int capacity;
public:
	OrderedList(int capacity = 500) : container(capacity)
	{
	}
	~OrderedList();

	bool isEmpty()
	{
		return container.isEmpty();
	}

	int getLength() const
	{
		return container.getLength();
	}

	T remove(int position)
	{
		return container.remove(position);
	}

	T retrieve(int position) const
	{
		return container.retrieve(position);
	}

	// this is for an increasing order, if you want a decreasing order, change the sign to > 
	int insert(T data)
	{
		int position;
		
		for (position = 1; position <= getLength(); position++)
		{
			if (data < retrieve(position))
			{
				break;
			}
		}

		container.insert(position, data);

		return position;
	}

	int find(T data) const
	{
		int position;

		for (position = 1; position <= getLength(); position++)
		{
			if (data == retrieve(position))
			{
				return position;
			}
		}

		return -1;
	
	}
};

// functor with reference variable
class isGreater
{
	template <class T>
	static bool compare(const T& a, const T& b)
	{
		return a > b;
	}
};

// functor with pointer
class isGreater
{
	template <class T>
	static bool compare(const T* a, const T* b)
	{
		return *a > *b;
	}
};

template <class T, class Order>
class OrderedList
{

};

int mainSTOPPED()
{
	system("PAUSE");

	return 0;
}