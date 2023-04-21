/// <author>
/// Joshua Bradley
/// </author>

#pragma once

#include <math.h> 

/// <summary>
/// A generic data structure designed to store a pair of conceptually related values
/// that share a numeric base data type.
/// </summary>
/// <typeparam name="T">The type of the data to be stored in the vector.</typeparam>
template<typename T>
struct Vector2 {
	/// <summary>
	/// The Vector2 directed upwards.
	/// </summary>
	static const Vector2<T> up;
	/// <summary>
	/// The Vector2 directed downwards
	/// </summary>
	static const Vector2<T> down;
	/// <summary>
	/// The Vector2 directed to the left.
	/// </summary>
	static const Vector2<T> left;
	/// <summary>
	/// The Vector2 directed to the right.
	/// </summary>
	static const Vector2<T> right;
	/// <summary>
	/// The Vector2 with all zero components.
	/// </summary>
	static const Vector2<T> zero;

	/// <summary>
  /// The x-component of the vector.
  /// </summary>
  T x_;
	/// <summary>
	/// The y-component of the vector.
	/// </summary>
	T y_;
	/// <summary>
	/// Constructor for the Vector2 struct.
	/// </summary>
	/// <param name="x_">The x-component of the vector.</param>
	/// <param name="y_">The y-component of the vector.</param>
	Vector2<T>(T x = 0, T y = 0);
	/// <summary>
	/// Gets the magnitude of the vector.
	/// </summary>
	/// <returns>The magnitude of the vector.</returns>
	float GetLength(void) const;
	/// <summary>
	/// Converts the vector into a unit vector.
	/// </summary>
	void Normalize(void);
	/// <summary>
	/// Overload for Vector2 addition with another vector.
	/// </summary>
	/// <param name="other">The vector on the right-hand side of the operation.</param>
	/// <returns>A new Vector2, the result of vector addition.</returns>
	Vector2<T> operator+(const Vector2<T>& other) const;
	/// <summary>
	/// Overload for vector subtraction with another vector.
	/// </summary>
	/// <param name="other">The vector on the right-hand side of the operation.</param>
	/// <returns>A new Vector2, the result of vector subtraction.</returns>
	Vector2<T> operator-(const Vector2<T>& other) const;
	/// <summary>
	/// Overload for vector addition with another vector, modifying the existing vector.
	/// </summary>
	/// <param name="other">The vector on the right-hand side of the operation.</param>
	/// <returns>A modified Vector2, the result of vector addition.</returns>
	Vector2<T>& operator+=(const Vector2<T>& other);
	/// <summary>
	/// Overload for vector subtraction with another vector, modifying the existing vector.
	/// </summary>
	/// <param name="other">The vector on the right-hand side of the operation.</param>
	/// <returns>A modified Vector2, the result of vector subtraction.</returns>
	Vector2<T>& operator-=(const Vector2<T>& other);
	/// <summary>
	/// Overload for Vector2 multiplication with a float, modifying the existing vector.
	/// </summary>
	/// <param name="val">The value to multiply the vector components by.</param>
	/// <returns>A modified Vector2, the result of vector multiplication with a float.</returns>
	Vector2<T>& operator*=(float val);
	/// <summary>
	/// Overload for vector division with a float, returning a new Vector2, modifying the existing vector.
	/// </summary>
	/// <param name="val">The value to divide the vector components by.</param>
	/// <returns>A modified Vector2, the result of vector division with a float.</returns>
	Vector2<T>& operator/=(float val);
	/// <summary>
	/// Overload for vector multiplication with a float.
	/// </summary>
	/// <param name="val">The value to multiply the vector components by.</param>
	/// <returns>A new Vector2<float>, the result of vector multiplication with a float.</returns>
	Vector2<float> operator*(float val) const;
	/// <summary>
	/// Overload for vector division with a float.
	/// </summary>
	/// <param name="val">The value to multiply the vector components by.</param>
	/// <returns>A new Vector2<float>, the result of vector division with a float.</returns>
	Vector2<float> operator/(float val) const;
	/// <summary>
	/// Overload for testing vector equality.
	/// </summary>
	/// <param name="other">The vector on the right-hand side of the operation.</param>
	/// <returns>True if the vectors are equal, else false.</returns>
	bool operator==(const Vector2<T>& other) const;
	/// <summary>
	/// Overload for testing vector inequality.
	/// </summary>
	/// <param name="other">The vector on the right-hand side of the operation.</param>
	/// <returns>True if the vectors are unequal, else false.</returns>
	bool operator!=(const Vector2<T>& other) const;
};

template <typename T>
Vector2<T>::Vector2(const T x, const T y)
	: x_(x),
	  y_(y) {}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
	return Vector2<T>(x_ + other.x_, y_ + other.y_);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
	return Vector2<T>(x_ - other.x_, y_ - other.y_);
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other) {
	static_cast<float>(x_ += other.x_);
	static_cast<float>(y_ += other.y_);

	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other) {
	static_cast<float>(x_ -= other.x_);
	static_cast<float>(y_ -= other.y_);

	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(float val) {
	x_ = static_cast<T>(x_ * val);
	y_ = static_cast<T>(y_ * val);

	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(float val) {
	x_ = static_cast<T>(x_ / val);
	y_ = static_cast<T>(y_ / val);

	return *this;
}

template <typename T>
Vector2<float> Vector2<T>::operator*(const float val) const {
	return {x_ * val, y_ * val};
}

template <typename T>
Vector2<float> Vector2<T>::operator/(float val) const {
	return {x_ / val, y_ / val};
}

template <typename T>
float Vector2<T>::GetLength() const {
	auto dblMyX = static_cast<double>(x_);
	auto dblMyY = static_cast<double>(y_);

	return static_cast<float>(sqrt(dblMyX * dblMyX + dblMyY * dblMyY));
}

template <typename T>
void Vector2<T>::Normalize() {
	auto length = GetLength();

	if (length > 0.f) {
		*this /= length;
	}
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& other) const {
	return x_ == other.x_ && y_ == other.y_;
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& other) const {
	return !(*this == other);
}

template <typename T>
const Vector2<T> Vector2<T>::up(0, -1);

template <typename T>
const Vector2<T> Vector2<T>::down(0, 1);

template <typename T>
const Vector2<T> Vector2<T>::left(-1, 0);

template <typename T>
const Vector2<T> Vector2<T>::right(1, 0);

template <typename T>
const Vector2<T> Vector2<T>::zero(0, 0);