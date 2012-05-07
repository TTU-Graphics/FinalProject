//#include "particles.h"
//
//Particles::Particles(float radius, int subdivs,
//    int numLights, vec4 ambient, vec4 diffuse,
//    vec4 specular): ShadedModel(numLights, ambient, diffuse, specular) {
//  this->radius = radius;
//  subdivisions = subdivs;
//
//  name = "sphere";
//  buildLightShader("multLight",buildString("multLight-%d",numLights),numLights);
//  vShader = buildString("multLight-%d.vert",numLights);
//  fShader = buildString("multLight-%d.frag",numLights);
//  //vShader = "multlight.vert";
//  //fShader = "multlight.frag";
//  vertexCount = calculateVerticies(subdivisions);
//  bufferCount = 2;
//
//  /*materialAmbient = vec4(1,0,1,1);
//  materialDiffuse = vec4(1,.8,0,1);
//  materialSpecular = vec4(1,0,1,1);*/
//
//  //hasLight = false;
//
//  printf("sphere before init\n");
//  init();
//  printf("sphere after init\n");
//}
//
////{{{ build model functions
//void Particles::buildModel() {
//  printf("building particles\n");
//  glUseProgram(program);
//  vec4* points = new vec4[vertexCount];
//  vec4* normals = new vec4[vertexCount];
//  ptsIndex = 0;
//
//
//  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
//      vertexCount,points,"vPosition");
//
//
//  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
//      vertexCount,normals,"vNormal");
//
//  delete[] points;
//  delete[] normals;
//
//  ambientProduct = glGetUniformLocation(program, "AmbientProduct");
//  diffuseProduct = glGetUniformLocation(program, "DiffuseProduct");
//  specularProduct = glGetUniformLocation(program, "SpecularProduct");
//  lightPosition = glGetUniformLocation(program, "LightPosition");
//
//  normalMatrix = glGetUniformLocation(program, "NormalMatrix");
//  /*worldPosition = glGetUniformLocation(program, "WorldPosition");
//  worldRotation = glGetUniformLocation(program, "WorldRotation");//*/
//
//  // set material shininess
//  glUniform1f( glGetUniformLocation(program, "Shininess"), 5.0);
//
//  printf("done building sphere\n");
//}
//
//void Particles::setModelView(mat4 mat) {
//  prog->setUniform(mat, "ModelView");
//}
//
//bool Particles::customRender() {
//
//
//	glDrawArrays(GL_POINTS, 0, particle_count);
//	return true;
//}