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

	// Getters
	Body GetBody() const { return m_body; };
	Color GetColor() const { return m_color; };
	Height GetHeight() const { return m_height; };
	Shape GetShape() const { return m_shape; };

private:
	Body m_body;
	Color m_color;
	Height m_height;
	Shape m_shape;
};
