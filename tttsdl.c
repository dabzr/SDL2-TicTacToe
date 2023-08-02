#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

int variables[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Rect button[10] = {{170, 50, 75, 75}, {280, 50, 85, 75}, {410, 50, 75, 75}, {170, 170, 75, 75}, {280, 170, 85, 75}, {410, 170, 75, 75}, {170, 290, 75, 75}, {280, 290, 85, 75}, {410, 290, 75, 75}};


bool darkmode = true;
int ModeScreen, ModeTable;

int vez = 0;
int pos;

int isDarkMode(bool darkmode){
  if (darkmode){return 1;}
  else{return 255;}
}

void gameUI(SDL_Renderer *renderer, int ModeScreen){
  if (ModeScreen == 1){ModeTable=255;}
  else{ModeTable=1;}
  SDL_SetRenderDrawColor(renderer, ModeScreen, ModeScreen, ModeScreen, ModeScreen);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, ModeTable, ModeTable, ModeTable, ModeTable);
  SDL_Rect horizontal_rect_0= {170, 140, 320, 10};
  SDL_RenderFillRect(renderer, &horizontal_rect_0);
  SDL_Rect horizontal_rect_1= {170, 260, 320, 10};
  SDL_RenderFillRect(renderer, &horizontal_rect_1);
  SDL_Rect vertical_rect_0 = {260, 50, 10, 300};
  SDL_RenderFillRect(renderer, &vertical_rect_0);
  SDL_Rect vertical_rect_1 = {390, 50, 10, 300};
  SDL_RenderFillRect(renderer, &vertical_rect_1);
  SDL_SetRenderDrawColor(renderer, ModeScreen, ModeScreen, ModeScreen, ModeScreen);
  for (int i=0;i<9;i++){SDL_RenderFillRect(renderer, &button[i]);}

  SDL_SetRenderDrawColor(renderer, ModeTable, ModeTable, ModeTable, ModeTable);

  if (vez >= 1){
    SDL_Surface* surface;
    if (vez%2 == 0){surface = IMG_Load("O.png");}
    else{surface = IMG_Load("x.png");}
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    for (int i=0;i<9;i++){
      if(pos == i){
        SDL_QueryTexture(tex, NULL, NULL, &button[i].w, &button[i].h);
        SDL_RenderCopy(renderer, tex, NULL, &button[i]);}
    }
  }
  

  SDL_RenderPresent(renderer);
}


static int regionMatch(const SDL_Rect *rect, int x, int y){
  return ((x>=rect->x) && (x <= rect->x + rect->w) && (y >= rect->y ) && (y <= rect->y + rect->h));
}

void windowLoop(SDL_Window *window, SDL_Renderer *renderer){
  int x, y;
  int done = 0;
  SDL_Event event;
  while(!done){
    while(SDL_PollEvent(&event)){
      switch(event.type){
        case SDL_WINDOWEVENT_CLOSE:
          {
            if (window){
              SDL_DestroyWindow(window);
              window = NULL;}
          }
          break;
    case SDL_QUIT:
        done = 1;
      break;
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&x, &y);
          
        for (int i=0;i<9;i++){
          if ((regionMatch(&button[i], x, y)) && variables[i] == 0){
            vez++;
            pos = i;
            variables[i]++;
            }
        }
      break;
      }
    } 
  gameUI(renderer, isDarkMode(darkmode));
  }
  SDL_DestroyWindow(window);
SDL_DestroyRenderer(renderer);
}

int main (){
  window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
  windowLoop(window, renderer);

}
