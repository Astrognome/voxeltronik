#include "voxelutils.h"
#include "mathplus.h"

namespace vtk {

glm::ivec3 worldPosToChunkPos(const glm::ivec3& pos) {
	return glm::ivec3(mp::floor_div3(pos.x, 16),
	                  mp::floor_div3(pos.y, 16),
	                  mp::floor_div3(pos.z, 16));
}

glm::ivec2 worldPosToChunkPos(const glm::ivec2& pos) {
	return glm::ivec2(mp::floor_div3(pos.x, 16),
	                  mp::floor_div3(pos.y, 16));
}


glm::ivec3 chunkPosToWorldPos(const glm::ivec3& cPos, const glm::ivec3& lPos) {
	return glm::ivec3((cPos * 16) + lPos);
}

std::pair<glm::ivec3, glm::ivec3> worldPosToLocalPos(const glm::ivec3& pos) {
	auto cPos = worldPosToChunkPos(pos);
	auto lPos = pos - (16 * cPos);
	return std::make_pair(cPos, lPos);
}

std::pair<glm::ivec3, glm::ivec3> localPosToLocalPos(const glm::ivec3& cPos, const glm::ivec3& lPos) {
	glm::ivec3 wPos = chunkPosToWorldPos(cPos, lPos); // get world coords
	return worldPosToLocalPos(wPos);
	
}
}
