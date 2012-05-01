#include "colorTri.h"

ChainedTri::ChainedTri() {
  vShader = "color.vert";
  fShader = "color.frag";
  name = "ChainedTri";

  vertexCount = 3;
  bufferCount = 2;
  init();
}

void ChainedTri::buildModel() {
  vec4* points = new vec4[vertexCount];
  vec4* colors = new vec4[vertexCount];
  
  buildTri(points,0,
      vec4(-.3, -.3, 0.0, 1.),
      vec4( 0.,  .3, 0.0, 1.),
      vec4( .3, -.3, 0.0, 1.));

  for(int i=0;i<vertexCount;i++)
    colors[i] = vec4(0,0,1,1); //blue

  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(vec4),points,GL_STATIC_DRAW);
  vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError(name,"vPosition");

  glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
  glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(vec4),colors,GL_STATIC_DRAW);
  vColor = glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(vColor);
  glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glError(name,"vColor");

  delete[] points;
  delete[] colors;
}
