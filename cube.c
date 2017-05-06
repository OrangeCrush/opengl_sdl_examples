#include <SDL.h>
#include <GL/gl.h>

// gcc graphics.c $(sdl2-config --cflags --libs ) -lGL

/*
 * Rotate a multicolored cube.  One side changes colors
 */


int main() {
   SDL_Window *window;
   SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

   window = SDL_CreateWindow(
      "An SDL2 window",                                // window title
      SDL_WINDOWPOS_UNDEFINED,                         // initial x position
      SDL_WINDOWPOS_UNDEFINED,                         // initial y position
      640,                                             // width, in pixels
      480,                                             // height, in pixels
      SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN_DESKTOP  // flags - see below
   );

   SDL_GLContext context = SDL_GL_CreateContext(window);
   SDL_GL_MakeCurrent(window, context);

   int w,h;

   SDL_GetWindowSize(window, &w, &h);
   glViewport(0,0,w,h);

   glEnable(GL_DEPTH_TEST);


   int color = 0;

   while(1){
      SDL_PumpEvents();
      glRotatef(1,5,5,5);
      glBegin(GL_QUADS);

      glColor3ub(color++ & 0x0FF, 0x86, 0xf4);

      // Front face
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(0.5,-0.5,0.5);
      glVertex3f(-0.5,-0.5,0.5);
      glVertex3f(-0.5,0.5,0.5);


      glColor3ub(0xb9, 0xf4, 0x42);
      // Back face
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(0.5,-0.5,-0.5);
      glVertex3f(-0.5,-0.5,-0.5);
      glVertex3f(-0.5,0.5,-0.5);


      glColor3ub(0xef, 0x04, 0x10);
      // Top face
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(-0.5,0.5,-0.5);
      glVertex3f(-0.5,0.5,0.5);


      glColor3ub(0xf1, 0xf4, 0x42);
      // Bottom face
      glVertex3f(0.5,-0.5,0.5);
      glVertex3f(0.5,-0.5,-0.5);
      glVertex3f(-0.5,-0.5,-0.5);
      glVertex3f(-0.5,-0.5,0.5);

      glColor3ub(0xf4, 0x42, 0xce);
      // right face
      glVertex3f(0.5,-0.5,0.5);
      glVertex3f(0.5,-0.5,-0.5);
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(0.5,0.5,0.5);

      glColor3ub(0xf4, 0x42, 0xce);
      // left face
      glVertex3f(-0.5,-0.5,0.5);
      glVertex3f(-0.5,-0.5,-0.5);
      glVertex3f(-0.5,0.5,-0.5);
      glVertex3f(-0.5,0.5,0.5);

      glEnd();
      SDL_GL_SwapWindow(window);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

      SDL_Event e;
      while (SDL_PollEvent(&e))
      {   
         if (e.type == SDL_QUIT)
            return 0;
      }   

   }

   SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
   SDL_DestroyWindow(window);

   SDL_Quit();
   return 0;
}
