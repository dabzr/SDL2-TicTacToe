#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int variables[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int hist[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char plays[10] = "         ";
char XO[3] = "OX";
char space[2] = " ";
char winner;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *label;
TTF_Font *font;

SDL_Rect button[10] = {{170, 50, 75, 75}, {280, 50, 85, 75}, {410, 50, 75, 75}, {170, 170, 75, 75}, {280, 170, 85, 75}, {410, 170, 75, 75}, {170, 290, 75, 75}, {280, 290, 85, 75}, {410, 290, 75, 75}};
SDL_Texture *texture[10];

bool darkmode = true;
int ModeScreen, ModeTable;

int vez = 0;
int pos;

int isDarkMode(bool darkmode){
  if (darkmode){return 1;}
  else{return 255;}
}

int verifyVictory(char pl[10]){
  if ((pl[0] == pl[1]) && (pl[1] == pl[2]) && (pl[0] != space[0])) {winner = pl[0]; return 1;}
  else if ((pl[3] == pl[4]) && (pl[4] == pl[5]) && (pl[3] != space[0])) {winner = pl[3];return 1;}
  else if ((pl[6] == pl[7]) && (pl[7] == pl[8]) && (pl[6] != space[0])) {winner = pl[6];return 1;}
  else if ((pl[0] == pl[3]) && (pl[3] == pl[6]) && (pl[6] != space[0])){winner = pl[6];return 1;}
  else if ((pl[1] == pl[4]) && (pl[4] == pl[7]) && (pl[7] != space[0])){winner = pl[7];return 1;}
  else if ((pl[2] == pl[5]) && (pl[5] == pl[8]) && (pl[8] != space[0])){winner = pl[8];return 1;}
  else if ((pl[0] == pl[4]) && (pl[4] == pl[8]) && (pl[0] != space[0])){winner = pl[0];return 1;}
  else if ((pl[2] == pl[4]) && (pl[4] == pl[6]) && (pl[2] != space[0])){winner = pl[2];return 1;}
  else if ((pl[0] != space[0]) && (pl[1] != space[0]) && (pl[2] != space[0]) && (pl[3] != space[0]) && (pl[4] != space[0]) && (pl[5] != space[0]) && (pl[6] != space[0]) && (pl[7] != space[0]) && (pl[8] != space[0]))
        {return 2;}
  else{return 0;}
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
    if (!(vez%2)) surface = IMG_Load("../png/O.png");
    else surface = IMG_Load("../png/x.png");
    texture[vez] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    for (int i=0;i<9;i++){
      if(pos == i){
        SDL_QueryTexture(texture[vez], NULL, NULL, &button[i].w, &button[i].h);
        SDL_RenderCopy(renderer, texture[vez], NULL, &button[i]);}
    }
    if (vez>1){
      for (int i=1;i<=vez;i++){
        if (pos != hist[i])
        SDL_RenderCopy(renderer, texture[i], NULL, &button[hist[i]]);
      }
    }
  
  }
  if((verifyVictory(plays) == 1) || (verifyVictory(plays) == 2)){
    TTF_Init();
    font = TTF_OpenFont("../fonts/arial.ttf", 24);
    char text[25];
    sprintf(text, "Player %c is the Winner", winner);
    if (verifyVictory(plays) == 2){sprintf(text, "Draw!");}
    SDL_Color color = {ModeTable, ModeTable, ModeTable, ModeTable};
    SDL_Surface *tmp = TTF_RenderText_Blended(font, text, color); 
    SDL_Texture *tmpTex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_Rect textRect = {200, 400, tmp->w, tmp->h};
    SDL_RenderCopy(renderer, tmpTex, NULL, &textRect);
    SDL_FreeSurface(tmp);
    SDL_DestroyTexture(tmpTex);
    TTF_Quit();
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
            variables[i]++;
            vez++;
            hist[vez]=i;
            pos = i;
            plays[pos] = XO[vez%2];
          }
        }
      break;
      }
    }
  gameUI(renderer, isDarkMode(darkmode));

  if (verifyVictory(plays) == 1){
    gameUI(renderer, isDarkMode(darkmode));
    SDL_Delay(3000);
    break;
    }
  if (verifyVictory(plays) == 2){
    gameUI(renderer, isDarkMode(darkmode));
    SDL_Delay(3000);
    break;
  }
  }
  SDL_DestroyWindow(window);
SDL_DestroyRenderer(renderer);
}

int main (){
  window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
  windowLoop(window, renderer);

}
