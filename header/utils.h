#ifndef UTILS
#define UTILS

int const WIDTH = 1600;
int const HEIGHT = 900;

struct Float2 {
	float x;
	float y;
	
	Float2 operator+(Float2 b) {
		return {x+b.x,y+b.y};
	};
	
	Float2 operator-(Float2 b) {
		return {x-b.x,y-b.y};
	};
	
	Float2 operator+=(Float2 b) {
		x += b.x;
		y += b.y;
		return *this;
	};
	
	Float2 operator-=(Float2 b) {
		x -= b.x;
		y -= b.y;
		return *this;
	};
	
	Float2 operator/(float b) {
		return {x/b,y/b};
	};
	
	Float2 operator*(float b) {
		return {x*b,y*b};
	};
	
	Float2 operator/=(float b) {
		x /= b;
		y /= b;
		return *this;
	};
	
	Float2 operator*=(float b) {
		x *= b;
		y *= b;
		return *this;
	};
	
	Float2& normalize() {
		if(x*x + y*y > 0) {
			x /= sqrt(x*x + y*y);
			y /= sqrt(x*x + y*y);
		}
		return *this;
	};
	
	float norme() {
		return sqrt(x*x+y*y);
	}
};

#endif
