#include "Includes.hpp"

namespace GC_3D
{
	class Importer
	{
	public:
		static bool DoTheImportThing(
			const std::string& pFile,
			std::vector<unsigned short>& indices,
			std::vector<glm::vec3>& vertices,
			std::vector<glm::vec2>& uvs,
			std::vector<glm::vec3>& normals);
	};
}