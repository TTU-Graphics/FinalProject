#include "Angel.h"
#include <time.h>
#include <math.h>
#include <list>
#include "helpers.h"
#include "menger.h"
#include "colorTri.h"
#include "shadedTri.h"
#include "sphere.h"
#include "light.h"
#include "texTri.h"
#include "scene/scene.h"
#include "animation/animator.h"
#include "animation/orbitalModel.h"

mat4 getView();
//{{{ Variables

Menger* menger;
ChainedTri *tri;
TexTri *tri2;
Sphere *sphere;
Animator* animator;
Light* light, *light2, *light3;
Scene *scene;

//models list
std::list<Model*> models;
std::list<Model*>::iterator modelIterator;

GLfloat fovy = 45.0; // Field of view in y angle (degres)
GLfloat aspect;      // Viewport aspect ratio
GLfloat zNear = 0.5, zFar = 50.0;

// eye movement variables
//const float pxToRad = (2*PI/360)/5.;  // 10px for ever degree angle
const float MAX_THETA = (89.0/360)*2*PI;
float camTheta = 0, camPhi = 0,
      upTheta  = (1*degToRad), upPhi = 0;
float camRadius = 15.;
vec4 eye = sphericalToPoint(camRadius, camTheta, camPhi,1.),
     at(0., 0., 0., 1.),
     up     = sphericalToPoint(camRadius, upTheta,  upPhi,0.);

// window variables
int winHeight = 512, winWidth = 512,
    mouseX, mouseY;
bool dragging;

// idle variables
clock_t lastAction;           // time when the last action was performed
clock_t delayToSpin = 3 * CLOCKS_PER_SEC; // seconds to delay since lastAction
float lastCamPhi;
float rotateDegPerSec = 20;

/**
 * Menu Constants
 */
const int
  MNU_SHOW_MENGER          =  1,
  MNU_SHOW_INVERSE_MENGER  =  2,
  MNU_RESET_CAM            =  3,
  MNU_INCREASE_SUBDIVS     =  4,
  MNU_DECREASE_SUBDIVS     =  5,
  MNU_ZOOM_IN              =  6,
  MNU_ZOOM_OUT             =  7,
  MNU_SHOW_GASKET          =  8,
  MNU_SET_PERSPECTIVE      =  9,
  MNU_SET_ORTHOGRAPHIC     = 10;

/**
 * View Types Constants
 */
const int
  VIEW_PERSPECTIVE = 1,
  VIEW_ORTHOGRAPHIC = 2;
int camView = 1;

/**
 * timing functions
 */
clock_t lastTick;
int clocksPerFrame = CLOCKS_PER_SEC/60;
//}}} End Variables
//{{{ recalculateCamera()
/**
 * Recalculates the camera based on the current thetas and phis
 */
void recalculateCamera() {
  //Ensure eye does not extend beyond [89,-89]
  if(camTheta > MAX_THETA) {
    camTheta = MAX_THETA;
  } else if(camTheta < -1*MAX_THETA) {
    camTheta = -1*MAX_THETA;
  }

  upTheta = camTheta + 1*degToRad;
  upPhi   = camPhi;

  eye = sphericalToPoint(camRadius, camTheta, camPhi, 1.);
  up  = sphericalToPoint(camRadius, upTheta,  upPhi,  0.);
}
//}}}
//{{{ Idle Function
void resetIdle() {
  lastAction = time(NULL);
  lastCamPhi = camPhi;
}
void idle() {
  clock_t ticks = clock();
  if(ticks - lastTick >= clocksPerFrame) {
    float seconds = ((float)ticks)/CLOCKS_PER_SEC;
    //animator->step(seconds);
    scene->tick(seconds);
    lastTick = ticks;
    glutPostRedisplay();
  }
}
//}}}
//{{{ Menu Selection (menuSelect(int selection))
/**
 * handles menu operations
 * can also be used in code to run the program
 */
void menuSelect(int selection) {
  switch(selection) {
    case MNU_SHOW_MENGER:
      menger->setType(Menger::NORMAL);
      break;
    case MNU_SHOW_INVERSE_MENGER:
      menger->setType(Menger::INVERSE);
      break;
    case MNU_RESET_CAM:
      camTheta = 0.;
      camPhi = 0.;
      recalculateCamera();
      break;
    case MNU_INCREASE_SUBDIVS:
      menger->incrementSubdivisions();
      break;
    case MNU_DECREASE_SUBDIVS:
      menger->decrementSubdivisions();
      break;
    case MNU_ZOOM_IN:
      camRadius -= 1;
      recalculateCamera();
      break;
    case MNU_ZOOM_OUT:
      camRadius += 1;
      recalculateCamera();
      break;
    case MNU_SET_PERSPECTIVE:
      camView = VIEW_PERSPECTIVE;
      break;
    case MNU_SET_ORTHOGRAPHIC:
      camView = VIEW_ORTHOGRAPHIC;
      break;
  }

  resetIdle();
  glutPostRedisplay();
}
//}}}
//{{{ Init Functions
//{{{ buildMenu()
int buildMenu()
{
  /*MNU_SHOW_MENGER          = 1,
  MNU_SHOW_INVERSE_MENGER  = 2,
  MNU_RESET_CAM            = 3,
  MNU_SIMPLE_COLORS        = 4,
  MNU_REALISTIC_COLORS     = 5,
  MNU_INCREASE_SUBDIVS     = 6,
  MNU_DECREASE_SUBDIVS     = 7,
  MNU_ZOOM_IN              = 8,
  MNU_ZOOM_OUT             = 9;*/
  int menu;
  menu = glutCreateMenu (menuSelect);
  glutAddMenuEntry("Show Menger\t\t\ts", MNU_SHOW_MENGER);
  glutAddMenuEntry("Show Inverse Menger\tS", MNU_SHOW_INVERSE_MENGER);
  //glutAddMenuEntry("Show Gasket\t\tg", MNU_SHOW_GASKET);
  glutAddMenuEntry("Increase Subdivisions\t+", MNU_INCREASE_SUBDIVS);
  glutAddMenuEntry("Decrease Subdivisions\t-", MNU_DECREASE_SUBDIVS);
  glutAddMenuEntry("Zoom In", MNU_ZOOM_IN);
  glutAddMenuEntry("Zoom Out", MNU_ZOOM_OUT);
  glutAddMenuEntry("Reset Camera", MNU_RESET_CAM);
  glutAddMenuEntry("Use Perspective View", MNU_SET_PERSPECTIVE);
  glutAddMenuEntry("Use Orthographic View", MNU_SET_ORTHOGRAPHIC);
  return menu;
}
//}}}
//{{{ Mouse and Keyboard Functions
/**
 * Assume that the eye is locked to a sphere of camRadius. Every
 * movement of x or y corresponds to a movement of the eye. The degrees
 * moved is determined via pxToRad.
 */
void mouseDragged(int x, int y) {
  if(!dragging) {
    return;
  }
  int dx = mouseX - x;
  int dy = mouseY - y;

  scene->mouseDragged(dx, dy);

  mouseX = x;
  mouseY = y;

  /*float dPhi   = dx * pxToRad;
  float dTheta = dy * pxToRad;

  camTheta += dTheta;
  camPhi   += dPhi;

  recalculateCamera();

  mouseX = x;
  mouseY = y;

  mat4 mv = LookAt(eye, at, up);
  scene->setWorldMatrix(mv);*/

  resetIdle();
  glutPostRedisplay();
}

void mouseButtonPressed(int button, int state, int x, int y) {
  if(state == GLUT_UP) {
    dragging = false;
  } else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    dragging = true;
    mouseX = x;
    mouseY = y;
  }

  if(button > 2) {
    printf("scroll button=%d\n",button);
  }
}

void keyPressed( unsigned char key, int x, int y )
{
  switch ( key ) {
    case 033:
      exit( EXIT_SUCCESS );
      break;
    case 'q':
      exit( EXIT_SUCCESS );
      break;

    case ' ': menuSelect(MNU_RESET_CAM); break;
    case 'o': menuSelect(MNU_SET_ORTHOGRAPHIC); break;
    case 'p': menuSelect(MNU_SET_PERSPECTIVE); break;

    case '+': menuSelect(MNU_INCREASE_SUBDIVS); break;
    case '-': menuSelect(MNU_DECREASE_SUBDIVS); break;

    case 's': menuSelect(MNU_SHOW_MENGER); break;
    case 'S': menuSelect(MNU_SHOW_INVERSE_MENGER); break;
    case 'g': menuSelect(MNU_SHOW_GASKET); break;

    case '0':
      menger->setSubdivisions(0);
      glutPostRedisplay();
      break;
    case '1':
      menger->setSubdivisions(1);
      glutPostRedisplay();
      break;
    case '2':
      menger->setSubdivisions(2);
      glutPostRedisplay();
      break;
    case '3':
      menger->setSubdivisions(3);
      glutPostRedisplay();
      break;
    case '4':
      menger->setSubdivisions(4);
      glutPostRedisplay();
      break;
  }
}
//}}}

void init( void )
{
  //create scene
  scene = new Scene("scene.js");
  printf("created scene\n");

  //create menger object
  /*menger = new Menger(vec3(0,0,0), 1, 2);
  tri = new ChainedTri();
  tri2 = new TexTri();
  sphere = new Sphere(0.7, 3, 2);
  Sphere *sphere2 = new Sphere(0.2, 3, 1);
  ShadedTri *sTri = new ShadedTri();
  Menger *m2 = new Menger(vec3(0,0,0), .4, 1);
  m2->setType(Menger::INVERSE);
  ChainedTri* tri3 = new ChainedTri();

  models.push_back(menger);
  models.push_back(tri);
  models.push_back(tri2);
  models.push_back(sphere);
  models.push_back(sphere2);
  models.push_back(sTri);
  models.push_back(m2);
  models.push_back(tri3);

  OrbitalModel *om = new OrbitalModel(menger, tri, 2, 0, 90);
  animator = new Animator();
  animator->addAnimation(om);
  animator->addAnimation(new OrbitalModel(tri, tri2, .5, 0, -360*3));
  animator->addAnimation(new OrbitalModel(menger, sphere, 4, 30, 0));
  animator->addAnimation(new OrbitalModel(sphere, sphere2, 1.3, 0, -10));
  animator->addAnimation(new OrbitalModel(menger, sTri, 3, -90, 0));
  animator->addAnimation(new OrbitalModel(menger, m2, 6, 30, 15));
  animator->addAnimation(new OrbitalModel(m2, tri3, 1, 5, 30));

  light = new Light(
      vec4(0,0,0,1),   //position
      vec4(.2,.2,.2,1), //ambient
      vec4(1,1,1,1),    //diffuse
      vec4(1,1,1,1));   //specular
  light2 = new Light(
      vec4(3,0,0,0),   //position
      vec4(.2,.2,.5,1), //ambient
      vec4(.2,.4,1,1),    //diffuse
      vec4(1,1,.8,1));   //specular
  light3 = new Light(
      vec4(0,1,0,0),   //position
      vec4(.2,.4,.2,1), //ambient
      vec4(1,1,.2,1),    //diffuse
      vec4(.3,1,1,1));   //specular
  sphere->setLight(light,0);
  sphere->setLight(light2,1);
  sphere2->setLight(light,0);
  sTri->setLight(light);//*/

  buildMenu();
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  // depth
  glEnable(GL_DEPTH_TEST);
  
  // texture
  glEnable(GL_TEXTURE_2D);

  // alpha
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor( 0.9, 0.9, 0.9, 1.0 ); // white background
}
//}}}
//{{{ Display functions
mat4 getView() {
  switch(camView) {
    case VIEW_PERSPECTIVE:
      return Perspective(fovy, aspect, zNear, zFar);
    case VIEW_ORTHOGRAPHIC:
      return Ortho(-1.5, 1.5, -1.5, 1.5, .5, 10.);
  }
}

void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window
  glFinish();

  //mat4 mv = LookAt(eye, at, up);
#ifdef DEBUG_MATS
  printf("set mv to:\n");
  printMat("mv",mv);
  printf("set p to:\n");
  printMat("p",p);
#endif

  //menger->setModelView(mv);
  //light->setWorldMatrix(mv);
  //sphere->setWorldMatrix(mv);
  //tri->setModelView(mv);

#ifdef DEBUG
  printf("displaying\n");
  //printVec("eye",eye);
  //printMat("menger mv",menger->getAdjustedModelView());
  //printMat("tri mv",tri->getAdjustedModelView());
#endif

  //render menger sponge
  /*for(modelIterator = models.begin(); modelIterator != models.end(); modelIterator++) {
    (*modelIterator)->render();
  }*/
  scene->render();
  /*menger->render();
  tri->render();
  tri2->render();
  sphere->render();*/

  glutSwapBuffers();
}

void reshape(int width, int height) {
  glViewport(0,0,width,height);
  aspect = GLfloat(width)/height;
  scene->setAspect(aspect);
  //mat4 p = getView();
  /*for(modelIterator = models.begin(); modelIterator != models.end(); modelIterator++) {
    (*modelIterator)->setProjection(p);
  }*/
  //scene->setProjection(p);
}
//}}}

int main( int argc, char **argv )
{
  srand(time(NULL));
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA );
  glutInitWindowSize( winHeight, winWidth );
  glutCreateWindow( "3D Menger Sponge" );

  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouseButtonPressed);
  glutMotionFunc(mouseDragged);

  resetIdle();
  glutIdleFunc(idle);
  
  //mat4 mv = LookAt(eye, at, up);
  //scene->setWorldMatrix(mv);

  const GLubyte *renderer = glGetString( GL_RENDERER );
  const GLubyte *vendor = glGetString( GL_VENDOR );
  const GLubyte *version = glGetString( GL_VERSION );
  const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
  GLint major, minor;
  //glGetIntegerv(GL_MAJOR_VERSION, &major);
  //glGetIntegerv(GL_MINOR_VERSION, &minor);
  printf("GL Vendor : %s\n", vendor);
  printf("GL Renderer : %s\n", renderer);
  printf("GL Version (string) : %s\n", version);
  //printf("GL Version (integer) : %d.%d\n", major, minor);
  printf("GLSL Version : %s\n", glslVersion);

  glutMainLoop();
  return 0;
}
