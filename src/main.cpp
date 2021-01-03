#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>

#include "RenderWindow.hpp"
#include "renderwindow.cpp"
#include "Entity.hpp"
#include "entity.cpp"
#include "game.cpp"

char in{' '};





Game game;
std::string currentState{"123456789"};
std::mutex lock;

class cont{
	public:
	std::fstream str;
	~cont(){
		str.close();
	}
};

cont out;

void GamePlay(){
	bool running = true;
	while(running){
 	   game.gameStart();
	    bool Winning = true;
	    currentState = game.getState();
  	  while(Winning){
  	  	
		    while(true){	
 		   	int input;
 		   	lock.lock();
 		   	if(in > '0'){
 		   		input = in - '0';
 		   	}
 		   	//out.str << input << '\n';
 		   	lock.unlock();
   		 	bool pass = game.turnX(input);
   		 	//out.str << pass << '\n';
   		 	SDL_Delay(500);
    			if(pass)
    				break;
		    }
		    int state = game.checkGame();
		    currentState = game.getState();
		    lock.unlock();
  		  if(state != 1)
		        running = false;
 		   while(true){
   			 int input2;
   			 
 	  	 	if(in > '0'){
 		   		input2 = in - '0';
 		   	}
 		   	
 	   		bool pass = game.turnO(input2);
 	   		SDL_Delay(500);
 	  		 if(pass)
 			   	break;
 		   }

 		   state = game.checkGame();
		    currentState = game.getState();
		    if(state != 1){
 		       running = false;
		    }
	    }
	
    SDL_Delay(2000);
	}
}

void Remote(){
	SDL_Delay(1000);
	in = '1';
	SDL_Delay(1000);
	in = '5';
	SDL_Delay(1000);
	in = '2';
	SDL_Delay(1000);
	in = '9';
	SDL_Delay(1000);
	in = '3';
	return;
}

bool ProcessEvents(SDL_Event& event){
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT)
			return false;
		else if(event.type == SDL_KEYDOWN){
			switch(event.key.keysym.sym){
			case SDLK_1:
				in = '1';
				break;
			case SDLK_2:
				in = '2';
				break;			
			case SDLK_3:
				in = '3';
				break;
			case SDLK_4:
				in = '4';
				break;
			case SDLK_5:
				in = '5';
				break;
			case SDLK_6:
				in = '6';
				break;
			case SDLK_7:
				in = '7';
				break;
			case SDLK_8:
				in = '8';
				break;
			case SDLK_9:
				in = '9';
				break;
			}
		}
	}
	return true;
}

void None(){
	while(true){
		
		std::cout << "lmao";
		
	}
}


int main(int argc, char* args[])
{
	
	
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
	SDL_Texture* XTexture = window.loadTexture("res/gfx/X.png");
	SDL_Texture* OTexture = window.loadTexture("res/gfx/O.png");
	

    // Entity entities[4] = {Entity(0, 0, grassTexture),
    //               			        Entity(30, 0, grassTexture),
    //             		 	         Entity(30, 30, grassTexture),
    //                 			      Entity(30, 60, grassTexture)};

    std::vector<Entity> entities;
    std::vector<Entity> Xs;
    std::vector<Entity> Os;
    std::vector<Entity> Blanks;
	
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			Blanks.emplace_back(Entity(j * 30*5, i * 30*5, grassTexture));
	
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			Xs.emplace_back(Entity(j * 30*5, i * 30*5, XTexture));
	
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			Os.emplace_back(Entity(j * 30*5, i * 30*5, OTexture));
	
	bool gameRunning = true;

	SDL_Event event;
	
	std::thread ayy(GamePlay);
	std::thread lmao(Remote);
	while (gameRunning)
	{
		out.str.open("out.txt", std::ios::app);
		// Get our controls and events
		bool gameRunning =
		ProcessEvents(event);

		window.clear();
		
		//out.str << in << '\n';
		
		
		for(int i = 0; i < 8; ++i){
			std::cout << currentState[i] << ' ';
		}
		std::cout << '\n';
		
		for(int i = 0; i < 9; ++i){
			if(currentState[i] == 'X'){
				window.render(Xs[i]);
			}
			else if(currentState[i] == 'O'){
				window.render(Os[i]);
			}
			else{
				
				window.render(Blanks[i]);
			}
		}
		if(game.checkGame() != 1){
			out.str << "someone won\n wooooooooo\n \n\n";
		}
		out.str.close();

		window.display();

	}
	ayy.join();
	lmao.join();
	window.cleanUp();
	SDL_Quit();
	
	return 0;
}