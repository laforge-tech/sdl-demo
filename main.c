
#include <SDL2/SDL.h>

#include <unistd.h>

void fatal(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void loop() {
	SDL_Event event;

	for (;;) {
		SDL_Event event;

		// Deal with events
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_MOUSEBUTTONDOWN:
				printf("Mouse click: %d %d\n", event.button.x, event.button.y );
				break;
			case SDL_QUIT:
				return;
			}
		}

		// Sleep 10 ms
		usleep(10000);

		// Do some work
	}
}

int main(int argc, char* argv[]) {
	int cr;
	
	cr = SDL_Init(SDL_INIT_VIDEO);
	if (cr != 0) fatal("Erreur initialisation SDL");

	SDL_Window* w = SDL_CreateWindow("Hive", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED , 640, 480, SDL_WINDOW_SHOWN);
	if(w == NULL) {
        	fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
	        return EXIT_FAILURE;
    }

	SDL_Surface *tmp = SDL_LoadBMP("background.bmp");
	if (tmp == NULL) {
		fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	if (r == NULL) {
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(r, tmp);
	if (texture == NULL) {
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
		return EXIT_FAILURE;	
	}

	SDL_FreeSurface(tmp);

	SDL_RenderCopy(r, texture, NULL, NULL);

  	cr = SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (cr) {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

	//SDL_RenderClear(r);

  	cr = SDL_SetRenderDrawColor(r, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (cr) {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

  	cr = SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);
	if (cr) {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

	SDL_Point p1 = { 50, 50 };
	SDL_Point p2 = { 150, 50 };
	SDL_RenderDrawLine(r, 50,50, 200, 200);

	SDL_RenderPresent(r);

	loop();

	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);

	SDL_Quit();
}
