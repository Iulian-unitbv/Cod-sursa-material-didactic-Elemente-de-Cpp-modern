#pragma once
class Piece
{
public:
	enum class Body
	{
		Full,
		Hollow
	};

	enum class Color
	{
		Dark,
		Light
	};

	enum class Height
	{
		Short,
		Tall
	};

	enum class Shape
	{
		Round,
		Square
	};

public:
	Piece(Body body, Color color, Height height, Shape shape);

private:
	Body m_body;
	Color m_color;
	Height m_height;
	Shape m_shape;
};
