#include "../../AOCHeaders/stdafx.h"


struct Layer
{
	Layer(int layer = 0, int depth = 0) : layer(layer), depth(depth), direction(true), currentDepth(1) {}

	int layer, depth, currentDepth;
	bool direction;
};


std::vector<Layer> readInput(std::fstream& in)
{
	std::vector<Layer> layers;
	std::string aux;
	Layer newLayer;

	while (in >> newLayer.layer >> aux >> newLayer.depth)
	{
		layers.push_back(newLayer);
	}

	return layers;
}


void moveLayers(std::vector<Layer>& layers)
{
	for (auto& layer : layers)
	{
		if (layer.direction)
		{
			layer.currentDepth++;
		}
		else
		{
			layer.currentDepth--;
		}

		if (layer.currentDepth == layer.depth)
		{
			layer.direction = false;
		}

		if (layer.currentDepth == 1)
		{
			layer.direction = true;
		}
	}
}


bool movePacket(std::vector<Layer> layers)
{
	int packet{ 0 }, it{ 0 }, size = layers.size();

	while (it < size)
	{
		if ((packet == layers[it].layer) && (layers[it].currentDepth == 1))
		{
			break;
		}

		packet++;
		if (packet > layers[it].layer)
		{
			it++;
		}

		moveLayers(layers);
	}

	return it < size;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<Layer> layers = readInput(in);
	int numberPicoseconds{ 0 };

	while (movePacket(layers))
	{
		moveLayers(layers);
		numberPicoseconds++;
	}

	out << numberPicoseconds;

	in.close();
	out.close();
}