#pragma once

#include "OGLIncludes.hpp"

class Inputs 
{
public:
	Inputs();

	virtual void OnEvent(SDL_Event* currentEvent);

public:
	virtual void OnQuit();
};