#include "OGLIncludes.hpp"
#include "GetAppPath.hpp"
#include "Application.hpp"


extern "C" 
{
	_declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}

int main(int argc, char* argv[])
{
	std::filesystem::path appPath(GetAppPath());

	Application app(appPath.parent_path().string(), 1600, 900);
	return app.OnExecute();
}