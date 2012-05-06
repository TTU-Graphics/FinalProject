#include "objModel.h"

ObjModel::ObjModel(const char* objFile,
	      int numLights, vec4 ambient, vec4 diffuse, vec4 specular)
		    : ShadedModel(numLights, ambient, diffuse, specular) {
  objFileName = objFile;
  bufferCount = 2; //verticies, texture coordinates (normals come from normal map)
  // init vertex count when building
  buildLightShader("multLightTex",buildString("multLightTex-%d",numLights),numLights);
  vShader = buildString("multLightTex-%d.vert",numLights);
  fShader = buildString("multLightTex-%d.frag",numLights);
  //vShader = "texture.vert";
  //fShader = "texture.frag";


  init();
}

void ObjModel::buildModel() {
  printf("\n");
  FILE *objFile = fopen(objFileName, "r");
  char line[256], materialFile[256], texFile[256], nMapFile[256];

  float x, y, z;
  int v1, v2, v3,
      t1, t2, t3,
      n1, n2, n3;
  bool createdBuffers = false;
  vertexCount = 0;
  clock_t time = clock();
  while( fgets(line, 256, objFile) != NULL) {
    // ignore comments
    if(line[0] == '#') {
      continue;
    }
    // material library
    else if(line[0] == 'm' && line[3] == 'l') {
      sscanf(line, "mtllib %s", materialFile);
    }
    // vertex
    else if(line[0] == 'v' && line[1] == ' ') {
      sscanf(line, "v %f %f %f", &x, &y, &z);
      colVerts.push_back(vec4(x, y, z, 1.));
      vertexCount++;
    }
    // texture
    else if(line[0] == 'v' && line[1] == 't') {
      sscanf(line, "vt %f %f", &x, &y);
      colTex.push_back(vec2(x, y));
    }
    // normal
    else if(line[0] == 'v' && line[1] == 'n') {
	  // Ignore normals since we're using object-space normal maps
	  continue;
      //sscanf(line, "vn %f %f %f", &x, &y, &z);
      //colNorms.push_back(vec3(x, y, z));
    }
    // use material
    else if(line[0] == 'u' && line[2] == 'm') {
      continue; // we are going to assume one material per object.
    }
    // s off
    else if(line[0] == 's') {
      continue; // we do not use this setting
    }
    // face
    else if(line[0] == 'f') {
      sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
          &v1, &t1, &n1,
          &v2, &t2, &n2,
          &v3, &t3, &n3);
      verts.push_back(colVerts[v1-1]);
      verts.push_back(colVerts[v2-1]);
      verts.push_back(colVerts[v3-1]);
      tex.push_back(colTex[t1-1]);
      tex.push_back(colTex[t2-1]);
      tex.push_back(colTex[t3-1]);
      //norms.push_back(colNorms[n1-1]);
      //norms.push_back(colNorms[n2-1]);
      //norms.push_back(colNorms[n3-1]);
    }
  }
  fclose(objFile);
  time = clock() - time;
  printf("read time of %s: %f\n",objFileName,((float)time)/CLOCKS_PER_SEC);

  time = clock();
  vertexCount = verts.size();
  vec4 *pVerts = &verts[0];
//  vec3 *pNorms = &norms[0];
  vec2 *pTex = &tex[0];
  printf("vertexCount = %d\n",vertexCount);

  // set verticies, normals, tangents, bitangents, and texture coordinates
  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pVerts,"vPosition");
  //prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
  //    vertexCount,pNorms,"vNormal");
  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pTex,"vTexture");

  time = clock() - time;
  printf("shader loading time of %s: %f\n",objFileName,((float)time)/CLOCKS_PER_SEC);

  // read material file
  printf("\tmaterial file \"%s\"\n",materialFile);
  time = clock();
  FILE *mtlFile = fopen(materialFile, "r");
  while( fgets(line, 256, objFile) != NULL) {
    // texture file
    // map_Kd textureFile
    if(line[0] == 'm' && line[5] == 'd') {
      sscanf(line, "map_Kd %s", texFile);
    }
    // map_Bump normal/bump map file
    if(line[0] == 'm' && line[7] == 'p') {
      sscanf(line, "map_Bump %s", nMapFile);
    }
    // Ka - ambient
    else if(line[0] == 'K' && line[1] == 'a') {
      sscanf(line, "Ka %f %f %f", &x, &y, &z);
      materialAmbient = vec4(x,y,z,1);
    }
    // Kd - diffuse
    else if(line[0] == 'K' && line[1] == 'd') {
      sscanf(line, "Kd %f %f %f", &x, &y, &z);
      materialDiffuse = vec4(x,y,z,1);
    }
    // Ks - specular
    else if(line[0] == 'K' && line[1] == 's') {
      sscanf(line, "Ks %f %f %f", &x, &y, &z);
      materialSpecular = vec4(x,y,z,1);
    }
  }
  //updateMaterialProducts();
  time = clock() - time;
  printf("material file loading time of %s: %f\n",materialFile,((float)time)/CLOCKS_PER_SEC);

  // set shininess
  glUniform1f( glGetUniformLocation(program, "Shininess"), 1.0);

  // set texture image
  printf("\ttexture file \"%s\"\n",texFile);
  time = clock();
  prog->setTexture(texFile,"Texture");
  time = clock() - time;
  printf("texture file loading time of %s: %f\n",texFile,((float)time)/CLOCKS_PER_SEC);
  // set normal map
  printf("\tnormal map file\"%s\"\n",nMapFile);
  time = clock();
  prog->setTexture(nMapFile,"NormalMap");
  time = clock() - time;
  printf("normal file loading time of %s: %f\n",nMapFile,((float)time)/CLOCKS_PER_SEC);
}

void ObjModel::preRender() {
  glActiveTexture(GL_TEXTURE1);
  prog->bindTexture();
}
