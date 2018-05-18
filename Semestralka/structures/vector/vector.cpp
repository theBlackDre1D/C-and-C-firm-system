#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) : //Kopirovaci konstruktor
		Vector(other.size_)
	{
		//TODO 01: Vector
		memory_ = memcpy(memory_, other.memory_, size_);
		/*throw std::exception("Vector::Vector: Not implemented yet.");*/
	}

	Vector::~Vector()
	{
		//TODO 01: Vector
		free(memory_);
		memory_ = nullptr; // je dobre robit to takto, aby mi neukazovlai smerniky na pamat ktora mi uz nepatri
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		//TODO 01: Vector
		//throw std::exception("Vector::operator=: Not implemented yet.");
		if (this != &other) {
			size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memory_ = memcpy(memory_, other.memory_, size_);
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		//TODO 01: Vector
		//throw std::exception("Vector::operator==: Not implemented yet.");
		return size_ == other.size_ && memcmp(memory_, other.memory_, size_); // == 0;
	}

	byte& Vector::operator[](const int index) // vracia adresu 
	{
		//TODO 01: Vector
		//throw std::exception("Vector::operator[]: Not implemented yet.");
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!"); // trieda vytvorena ucitelmi na osetrovanie
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const // vracia hodnotu
	{
		//TODO 01: Vector
		//throw std::exception("Vector::operator[]: Not implemented yet.");
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return *(reinterpret_cast<byte*>(memory_) + index); // pretypujem smernik void na byte
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		//TODO 01: Vector
		// Na domacu ulohu!
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "Invalid end index in Vector!");
		
		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		//TODO 01: Vector
		// Na domacu ulohu!
		if (length != 0) {
			DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid index in Vector src!");
			DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid index in Vector dest!");
			DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid index in Vector src!");
			DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_, "Invalid index in Vector dest!");

			if (&src == &dest && (srcStartIndex + length <= destStartIndex || destStartIndex + length <= srcStartIndex)) {
				memmove(src.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
			else {
				memcpy(src.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		//TODO 01: Vector
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return reinterpret_cast<byte*>(memory_) + index;
	}

}