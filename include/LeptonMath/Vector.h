
#include <ostream>

#include <array>
#include <initializer_list>
#include <concepts>

#include <cassert>

namespace lm{

	// forward declations

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	class Vector;

	template<typename T, size_t size>
	std::ostream& operator<<(std::ostream& s, const Vector<T, size> vec);

	template<typename T, size_t size>
	Vector<T, size> operator+(const Vector<T, size>& v1, const  Vector<T, size>& v2);

	template<typename T, size_t size>
	T operator*(const Vector<T, size>& v1, const  Vector<T, size>& v2);

	// Vector class

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	class Vector {
	private:
		std::array<T, size> data;

	public:
		
		// Constructors

		Vector() = default;
		Vector(std::initializer_list<T> init);


		// Operators

		friend std::ostream& operator<< <>(std::ostream& s, const Vector<T, size> vec);

		friend Vector<T, size> operator+ <>(const Vector<T, size>& v1, const  Vector<T, size>& v2);

		friend T operator* <>(const Vector<T, size>& v1, const  Vector<T, size>& v2);

	};

	// Common type defintions

	template<size_t size>
	using Vectorf = Vector<float, size>;

	template<size_t size>
	using Vectori = Vector<int, size>;

	using Vector2f = Vector<float, 2>;
	using Vector3f = Vector<float, 3>;
	using Vector4f = Vector<float, 4>;

	// Definitions

	template<typename T, size_t size> requires std::is_arithmetic_v<T>
	Vector<T, size>::Vector(std::initializer_list<T> init) {
		assert(init.size() <= size);
		std::copy(init.begin(), init.end(), data.begin());
	}


	template<typename T, size_t size>
	Vector<T, size> operator+(const Vector<T, size>& v1, const  Vector<T, size>& v2) {
		Vector<T, size> out;

		for (size_t i = 0; i < size; ++i) {
			out.data[i] = v1.data[i] + v2.data[i];
		}

		return out;
	}


	template<typename T, size_t size>
	T operator*(const Vector<T, size>& v1, const  Vector<T, size>& v2) {
		T out = T();

		for (size_t i = 0; i < size; ++i) {
			out += v1.data[i] * v2.data[i];
		}

		return out;
	}

	template<typename T, size_t size>
	std::ostream& operator<<(std::ostream& s, const Vector<T, size> vec) {
		s << "[";
		if (size > 0) s << vec.data[0];
		for (size_t i = 1; i < size; ++i) {
			s << "," << vec.data[i];
		}
		s << "]";
		return s;
	}

}