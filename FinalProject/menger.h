#ifndef __MENGER_H
#define __MENGER_H

//#include "chainedModel.h"
#include "model.h"
#include "helpers.h"

class Menger: public Model {//ChainedModel {
  public:
    static const int maxSubdivisions = 4;
    enum MengerType {
      NORMAL, INVERSE
    };

    //constructor
    Menger(vec3 center, float radius, int subdivs);//, ChainedModel *parent = NULL);
    
    //functions
    void buildModel();
    void setCenter(vec3 center);
    void setRadius(float radius);
    void setSubdivisions(int subdivs);
    void setType(MengerType type);
    void incrementSubdivisions();
    void decrementSubdivisions();

  protected:
    void buildFace(vec4* face, int color);
    void buildCube(vec3 center, float radius);

  private:
    GLuint vPosition, vColor;
    vec4 *points, *colors;
    int index, curSubdivisions;
    vec3 cubeCenter;
    float cubeRadius;
    MengerType curType;

    //functions
    int computeVerticies(int subdivs);
    int computeInverseVerticies(int subdivs);
    void subdivideMenger(vec3 center, float radius, int subs);
    void subdivideInverseMenger(vec3 center, float radius, int subs);
    void rebuild();

    //function pointers
    void (Menger::*subdivideFn) (vec3 center, float radius,int subs);
    int (Menger::*computeVerticiesFn) (int subdivisions);
};

#endif
