#ifndef COLOR_H
#define COLOR_H
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;

class Color
{
public:
	float r;
	float g;
	float b;
	Color();
	Color(float _r, float _g, float _b);
	Color add(const Color& c);
	Color multiply(float s) const;
	Color modulate(const Color& c) const;
	void saturate();
	void show();
	virtual ~Color();
	static inline Color black(){ return Color(0, 0, 0); }
	static inline Color white(){ return Color(1, 1, 1); }
	static inline Color red()  { return Color(1, 0, 0); }
	static inline Color green(){ return Color(0, 1, 0); }
	static inline Color blue() { return Color(0, 0, 1); }
protected:
private:

};

#endif // COLOR_H
