#include "Tesseract.h"

GLfloat Tesseract::theta = 0;

Tesseract::Tesseract( int numLights, vec4 ambient, vec4 diffuse, vec4 specular)
	: ShadedModel(numLights, ambient, diffuse, specular)
{
  bufferCount = 2; //verticies, normals
  buildLightShader("Tesseract",buildString("Tesseract-%d",numLights),numLights);
  vShader = buildString("Tesseract-%d.vert",numLights);
  fShader = buildString("Tesseract-%d.frag",numLights);

  colors = new vec4[24];
  colors[0] = vec4(1.0, 0.0, 0.0, 0.3);
  colors[1] = vec4(0.0, 1.0, 0.0, 0.3);
  colors[2] = vec4(0.0, 0.0, 1.0, 0.3);
  colors[3] = vec4(1.0, 1.0, 0.0, 0.3);
  colors[4] = vec4(1.0, 0.0, 1.0, 0.3);
  colors[5] = vec4(0.0, 1.0, 1.0, 0.3);
  colors[6] = vec4(0.1, 0.2, 0.3, 0.3);
  colors[7] = vec4(0.2, 0.1, 0.3, 0.3);
  colors[8] = vec4(0.1, 0.3, 0.2, 0.3);
  colors[9] = vec4(0.2, 0.3, 0.1, 0.3);
  colors[10] = vec4(0.3, 0.2, 0.1, 0.3);
  colors[11] = vec4(0.3, 0.1, 0.2, 0.3);
  colors[12] = vec4(0.7, 0.2, 1.0, 0.3);
  colors[13] = vec4(0.7, 1.0, 0.2, 0.3);
  colors[14] = vec4(0.2, 0.7, 1.0, 0.3);
  colors[15] = vec4(0.2, 1.0, 0.7, 0.3);
  colors[16] = vec4(1.0, 0.2, 0.7, 0.3);
  colors[17] = vec4(1.0, 0.7, 0.2, 0.3);
  colors[18] = vec4(0.5, 0.3, 0.0, 0.3);
  colors[19] = vec4(0.5, 0.0, 0.3, 0.3);
  colors[20] = vec4(0.0, 0.3, 0.5, 0.3);
  colors[21] = vec4(0.0, 0.5, 0.3, 0.3);
  colors[22] = vec4(0.3, 0.0, 0.5, 0.3);
  colors[23] = vec4(0.3, 0.5, 0.0, 0.3);

  init();
}

void Tesseract::buildModel()
{
  vertexCount = 6*24;
  points = new vec4[vertexCount];
  normals = new vec4[vertexCount];

  pVerts = &points[0];
  pNorms = &normals[0];
  printf("vertexCount = %d\n",vertexCount);

  tesseract( vec4(0), 0.5 );

  // set verticies and normals/colors
  prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pVerts,"vPosition");
  prog->setBuffer(buffers[1],BUFFER_OFFSET(0),GL_FLOAT,
      vertexCount,pNorms,"vNormal");

  std::cout << "Tesseract created" << std::endl;
}

void Tesseract::preRender()
{
	prog->setUniform(Tesseract::theta, "Theta");
}

void Tesseract::triangle( const vec4& a, const vec4& b, const vec4& c, int color )
{
    points[Index] = a;  normals[Index] = colors[color]; normals[Index].w = 0.6;  Index++;
    points[Index] = b;  normals[Index] = colors[color]; normals[Index].w = 0.6;  Index++;
    points[Index] = c;  normals[Index] = colors[color]; normals[Index].w = 0.6;  Index++;
}

void Tesseract::face( const vec4& a, const vec4& b, const vec4& c, const vec4& d )
{
	//std::cout << "\tBuilding face" << std::endl;
	triangle(a,b,d, face_num);
	triangle(d,b,c, face_num);
	face_num++;

	//face_vertices[face_index] = a; face_index++;
	//face_vertices[face_index] = b; face_index++;

	//face_vertices[face_index] = b; face_index++;
	//face_vertices[face_index] = c; face_index++;

	//face_vertices[face_index] = c; face_index++;
	//face_vertices[face_index] = d; face_index++;
	//
	//face_vertices[face_index] = d; face_index++;
	//face_vertices[face_index] = a; face_index++;
	//FaceVerticesUsed += 8;
}

void Tesseract::tesseract( const vec4& center, GLfloat face_dist )
{
	std::cout << "Building tesseract" << std::endl;
	Index = 0;
	face_num = 0;

	vec4 a = center + vec4(-1.0*face_dist,-1.0*face_dist,-1.0*face_dist,1.0*face_dist);
	vec4 b = center + vec4(1.0*face_dist,-1.0*face_dist,-1.0*face_dist,1.0*face_dist);
	vec4 c = center + vec4(1.0*face_dist,1.0*face_dist,-1.0*face_dist,1.0*face_dist);
	vec4 d = center + vec4(-1.0*face_dist,1.0*face_dist,-1.0*face_dist,1.0*face_dist);
	vec4 e = center + vec4(-1.0*face_dist,1.0*face_dist,1.0*face_dist,1.0*face_dist);
	vec4 f = center + vec4(1.0*face_dist,1.0*face_dist,1.0*face_dist,1.0*face_dist);
	vec4 g = center + vec4(1.0*face_dist,-1.0*face_dist,1.0*face_dist,1.0*face_dist);
	vec4 h = center + vec4(-1.0*face_dist,-1.0*face_dist,1.0*face_dist,1.0*face_dist);
	vec4 i = center + vec4(-1.0*face_dist,-1.0*face_dist,1.0*face_dist,-1.0*face_dist);
	vec4 j = center + vec4(1.0*face_dist,-1.0*face_dist,1.0*face_dist,-1.0*face_dist);
	vec4 k = center + vec4(1.0*face_dist,1.0*face_dist,1.0*face_dist,-1.0*face_dist);
	vec4 l = center + vec4(-1.0*face_dist,1.0*face_dist,1.0*face_dist,-1.0*face_dist);
	vec4 m = center + vec4(-1.0*face_dist,1.0*face_dist,-1.0*face_dist,-1.0*face_dist);
	vec4 n = center + vec4(1.0*face_dist,1.0*face_dist,-1.0*face_dist,-1.0*face_dist);
	vec4 o = center + vec4(1.0*face_dist,-1.0*face_dist,-1.0*face_dist,-1.0*face_dist);
	vec4 p = center + vec4(-1.0*face_dist,-1.0*face_dist,-1.0*face_dist,-1.0*face_dist);


	face(o,p,m,n);
	face(n,m,l,k);
	face(k,l,i,j);
	face(j,i,p,o);
	face(m,p,i,l);
	face(o,j,k,n);

	face(a,b,c,d);
	face(d,c,f,e);
	face(a,d,e,h);
	face(h,e,f,g);
	face(g,f,c,b);
	face(b,a,h,g);

	face(a,p,o,b);
	face(b,o,j,g);
	face(g,j,i,h);
	face(h,i,p,a);

	face(c,n,m,d);
	face(d,m,l,e);
	face(e,l,k,f);
	face(f,k,n,c);

	face(d,m,p,a);
	face(e,l,i,h);
	face(f,k,j,g);
	face(c,n,o,b);

	std::cout << "Setting Tesseract Buffers" << std::endl;

	prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
		vertexCount,pVerts,"vPosition");
	prog->setBuffer(buffers[0],BUFFER_OFFSET(0),GL_FLOAT,
		vertexCount,pVerts,"vNormal");
}
