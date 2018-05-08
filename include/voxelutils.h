#pragma once

#include <tuple>
#include <glm/glm.hpp>

namespace vtk {

enum class FaceDirection {
	TOP = 0,
	BOTTOM = 1,
	NORTH = 2,
	SOUTH = 3,
	EAST = 4,
	WEST = 5
};

typedef std::tuple<unsigned, unsigned, unsigned> uPos; //used for voxel positions

struct uPosHash : public std::unary_function<uPos, std::size_t> {
	std::size_t operator()(const uPos& k) const {
		return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
	}
};

struct uPosEqual : public std::binary_function<uPos, uPos, bool> {
	bool operator()(const uPos& a, const uPos& b) const {
		return (std::get<0>(a) == std::get<0>(b) &&
		        std::get<1>(a) == std::get<1>(b) &&
		        std::get<2>(a) == std::get<2>(b));
	}
};


typedef std::tuple<int, int, int> iPos; //used for chunk positions
struct iPosHash : public std::unary_function<iPos, std::size_t> {
	std::size_t operator()(const iPos& k) const {
		return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
	}
};

struct iPosEqual : public std::binary_function<iPos, iPos, bool> {
	bool operator()(const iPos& a, const iPos& b) const {
		return (std::get<0>(a) == std::get<0>(b) &&
		        std::get<1>(a) == std::get<1>(b) &&
		        std::get<2>(a) == std::get<2>(b));
	}
};

// basic hash function for glm::ivec3
struct ivec3Hash : public std::unary_function<glm::ivec3, std::size_t> {
	std::size_t operator()(const glm::ivec3& k) const {
		std::size_t seed = 3;
		for(int i = 0; i < 3; ++i) {
			seed ^= k[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

// hash function for glm::ivec2
struct ivec2Hash : public std::unary_function<glm::ivec2, std::size_t> {
	std::size_t operator()(const glm::ivec2& k) const {
		std::size_t seed = 3;
		for(int i = 0; i < 2; ++i) {
			seed ^= k[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

}
