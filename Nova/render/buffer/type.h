#pragma once

namespace Nova::Buffer {

	enum class Type : unsigned char {
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		UInt, UInt2, UInt3, UInt4,
		Double, Double2, Double3, Double4,
		Bool,
		Mat2, Mat3, Mat4
	};

	static inline constexpr unsigned int TypeSize(Type type) {
		switch (type) {
		case Type::Float:	return sizeof(float);
		case Type::Float2:	return sizeof(float) * 2;
		case Type::Float3:	return sizeof(float) * 3;
		case Type::Float4:	return sizeof(float) * 4;
		case Type::Int:	return sizeof(int);
		case Type::Int2:	return sizeof(int) * 2;
		case Type::Int3:	return sizeof(int) * 3;
		case Type::Int4:	return sizeof(int) * 4;
		case Type::UInt:	return sizeof(unsigned int);
		case Type::UInt2:	return sizeof(unsigned int) * 2;
		case Type::UInt3:	return sizeof(unsigned int) * 3;
		case Type::UInt4:	return sizeof(unsigned int) * 4;
		case Type::Double:	return sizeof(float);
		case Type::Double2:	return sizeof(float) * 2;
		case Type::Double3:	return sizeof(float) * 3;
		case Type::Double4:	return sizeof(float) * 4;
		case Type::Mat2:	return sizeof(float) * 2 * 2;
		case Type::Mat3:	return sizeof(float) * 3 * 3;
		case Type::Mat4:	return sizeof(float) * 4 * 4;
		case Type::Bool:	return sizeof(bool);
		case Type::None:	return 0;
		default:	return 0;
		}
	}

	static inline constexpr unsigned int TypeCount(Type type) {
		switch (type) {
		case Type::Float:	return 1;
		case Type::Float2:	return 2;
		case Type::Float3:	return 3;
		case Type::Float4:	return 4;
		case Type::Int:	return 1;
		case Type::Int2:	return 2;
		case Type::Int3:	return 3;
		case Type::Int4:	return 4;
		case Type::UInt:	return 1;
		case Type::UInt2:	return 2;
		case Type::UInt3:	return 3;
		case Type::UInt4:	return 4;
		case Type::Double:	return 1;
		case Type::Double2:	return 2;
		case Type::Double3:	return 3;
		case Type::Double4:	return 4;
		case Type::Mat2:	return 2 * 2;
		case Type::Mat3:	return 3 * 3;
		case Type::Mat4:	return 4 * 4;
		case Type::Bool:	return 1;
		case Type::None:	return 0;
		default:	return 0;
		}
	}

}