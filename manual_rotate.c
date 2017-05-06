#include <SDL.h>
#include <GL/gl.h>

// gcc cube.c $(sdl2-config --cflags --libs ) -lGL

/*
 * Rotate a multicolored cube.  One side changes colors
 */


int main() {
   SDL_Window *window;
   SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

   window = SDL_CreateWindow(
      "Move the Cube with your arrow keys",            // window title
      SDL_WINDOWPOS_UNDEFINED,                         // initial x position
      SDL_WINDOWPOS_UNDEFINED,                         // initial y position
      0,                                               // width, in pixels
      0,                                               // height, in pixels
      SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_RESIZABLE  // flags - see below
   );

   SDL_GLContext context = SDL_GL_CreateContext(window);
   SDL_GL_MakeCurrent(window, context);

   int w,h;

   SDL_GetWindowSize(window, &w, &h);
   glViewport(0,0,w,h);

   glEnable(GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
   glFrustum(1,-1,1,-1,0.5,100);
   glTranslatef(0,0,-1.5);
   glScalef((float)(w)/h,2,1);
   glMatrixMode(GL_MODELVIEW);

   SDL_GL_SetSwapInterval(1);


   while(1){
      SDL_PumpEvents();
      glBegin(GL_QUADS);

      glColor3ub(0xFF, 0x86, 0xf4);

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
      while (SDL_PollEvent(&e)){
         if (e.type == SDL_QUIT)
            return 0;
      }   
      int num = 0;

      const char* state = SDL_GetKeyboardState(&num);
      if(state[SDL_SCANCODE_UP]){
         glRotatef(1,1,0,0);
      }
      if(state[SDL_SCANCODE_DOWN]){
         glRotatef(-1,1,0,0);
      }
      if(state[SDL_SCANCODE_RIGHT]){
         glRotatef(1,0,1,0);
      }
      if(state[SDL_SCANCODE_LEFT]){
         glRotatef(-1,0,1,0);
      }
   }

   SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
   SDL_DestroyWindow(window);

   SDL_Quit();
   return 0;
}
