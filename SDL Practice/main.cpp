// This is the main SDL include file
#include <SDL.h>
// iostream is so we can output error messages to console
#include <iostream>
#include "Texture.h"
#include "Entity.h"

int main(int argc, char *argv[])
{
	// This is our initialisation phase

	// SDL_Init is the main initialisation function for SDL
	// It takes a 'flag' parameter which we use to tell SDL what systems we're going to use
	// Here, we want to use SDL's video system, so we give it the flag for this
	// Incidentally, this also initialises the input event system
	// This function also returns an error value if something goes wrong
	// So we can put this straight in an 'if' statement to check and exit if need be
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}



	// Now we have got SDL initialised, we are ready to create a window!
	// These are some variables to help show you what the parameters are for this function
	// You can experiment with the numbers to see what they do
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 640;
	int winHeight = 480;
	SDL_Window *window = SDL_CreateWindow("My Window!!!",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	// The last parameter lets us specify a number of options
	// Here, we tell SDL that we want the window to be shown and that it can be resized
	// You can learn more about SDL_CreateWindow here: https://wiki.libsdl.org/SDL_CreateWindow?highlight=%28\bCategoryVideo\b%29|%28CategoryEnum%29|%28CategoryStruct%29
	// The flags you can pass in for the last parameter are listed here: https://wiki.libsdl.org/SDL_WindowFlags

	// The SDL_CreateWindow function returns an SDL_Window
	// This is a structure which contains all the data about our window (size, position, etc)
	// We will also need this when we want to draw things to the window
	// This is therefore quite important we don't lose it!

	// The SDL_Renderer is a structure that handles rendering
	// It will store all of SDL's internal rendering related settings
	// When we create it we tell it which SDL_Window we want it to render to
	// That renderer can only be used for this window
	// (yes, we can have multiple windows - feel free to have a play sometime)
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	Texture* t_guy = new Texture("guy.bmp",renderer);
	Entity* guy = new Entity(t_guy, Vec2(75, 4));
	if (!guy)
	{
		//Make better (i.e not external)
		std::cout << "Class wasn't constucted guy" << std::endl;
		SDL_Delay(10000);
		SDL_Quit();
		return -1;
	}

	Texture* t_guyName = new Texture("guyName.bmp", renderer);
	Entity* guyName = new Entity(t_guyName, Vec2(25, 110));
	if (!guyName)
	{
		std::cout << "Class wasn't constucted guyname" << std::endl;
		SDL_Delay(10000);
		SDL_Quit();
		return -1;
	}
	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures
	bool go = true;
	while (go)
	{

		// Here we are going to check for any input events
		// Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event'
		// SDL has a queue of events
		// We need to check for each event and then do something about it (called 'event handling')
		// the SDL_Event is the datatype for the event
		SDL_Event incomingEvent;
		// SDL_PollEvent will check if there is an event in the queue
		// If there's nothing in the queue it won't sit and wait around for an event to come along (there are functions which do this, and that can be useful too!)
		// For an empty queue it will simply return 'false'
		// If there is an event, the function will return 'true' and it will fill the 'incomingEvent' we have given it as a parameter with the event data
		while (SDL_PollEvent(&incomingEvent))
		{
			// If we get in here, we have an event and need to figure out what to do with it
			// For now, we will just use a switch based on the event's type
			switch (incomingEvent.type)
			{
			case SDL_QUIT:
				// The event type is SDL_QUIT
				// This means we have been asked to quit - probably the user clicked on the 'x' at the top right corner of the window
				// To quit we need to set our 'go' bool to false so that we can escape out of the game loop
				go = false;
				break;

				// If you want to learn more about event handling and different SDL event types, see:
				// https://wiki.libsdl.org/SDL_Event
				// and also: https://wiki.libsdl.org/SDL_EventType
				// but don't worry, we'll be looking at handling user keyboard and mouse input soon
			}
		}


		// Update our world
		// (nothing to update for now)


		// Draw our world

		// Start by clearing what was drawn before
		// Set the colour for drawing, set to red here
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
		// Clear the entire screen to our selected colour
		SDL_RenderClear(renderer);

		// To be honest because we're not actually changing anything each time we draw our texture, the whole game loop is a bit of an overkill
		// The point is though, I wanted to show you this way of doing things so that when we *do* change stuff each frame
		// we don't need to think about a whole new program structure!
		// Also, feel free to start playing and see if you can get the texture to move about ;)
		// Or just wait for next week :)

		guy->render();
		guyName->render();


		// This tells the renderer to actually show its contents to the screen
		// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
		SDL_RenderPresent(renderer);
	}

	// If we get outside the main game loop, it means our user has requested we exit


	// Our cleanup phase, hopefully fairly self-explanatory ;)
	delete guy;
	delete guyName;
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}