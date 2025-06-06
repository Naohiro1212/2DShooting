#pragma once

//XGA SIZE
const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;

extern float gDeltaTime; // ƒtƒŒ[ƒ€ŠÔ‚ÌŠÔ·

inline float GetDeltaTime()
{
	return gDeltaTime;
}

struct Point
{
	float x;
	float y;
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;
	inline Point GetCenter() const
	{
		return { x + width / 2, y + height / 2 };
	}
};