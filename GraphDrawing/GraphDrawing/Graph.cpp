#include "Graph.h"
#include <fstream>

Graph::Graph()
{
}

void Graph::AddNode(Node node)
{
	nodes.push_back(node);
}

void Graph::AddNode(QPoint position)
{
	bool verify = true;
	for (Node& node : nodes)
	{
		if (((node.getPosition().x() - 20 <= position.x()) && (position.x() <= node.getPosition().x() + 30)) &&
			((node.getPosition().y() - 20 <= position.y()) && (position.y() <= node.getPosition().y() + 30)))
		{
			verify=false;
			break;
		}
	}
	if (verify == true)
	{
		Node node;
		node.setPosition(position);
		node.setValue(nodes.size() + 1);
		nodes.push_back(node);
		SaveMatrix();
	}
}

void Graph::AddArch(Arch arch)
{
	arches.push_back(arch);
}

void Graph::AddArch(Node node1, Node node2)
{
	bool verify = true;
	for (Arch& arch : arches)
	{
		if (m_type == 2)
		{
			if(((arch.getFirstNode() == node1) && (arch.getSecondNode() == node2)) ||
				((arch.getSecondNode() == node1) && (arch.getFirstNode() == node2)))
			{
				verify = false;
				break;
			}
		}
		else
		{
			if((arch.getFirstNode() == node1) && (arch.getSecondNode() == node2))
			{
				verify = false;
				break;
			}
		}
	}
	if (verify == true)
	{
		arches.push_back(Arch(node1, node2));
		SaveMatrix();
	}
}

void Graph::setType(int type)
{
	m_type = type;
}

int Graph::getType()
{
	return m_type;
}

std::vector<Node> Graph::getNodes()
{
	return nodes;
}

std::vector<Arch> Graph::getAches()
{
	return arches;
}

void CreateMatrixAdj(std::vector<std::vector<int>>& matrixAdj, const std::vector<Node>& nodes,std::vector<Arch> arches,int type)
{
	for (int index = 0; index < nodes.size(); index++)
	{
		std::vector<int> columns;
		for (int index = 0; index < nodes.size(); index++)
			columns.push_back(0);
		matrixAdj.push_back(columns);
	}
	for (int index = 0; index < arches.size(); index++)
	{
		matrixAdj[arches[index].getFirstNode().getValue() - 1][arches[index].getSecondNode().getValue() - 1] = 1;
		if(type==2)
		  matrixAdj[arches[index].getSecondNode().getValue() - 1][arches[index].getFirstNode().getValue() - 1] = 1;
	}
}

void Graph::SaveMatrix()
{
	std::ofstream fout("Save.txt");
	std::vector<std::vector<int>> matrixAdj;
	fout << nodes.size() << '\n';
	CreateMatrixAdj(matrixAdj,nodes,arches,m_type);
	for (int index = 0; index < nodes.size(); index++)
	{
		for (int jndex = 0; jndex < nodes.size(); jndex++)
			fout << matrixAdj[index][jndex] << ' ';
		fout << '\n';
	}
	fout.close();
}
