#pragma once
#include <QPainter>

class Node
{
private:
	int m_value;
	QPoint m_position;
public:
	Node();
	Node(QPoint position, int value);
	void setValue(int value);
	void setPosition(QPoint position);
	int getValue();
	QPoint getPosition();
	bool operator==(Node node);
};

