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

SDL_Rect button0 = {170, 50, 75, 75};
SDL_Rect button1 = {280, 50, 85, 75};
SDL_Rect button2 = {410, 50, 75, 75};
SDL_Rect button3 = {170, 170, 75, 75};
SDL_Rect button4 = {280, 170, 85, 75};
SDL_Rect button5 = {410, 170, 75, 75};
SDL_Rect button6 = {170, 290, 75, 75};
SDL_Rect button7 = {280, 290, 85, 75};
SDL_Rect button8 = {410, 290, 75, 75};

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
  SDL_RenderFillRect(renderer, &button0);
  SDL_RenderFillRect(renderer, &button1);
  SDL_RenderFillRect(renderer, &button2);
  SDL_RenderFillRect(renderer, &button3);
  SDL_RenderFillRect(renderer, &button4);
  SDL_RenderFillRect(renderer, &button5);
  SDL_RenderFillRect(renderer, &button6);
  SDL_RenderFillRect(renderer, &button7);
  SDL_RenderFillRect(renderer, &button8);

  SDL_SetRenderDrawColor(renderer, ModeTable, ModeTable, ModeTable, ModeTable);

  if (vez >= 1){
    SDL_Surface* surface;
    if (vez%2 == 0){surface = IMG_Load("O.png");}
    else{surface = IMG_Load("x.png");}
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(pos == 0){
      SDL_QueryTexture(tex, NULL, NULL, &button0.w, &button0.h);
      SDL_RenderCopy(renderer, tex, NULL, &button0);}

    if (pos == 1){
      SDL_QueryTexture(tex, NULL, NULL, &button1.w, &button1.h);
      SDL_RenderCopy(renderer, tex, NULL, &button1);}
    if (pos == 2){
      SDL_QueryTexture(tex, NULL, NULL, &button2.w, &button2.h);
      SDL_RenderCopy(renderer, tex, NULL, &button2);}
    if (pos == 3){
      SDL_QueryTexture(tex, NULL, NULL, &button3.w, &button3.h);
      SDL_RenderCopy(renderer, tex, NULL, &button3);}
    if (pos == 4){
      SDL_QueryTexture(tex, NULL, NULL, &button4.w, &button4.h);
      SDL_RenderCopy(renderer, tex, NULL, &button4);}
    if (pos == 5){
      SDL_QueryTexture(tex, NULL, NULL, &button5.w, &button5.h);
      SDL_RenderCopy(renderer, tex, NULL, &button5);}
    if (pos == 6){
      SDL_QueryTexture(tex, NULL, NULL, &button6.w, &button6.h);
      SDL_RenderCopy(renderer, tex, NULL, &button6);}
    if (pos == 7){
      SDL_QueryTexture(tex, NULL, NULL, &button7.w, &button7.h);
      SDL_RenderCopy(renderer, tex, NULL, &button7);}
    if (pos == 8){
      SDL_QueryTexture(tex, NULL, NULL, &button8.w, &button8.h);
      SDL_RenderCopy(renderer, tex, NULL, &button8);}
    
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
        if ((regionMatch(&button0, x, y)) && variables[0] == 0){
            vez++;
            pos = 0;
            variables[0]++;
          }
        if ((regionMatch(&button1, x, y)) && variables[1] == 0){
            vez++;
            pos = 1;
            variables[1]++;
          }
        if ((regionMatch(&button2, x, y)) && variables[2] == 0){
            vez++;
            pos = 2;
            variables[2]++;
          }
        if ((regionMatch(&button3, x, y)) && variables[3] == 0){
            vez++;
            pos = 3;
            variables[3]++;
          }
        if ((regionMatch(&button4, x, y)) && variables[4] == 0){
            vez++;
            pos = 4;
            variables[4]++;
          }
        if ((regionMatch(&button5, x, y)) && variables[5] == 0){
            vez++;
            pos = 5;
            variables[5]++;
          }
        if ((regionMatch(&button6, x, y)) && variables[6] == 0){
            vez++;
            pos = 6;
            variables[6]++;
          }
        if ((regionMatch(&button7, x, y)) && variables[7] == 0){
            vez++;
            pos = 7;
            variables[7]++;
          }
        if ((regionMatch(&button8, x, y)) && variables[8] == 0){
            vez++;
            pos = 8;
            variables[8]++;
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
