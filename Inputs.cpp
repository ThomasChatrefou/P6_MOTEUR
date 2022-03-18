#include "Inputs.hpp"

Inputs::Inputs()
{
}

void Inputs::OnEvent(SDL_Event* currentEvent)
{
	switch (currentEvent->type) 
	{
	case SDL_QUIT:
		OnQuit();
		break;
	}
}

void Inputs::OnQuit()
{
}
