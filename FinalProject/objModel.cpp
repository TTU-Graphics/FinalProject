#include "objModel.h"

ObjModel::ObjModel(const char* objFile,
	      int numLights, vec4 ambient, vec4 diffuse, vec4 specular)
		    : ShadedModel(numLights, ambient, diffuse, specular) {
  objFileName = objFile;
  bufferCount = 5; //verticies, normals, tangents, binormals, textures
  // init vertex count when building
  buildLightShader("multLightTex",buildString("multLightTex-%d",numLights),numLights);
  vShader = buildString("multLightTex-%d.vert",numLights);
  fShader = buildString("multLightTex-%d.frag",numLights);
  //vShader = "texture.vert";
  //fShader = "texture.frag";


  init();
}

void ObjModel::buildModel() {
  printf("building obj model\n");
  FILE *objFile = fopen(objFileName, "r");
  char line[256], materialFile[256], texFile[256], nMapFile[256];

  float x, y, z;
  float tex1s, tex1t,
	    tex2s, tex2t;
  float q1x, q1y, q1z,
	    q2x, q2y, q2z;
  float det;
  vec3  t, b;
  int v1, v2, v3,
      t1, t2, t3,
      n1, n2, n3;
  bool createdBuffers = false;
  vertexCount = 0;
  printf("reading obj file\n");
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
      //printf("reading vertex\n");
      sscanf(line, "v %f %f %f", &x, &y, &z);
      colVerts.push_back(vec4(x, y, z, 1.));
      vertexCount++;
    }
    // texture
    else if(line[0] == 'v' && line[1] == 't') {
      //printf("reading tex\n");
      sscanf(line, "vt %f %f", &x, &y);
      colTex.push_back(vec2(x, y));
    }
    // normal
    else if(line[0] == 'v' && line[1] == 'n') {
      //printf("reading normal\n");
      sscanf(line, "vn %f %f %f", &x, &y, &z);
      colNorms.push_back(vec3(x, y, z));
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
      //printf("reading face\n");
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
      norms.push_back(colNorms[n1-1]);
      norms.push_back(colNorms[n2-1]);
      norms.push_back(colNorms[n3-1]);
<<<<<<< HEAD
	  q1x = colVerts[v2-1].x - colVerts[v1-1].x;
	  q1y = colVerts[v2-1].y - colVerts[v1-1].y;
	  q1z = colVerts[v2-1].z - colVerts[v1-1].z;
	  q2x = colVerts[v3-1].x - colVerts[v1-1].x;
	  q2y = colVerts[v3-1].y - colVerts[v1-1].y;
	  q2z = colVerts[v3-1].z - colVerts[v1-1].z;
	  tex1s = colTex[v2-1].x - colTex[v1-1].x;
	  tex1t = colTex[v2-1].y - colTex[v1-1].y;
	  tex2s = colTex[v3-1].x - colTex[v1-1].x;
	  tex2t = colTex[v3-1].y - colTex[v1-1].y;
	  det = -1.0 / ( tex1s*tex2t - tex1t*tex2s );
=======
      q1x = colVerts[v2-1].x - colVerts[v1-1].x;
      q1y = colVerts[v2-1].y - colVerts[v1-1].y;
      q1z = colVerts[v2-1].z - colVerts[v1-1].z;
      q2x = colVerts[v3-1].x - colVerts[v1-1].x;
      q2y = colVerts[v3-1].y - colVerts[v1-1].y;
      q2z = colVerts[v3-1].z - colVerts[v1-1].z;
      tex1s = colTex[v2-1].x - colTex[v1-1].x;
      tex1t = colTex[v2-1].y - colTex[v1-1].y;
      tex2s = colTex[v3-1].x - colTex[v1-1].x;
      tex2t = colTex[v3-1].y - colTex[v1-1].y;
      det = 1.0 / ( tex1s*tex2t - tex1t*tex2s );
>>>>>>> 87885381c6fd250a2884d2a23c091237d228a8b4

      t = det * vec3( tex2t*q1x - tex1t*q2x,
          tex2t*q1y - tex1t*q2y,
          tex2t*q1z - tex1t*q2z );
      b = det * vec3( -tex2s*q1x + tex1s*q2x,
          -tex2s*q1y + tex1s*q2y,
          -tex2s*q1z + tex1s*q2z );
      tans.push_back(t);
      tans.push_back(t);
      tans.push_back(t);
      bitans.push_back(b);
      bitans.push_back(b);
      bitans.push_back(b);
    }
  }
  fclose(objFile);

  vertexCount = verts.size();
  vec4 *pVerts = &verts[0];
  vec3 *pNorms = &norms[0];
  vec3 *pTans = &tans[0];
  vec3 *pBitans = &bitans[0];
  vec2 *pTex = &tex[0];
  printf("vertexCount = %d\n",vertexCount);

  // set verticies, normals, tangents, bitangents, and texture coordinates
  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pVerts,"vPosition");
  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pNorms,"vNormal");
  prog->setBuffer(buffers[2],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pTans,"vTangent");
  prog->setBuffer(buffers[3],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pBitans,"vBitangent");
  prog->setBuffer(buffers[4],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pTex,"vTexture");

  // read material file
  printf("\tmaterial file \"%s\"\n",materialFile);
  FILE *mtlFile = fopen(materialFile, "r");
  printf("reading material file\n");
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
      //TODO: implement Ka
    }
    // Kd - diffuse
    else if(line[0] == 'K' && line[1] == 'd') {
      sscanf(line, "Ka %f %f %f", &x, &y, &z);
      //TODO: implement Kd
    }
    // Ks - specular
    else if(line[0] == 'K' && line[1] == 's') {
      sscanf(line, "Ka %f %f %f", &x, &y, &z);
      //TODO: implement Ks
    }
  }

  // set shininess
  glUniform1f( glGetUniformLocation(program, "Shininess"), 1.0);

  // set texture image
  printf("\ttexture file \"%s\"\n",texFile);
  prog->setTexture(texFile,"Texture");
  // set normal map
  printf("\tnormal map file\"%s\"\n",nMapFile);
  prog->setTexture(nMapFile,"NormalMap");
}

void ObjModel::preRender() {
  glActiveTexture(GL_TEXTURE1);
  prog->bindTexture();
}
