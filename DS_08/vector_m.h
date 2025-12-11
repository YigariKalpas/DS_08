#pragma once

#ifndef debug_mode
#define debug_mode 1
#endif // debug_mode

#ifndef developer
#define developer 0
#endif // developer

template<typename T>
class vector_m
{
public:
	int capacity;
	int end_pointer;
	T* pointer;
	/// <summary>
	/// empty obj initiallize
	/// </summary>
	vector_m() : capacity(0),pointer(nullptr),end_pointer(0) {
		reserve(100); //default memory assignment
	};
	/// <summary>
	/// template with a certain size of this instace
	/// </summary>
	/// <param name="size_s",with array size initiallize></param>
	vector_m(int size_s) :capacity(size_s),end_pointer(10){
		pointer = new T[size_s];
		for (int i = 0; i < size_s; i++) {
			*(pointer + i) = T();
		}
	};
	vector_m(const vector_m<T>& other_element) {
		reserve(other_element.capacity);
		for (int i = 0; i < other_element.end_pointer; i++) {
			*(pointer + i) = *(other_element.pointer + i);
			end_pointer++;
		}
		return;
	}
	/// <summary>
	/// used for a vector_m to alloc a new space in heap
	/// </summary>
	/// <param name="new_size"></param>
	void reserve(long long new_size) {
		if (new_size < capacity)
			return;
		else {
			// at this moment we don't discuss about the already_illustrated vector, this case is just for one empty vector_m to initiallize ;
#if developer
			T* new_space = new T[new_size];
			// copy the elements from the pointer to the new_space
			delete[] pointer;
			pointer = new_space;
#endif	
			delete[] pointer;
			pointer = new T[new_size];
			end_pointer = 0;
			capacity = new_size;
			//不对size进行更改，此时没有对此块内容进行初始化，在原理上endpointer<=capacity可以保证
#if debug_mode
			std::cout << "reserve successfully\n";
#endif
			return;
		}
	}

	void push_back(const T& element) {
		if (end_pointer >= capacity) {
			std::cout << "push_back contents overflow";
			return;
		}
		else {
			*(pointer + end_pointer) = element;
			end_pointer++;
		}
	};

	void vector_show() const {
		for (int i = 0; i < end_pointer; i++) {
			std::cout << *(pointer + i) << "  ";
			if (!((i + 1) % 5))
				std::cout << std::endl;
		}
		return;
	};

	long long Get_Size()const {
		return end_pointer;
	};

	const T operator[](int i) const {
		if (i >= end_pointer) {
#if debug_mode
			std::cout << "Illegal Position\n";
#endif
			return *pointer;
		}
		else {
			return *(pointer + i);
		}
	}

	T& operator[](int i) {
		if (i >= end_pointer) {
#if debug_mode
			std::cout << "Illegal Position\n";
#endif
			return *pointer;
		}
		else {
			return *(pointer + i);
		}
	}

	inline void element_swap(int pos1, int pos2) {
		if (pos1 > end_pointer || pos2 > end_pointer || pos1 < 0 || pos1 < 0 || pos1 == pos2)
			return; 
		else {
			(*this)[pos2] += (*this)[pos1];
			(*this)[pos1] = (*this)[pos2] - (*this)[pos1];
			(*this)[pos2] -= (*this)[pos1];
		}
	}

	T* begin() const {
		return pointer;
	};
	T* end() {
		return pointer + end_pointer;
	};
};

