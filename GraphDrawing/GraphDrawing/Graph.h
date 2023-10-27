#pragma once

#include <vector>
#include "Arch.h"

class Graph
{
private:
	std::vector<Node> nodes;
	std::vector<Arch> arches;
	int m_type;
public:
	Graph();
	void AddNode(Node node);
	void AddNode(QPoint position);
	void AddArch(Arch arch);
	void AddArch(Node node1, Node node2);
	void setType(int type);
	int getType();
	std::vector<Node> getNodes();
	std::vector<Arch> getAches();
	void SaveMatrix();
};

