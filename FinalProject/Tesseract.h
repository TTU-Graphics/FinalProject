#ifndef __TESSERACT_H__
#define __TESSERACT_H__

#include "Angel.h"
#include "shadedModel.h"

class Tesseract : public ShadedModel {
public:
	Tesseract( int numLights,
        vec4 ambient = vec4(1,1,1,1),
        vec4 diffuse = vec4(1,1,1,1),
        vec4 specular = vec4(1,1,1,1) );

    // overloaded methods
    void buildModel();
    void preRender();
	
	static GLfloat theta;

private:
	void tesseract( const vec4& center, GLfloat face_dist );
	void face( const vec4& a, const vec4& b, const vec4& c, const vec4& d );
	void triangle( const vec4& a, const vec4& b, const vec4& c, int color );

	vec4 *colors;
	vec4 *points, *normals, *pVerts, *pNorms;
	int Index, face_num;
};

#endif
