#ifndef __PARTICLES_H
#define __PARTICLES_H
#include "model.h"
#include "helpers.h"
#include "Angel.h"
#include "light.h"

class Particles : public Model {
  public:
    Particles( int num );

    //functions
    void buildModel();
    void setModelView(mat4);
	void step(float seconds);
	mat4 physics(float seconds, int i);

	bool customRender();
    
  private:
    //shader variables
    GLuint vPosition, vColor;
    GLuint worldPosition, worldRotation;

    //variables
	int particles_to_display, counter; //Parameter to control delayed initial generation
    vec4 *points, *colors;
    vec3 *velocity;
	float last_time;
    //functions
};

#endif
