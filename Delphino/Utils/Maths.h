#pragma once
struct Vector2f {
	float x, y;
public:
	Vector2f(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2f operator+(Vector2f vec) {
		return Vector2f(x + vec.x, y + vec.y);
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
};
struct Vector3f : public Vector2f {
	float z;
public:
	Vector3f(float x, float y, float z) : Vector2f(x,y) {
		this->z = z;
	}
	Vector3f operator+(Vector3f vec) {
		return Vector3f(x + vec.x, y + vec.y, z + vec.z);
	}
	float getZ() {
		return z;
	}
};
struct Vector4f : public Vector3f{
	float w;
public:
	Vector4f(float x, float y, float z, float w) : Vector3f(x,y,z) {
		this->w = w;
	}
	Vector4f operator+(Vector4f vec) {
		return Vector4f(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}
	float getW() {
		return w;
	}
};
struct Color : public Vector4f {
	Color(float r, float g, float b, float a) : Vector4f(r, g, b, a){}
	float getR() {
		return x;
	}
	float getG() {
		return y;
	}
	float getB() {
		return z;
	}
	float getA() {
		return w;
	}
};