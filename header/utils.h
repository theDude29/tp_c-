#ifndef UTILS
#define UTILS

struct Division_by_zero_error{};

template<typename T>
struct num2 {
	T x;
	T y;
	
	num2 operator+(num2 b) {
		return {x+b.x,y+b.y};
	};
	
	num2 operator-(num2 b) {
		return {x-b.x,y-b.y};
	};
	
	num2 operator+=(num2 b) {
		x += b.x;
		y += b.y;
		return *this;
	};
	
	num2 operator-=(num2 b) {
		x -= b.x;
		y -= b.y;
		return *this;
	};
	
	num2 operator/(T b) {
		return {x/b,y/b};
	};
	
	num2 operator*(T b) {
		return {x*b,y*b};
	};
	
	num2 operator/=(T b) {
		x /= b;
		y /= b;
		return *this;
	};
	
	num2 operator*=(T b) {
		x *= b;
		y *= b;
		return *this;
	};
	
	num2& normalize() {
		if(x*x + y*y > 0) {
			x /= sqrt(x*x + y*y);
			y /= sqrt(x*x + y*y);
			
			return *this;
		}
		
		else {
			throw Division_by_zero_error{};
		}
	};
	
	T norme() {
		return sqrt(x*x+y*y);
	}
};

#endif
