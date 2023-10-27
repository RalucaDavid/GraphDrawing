#pragma once
#include "Node.h"

class Arch
{
private:
	Node m_firstNode;
	Node m_secondNode;
public:
	Arch();
	Arch(Node firstNode, Node secondNode);
	void setFirstNode(Node firstNode);
	void setSecondNode(Node secondNode);
	Node getFirstNode();
	Node getSecondNode();
};

