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
	case SDL_KEYDOWN:
		switch (currentEvent->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			OnQuit();
			break;
		}
		break;
	}
	
}

void Inputs::OnQuit()
{
}
