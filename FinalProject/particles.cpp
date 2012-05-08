#include "particles.h"
#include <cstdlib>
#include <cmath>

Particles::Particles( int num ) : Model(){
  printf("Creating Particles object with %d particles",num);
  last_time = 0;
  particles_to_display = 0;
  counter = 0;

  vShader = buildString("color.vert");
  fShader = buildString("color.frag");

  vertexCount = num;
  bufferCount = 2;

  points = new vec4[vertexCount];
  colors = new vec4[vertexCount];
  velocity = new vec3[vertexCount];
  
  printf("particles before init\n");
  init();
  printf("particles after init\n");
}

//{{{ build model functions
void Particles::buildModel() {
  printf("building particles\n");
  glUseProgram(program);

  for( int i=0; i<vertexCount; i++ )
  {
	  points[i] = vec4(0,0,0,1);
	  colors[i] = vec4((rand()*1.0)/(RAND_MAX*1.0),(rand()*1.0)/(RAND_MAX*1.0),(rand()*1.0)/(RAND_MAX*1.0),0.5);
	  // Initial velocities are random on [-.5,.5]x[0,1]x[-.5,.5] to make a nice fountain effect
	  velocity[i] = vec3((rand()*1.0)/(RAND_MAX*1.0)-0.5,(rand()*1.0)/(RAND_MAX*1.0),(rand()*1.0)/(RAND_MAX*1.0)-0.5);
  }

  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,points,"vPosition");

  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,colors,"vColor");


  /*worldPosition = glGetUniformLocation(program, "WorldPosition");
  worldRotation = glGetUniformLocation(program, "WorldRotation");//*/

  // set material shininess

  printf("done building sphere\n");
}

void Particles::setModelView(mat4 mat) {
  prog->setUniform(mat, "ModelView");
}

void Particles::step(float seconds) {
	counter = (counter+1)%5;
	if( counter==0 && particles_to_display++ > vertexCount )
	{
		particles_to_display = vertexCount;
	}

	for( int i=0; i<vertexCount; i++ )
	{
		if( abs(points[i].x) > 10 || abs(points[i].y) > 10 || abs(points[i].z) > 10 )
		{
			// If a particle leaves the acceptible region (can redefine this if necessary),
			// reset it to its initial position and re-randomize velocity.y since only y has acceleration
			points[i].x = 0;
			points[i].y = 0;
			points[i].z = 0;
			velocity[i].y = (rand()*1.0)/(RAND_MAX*1.0);
		}
		points[i] = physics(seconds, i) * points[i];
	}
	last_time = seconds;
}

mat4 Particles::physics(float seconds, int i) {
	velocity[i].y -= (seconds-last_time)*9.81; // Acceleration due to gravity
	return Translate( velocity[i].x*(seconds-last_time), velocity[i].y*(seconds-last_time), velocity[i].z*(seconds-last_time) );
}

bool Particles::customRender() {
  glEnable(GL_POINT_SMOOTH);
  glPointSize(100.0);
  // Buffer new particle locations
  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,points,"vPosition");

  glDrawArrays(GL_POINTS, 0, particles_to_display);
  return true;
}