//
//  main.c
//  SDLTutorials
//
//  Created by Nicolas Avila on 07-12-18.
//  Copyright © 2018 Nicolas Avila. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2_image/SDL_image.h>

int main(void) {
    //Inicializa
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
    }
    
    //Crea la ventana
    Uint32 win_flags = SDL_WINDOW_ALWAYS_ON_TOP;
    SDL_Window* win = SDL_CreateWindow("Nico SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, win_flags);
    if (!win) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    //Crea el renderer, que va a configurar el hardware gráfico
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    //Carga la imagen en memoria
    SDL_Surface* surface = IMG_Load("space_squid.png");
    if (!surface) {
        printf("Error al crear la superficie: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    //Carga la rextura
    SDL_Texture* text = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!text) {
        printf("Error al crear la textura: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    
    //Limpia la ventana
    SDL_RenderClear(rend);
    
    //Dibuja la imagen
    SDL_RenderCopy(rend, text, NULL, NULL);
    SDL_RenderPresent(rend);
    
    _Bool running = 1;
    while(running) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    running = 0;
                break;
            }
            
        }
    }
    
    SDL_DestroyWindow(win);
    SDL_Quit();
}
