#ifndef __CUBE_H
#define __CUBE_H

class Cube: public Model {
  public:
    Cube();
    void buildModel();
  private:
    GLuint vPosition, vColor;
    
    //functions
    void buildFace(vec4, vec4, vec4, vec4);
};

#endif
