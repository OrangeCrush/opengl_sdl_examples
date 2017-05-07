#include <SDL.h>
#include <GL/gl.h>

// gcc cube.c $(sdl2-config --cflags --libs ) -lGL

/*
 * Grass and texture example
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

   // Enable Lighting
   float light_position[] = {0,-1,0,1};

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);


   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_TEXTURE_2D);

   SDL_GL_SetSwapInterval(1);

   SDL_Surface *bmp = SDL_LoadBMP("img/grass.bmp");

   int texture = 0;

   glGenTextures(1, &texture);

   glBindTexture(GL_TEXTURE_2D, texture);

   glTexImage2D(GL_TEXTURE_2D, 0, 3, bmp->w, bmp->h, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp->pixels);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   float c_x = 0, c_z = 0;
   while(1){

      //Draw green plane
      float color[] = {0.0,0.5,0,1};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glNormal3f(0,-1,0);
      glVertex3f(1,0.5,1);

      glTexCoord2f(1,0);
      glVertex3f(1,0.5,-1);

      glTexCoord2f(1,1);
      glVertex3f(-1,0.5,-1);

      glTexCoord2f(0,1);
      glVertex3f(-1,0.5,1);
      glEnd();

      SDL_Event e;
      while (SDL_PollEvent(&e)){
         if (e.type == SDL_QUIT)
            return 0;
      }   

      SDL_GL_SwapWindow(window);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   }

   SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
   SDL_DestroyWindow(window);

   SDL_Quit();
   return 0;
}
