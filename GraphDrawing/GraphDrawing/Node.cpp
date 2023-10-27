#include "Node.h"

Node::Node()
{
    m_value = -1;
}

Node::Node(QPoint position, int value):m_position(position), m_value(value)
{
}

void Node::setValue(int value)
{
    m_value = value;
}

void Node::setPosition(QPoint position)
{
    m_position = position;
}

int Node::getValue()
{
    return m_value;
}

QPoint Node::getPosition()
{
    return m_position;
}

bool Node::operator==(Node node)
{
    if ((m_value == node.m_value) && (m_position == node.m_position))
        return true;
    return false;
}

