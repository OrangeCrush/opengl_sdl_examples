#include <SDL.h>
#include <GL/gl.h>

// gcc cube.c $(sdl2-config --cflags --libs ) -lGL

/*
 * Rotate a multicolored cube.  One side changes colors
 */

void draw_cube(float x, float y, float z, float n);


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


   float c_x = 0, c_z = 0;
   while(1){

      //Draw white plane
      glBegin(GL_QUADS);
      glColor3ub(0xFF,0xFF,0xFF);
      glVertex3f(1,0.5,1);
      glVertex3f(1,0.5,-1);
      glVertex3f(-1,0.5,-1);
      glVertex3f(-1,0.5,1);
      glEnd();


      SDL_Event e;
      while (SDL_PollEvent(&e)){
         if (e.type == SDL_QUIT)
            return 0;
      }   
      int num = 0;

      // Move the cube
      const char* state = SDL_GetKeyboardState(&num);
      if(state[SDL_SCANCODE_UP]){
        if (c_z >= -1) c_z -= 0.1;
      }
      if(state[SDL_SCANCODE_DOWN]){
        if (c_z <= 1) c_z += 0.1;
      }
      if(state[SDL_SCANCODE_RIGHT]){
        if (c_x >= -1) c_x -= 0.1; 
      }
      if(state[SDL_SCANCODE_LEFT]){
        if(c_x <= 1) c_x += 0.1; 
      }

      draw_cube(c_x,0.5,c_z,0.1);

      SDL_GL_SwapWindow(window);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   }

   SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example
   SDL_DestroyWindow(window);

   SDL_Quit();
   return 0;
}

void draw_cube(float x, float y, float z, float n){
      glBegin(GL_QUADS);

      glColor3ub(0x7F, 0x7F, 0x7F);

      // Front face
      glVertex3f(x+n,y+n,z+n);
      glVertex3f(x+n,y+-n,z+n);
      glVertex3f(x+-n,y+-n,z+n);
      glVertex3f(x+-n,y+n,z+n);


      // Back face
      glVertex3f(x+n,y+n,z+-n);
      glVertex3f(x+n,y+-n,z+-n);
      glVertex3f(x+-n,y+-n,z+-n);
      glVertex3f(x+-n,y+n,z+-n);


      // Top face
      glVertex3f(x+n,y+n,z+n);
      glVertex3f(x+n,y+n,z+-n);
      glVertex3f(x+-n,y+n,z+-n);
      glVertex3f(x+-n,y+n,z+n);


      // Bottom face
      glVertex3f(x+n,y+-n,z+n);
      glVertex3f(x+n,y+-n,z+-n);
      glVertex3f(x+-n,y+-n,z+-n);
      glVertex3f(x+-n,y+-n,z+n);

      // right face
      glVertex3f(x+n,y+-n,z+n);
      glVertex3f(x+n,y+-n,z+-n);
      glVertex3f(x+n,y+n,z+-n);
      glVertex3f(x+n,y+n,z+n);

      // left face
      glVertex3f(x+-n,y+-n,z+n);
      glVertex3f(x+-n,y+-n,z+-n);
      glVertex3f(x+-n,y+n,z+-n);
      glVertex3f(x+-n,y+n,z+n);

      glEnd();
}

