#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>

class Game {
protected:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture[10];
  TTF_Font* font;

  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {1, 1, 1, 1};

  std::array<int, 10> variables = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::array<int, 10> hist = variables;

  char plays[10] = "         ";
  char XO[3] = "OX";
  char winner;
  unsigned vez = 0, pos;

  SDL_Rect button[10] = {
      {170, 50, 75, 75}, {280, 50, 85, 75}, {410, 50, 75, 75},
      {170, 170, 75, 75}, {280, 170, 85, 75}, {410, 170, 75, 75},
      {170, 290, 75, 75}, {280, 290, 85, 75}, {410, 290, 75, 75}
  };

  SDL_Rect table_rects[4] = {
      {170, 140, 320, 10}, {170, 260, 320, 10}, // Horizontal
      {260, 50, 10, 300}, {390, 50, 10, 300}    // Vertical
  };

  int regionMatch(const SDL_Rect* rect, int x, int y) {
    return (x >= rect->x) && (x <= rect->x + rect->w) && (y >= rect->y) && (y <= rect->y + rect->h);
  }

  const int verifyVictory() {
    int winCombinations[8][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Horizontal
      {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Vertical
      {0, 4, 8}, {2, 4, 6}              // Diagonal
      };
    int a, b, c;
    for (int i = 0; i < 8; i++) {
      a = winCombinations[i][0];
      b = winCombinations[i][1];
      c = winCombinations[i][2];

      if (plays[a] != ' ' && plays[a] == plays[b] && plays[b] == plays[c]) {
        winner = plays[a];
        return 1;
      }
    }
    for (int i = 0; i < 9; i++)
      if (plays[i] == ' ')
        return 0;
    return 2;
  }

public:
  Game(SDL_Window* _window) : window(_window), renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) {
    TTF_Init();
    font = TTF_OpenFont("fonts/arial.ttf", 24);
  }
  ~Game() {
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
  }
};

class Graphics : public Game{
  public:
    Graphics(SDL_Window *window):Game(window){}
  protected:
    int notwon = 1;
    void gameUI(){
      SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
      SDL_RenderFillRect(renderer, &table_rects[0]);
      SDL_RenderFillRect(renderer, &table_rects[1]);
      SDL_RenderFillRect(renderer, &table_rects[2]);
      SDL_RenderFillRect(renderer, &table_rects[3]);
      if (vez){
        SDL_Surface* surface;
        if (!(vez%2)) surface = IMG_Load("png/O.png");
        else surface = IMG_Load("png/x.png");
        texture[vez] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        for (int i=0;i<9;i++)
          if(pos == i){
            SDL_QueryTexture(texture[vez], NULL, NULL, &button[i].w, &button[i].h);
            SDL_RenderCopy(renderer, texture[vez], NULL, &button[i]);}
        if (vez>1)
          for (int i=1;i<=vez;i++)
            if (pos != hist[i])
              SDL_RenderCopy(renderer, texture[i], NULL, &button[hist[i]]);
      }
      if(verifyVictory()){
        TTF_Init();
        font = TTF_OpenFont("fonts/arial.ttf", 24);
        char text[25];
        std::sprintf(text, "Player %c is the Winner", winner);
        if (verifyVictory() == 2)
          std::sprintf(text, "The players tied!");
        SDL_Surface *tmp = TTF_RenderText_Blended(font, text, white); 
        SDL_Texture *tmpTex = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_Rect textRect = {200, 400, tmp->w, tmp->h};
        SDL_RenderCopy(renderer, tmpTex, NULL, &textRect);
        SDL_FreeSurface(tmp);
        SDL_DestroyTexture(tmpTex);
        notwon = 0;
      }
      SDL_RenderPresent(renderer);
    }
};
class StartGame : public Graphics {
public:
    StartGame(SDL_Window* _window): Graphics(_window) {}
    void startGame() {
      int running = 1;
      int x, y;
      int done = 0;
      SDL_Event event;
      while (!done) {
        while (SDL_PollEvent(&event)) {
          switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE:
              if (window) {
                SDL_DestroyWindow(window);
                window = nullptr;
              }
              break;
              case SDL_QUIT:
                done = 1;
                break;
              case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                for (int i = 0; i < 9; i++) {
                  if ((regionMatch(&button[i], x, y)) && variables[i] == 0) {
                    variables[i]++;
                    vez++;
                    hist[vez] = i;
                    pos = i;
                    plays[pos] = XO[vez % 2];
                  }
                }
                break;
          case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
              case SDLK_ESCAPE:
              done = 1;
              break;
            }
          }
        }
          if (notwon==1)
            gameUI();
          if (!notwon){
            SDL_RenderPresent(renderer);
            notwon=2;
        }
      }
      if(verifyVictory())
        TTF_Quit();
      SDL_DestroyWindow(window);
      window = nullptr;
  }
};

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  StartGame jogo(window);
  jogo.startGame();

  IMG_Quit();
  SDL_Quit();

  return 0;
}
