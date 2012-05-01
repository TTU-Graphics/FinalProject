#include "texTri.h"

TexTri::TexTri(const char* texture) {
  vShader = (char*)"texture.vert";
  fShader = (char*)"texture.frag";
  name = "TexturedTri";
  this->texture = texture;

  vertexCount = 3;
  bufferCount = 2;
  init();
}

void TexTri::buildModel() {
  vec4* points = new vec4[vertexCount];
  vec2* tex = new vec2[vertexCount];
  
  buildTri(points,0,
      vec4(-1, -1, 0.0, 1.),
      vec4( 0.,  1, 0.0, 1.),
      vec4( 1, -1, 0.0, 1.));

  tex[0] = vec2(0, 0);
  tex[1] = vec2(.5, 1);
  tex[2] = vec2(1, 0);

  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,points,"vPosition");

  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,tex,"vTexture");

  printf("setting texture=%s\n",texture);
  prog->setTexture(texture,GL_TEXTURE0,0,"Texture");
  //prog->setTexture("uv_checker.png",GL_TEXTURE0,0,"Texture");

  delete[] points;
  delete[] tex;
}
