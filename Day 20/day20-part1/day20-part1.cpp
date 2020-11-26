#include "../../AOCHeaders/stdafx.h"


struct Coordinate
{
	Coordinate(const int x = 0, const int y = 0, const int z = 0) :x(x), y(y), z(z) {}
	Coordinate operator+(const Coordinate& c) const
	{
		return Coordinate(this->x + c.x, this->y + c.y, this->z + c.z);
	}

	static int manhattanDistance(const Coordinate& first, const Coordinate& second)
	{
		return std::abs(first.x - second.x) + std::abs(first.y - second.y) + std::abs(first.z - second.z);
	}

	int x, y, z;
};


struct Particle
{
	Particle(const Coordinate p, const Coordinate v, const Coordinate a) :p(p), v(v), a(a), id(lastId++) {}

	void updateParticle()
	{
		v = v + a;
		p = p + v;
	}

	Coordinate  p, v, a;
	int id;
	static int lastId;
};

int Particle::lastId = 0;

Coordinate readCoordinate(std::stringstream& ss)
{
	std::string coordinate;
	Coordinate curr;

	ss >> coordinate;

	std::stringstream ssCoordinate{ coordinate };
	char c{};

	ssCoordinate >> c >> c >> c >> curr.x >> c >> curr.y >> c >> curr.z;

	return curr;
}


std::vector<Particle> readInput(std::fstream& in)
{
	std::vector<Particle> particles;
	std::string line;
	Coordinate curr;

	while (std::getline(in, line))
	{
		std::stringstream ss{ line };

		particles.push_back({ readCoordinate(ss), readCoordinate(ss), readCoordinate(ss) });
	}

	return particles;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);

	std::vector<Particle> particles = readInput(in);;
	Coordinate center;

	for (int it = 0; it < 1000; it++)
	{
		for (auto& particle : particles)
		{
			particle.updateParticle();
		}
	}

	out << std::min_element(std::begin(particles), std::end(particles), [center](const auto& first, const auto& second)
		{
			return Coordinate::manhattanDistance(first.p, center) < Coordinate::manhattanDistance(second.p, center);
		})->id;

	in.close();
	out.close();
}