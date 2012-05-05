const int nLights = 2;
attribute   vec4 vPosition;
attribute   vec4 vNormal;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL[nLights];
varying  vec4 color;

struct LightInfo {
  vec4 Position, Direction;
  float Angle;
  //product of material and light properties
  vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
};
uniform LightInfo lights[nLights];

uniform mat4 ModelView;
//uniform vec4 LightPosition;
uniform mat4 Projection;
uniform mat3 NormalMatrix;
uniform mat4 WorldMatrix;

uniform float Theta;

void main()
{
//  fN = NormalMatrix * vNormal.xyz;
//  fE = (ModelView*vPosition).xyz;

//  for(int i=0; i<nLights; i++) {
//    if( lights[i].Position.w != 0.0 ) {
//      fL[i] = (lights[i].Position).xyz - fE;
//    } else {
//      fL[i] = (lights[i].Position).xyz;
//    }
//  }

	float sines[6], cosines[6];
	for( int i=0; i<6; i++ )
	{
		sines[i] = sin(float(i)*Theta);
		cosines[i] = cos(float(i)*Theta);
	}


	mat4 rotation = mat4( cosines[0],	sines[0],		0.0,	0.0,
						  -sines[0],	cosines[0],		0.0,	0.0,
						  0.0,			0.0,			1.0,	0.0,
						  0.0,			0.0,			0.0,	1.0 );
						  
	// YZ
	rotation = mat4( 1.0,			0.0,			0.0,		0.0,
					 0.0,			cosines[1],		sines[1],	0.0,
					 0.0,			-sines[1],		cosines[1],	0.0,
					 0.0,			0.0,			0.0,		1.0 ) * rotation;
	
	// XZ
	rotation = mat4( cosines[2],	0.0,	-sines[2],	0.0,
					 0.0,			1.0,	0.0,		0.0,
					 sines[2],		0.0,	cosines[2],	0.0,
					 0.0,			0.0,	0.0,		1.0 ) * rotation;
	
	// XW
	rotation = mat4( cosines[3],	0.0,	0.0,	sines[3],
					 0.0,			1.0,	0.0,	0.0,
					 0.0,			0.0,	1.0,	0.0,
					 -sines[3],		0.0,	0.0,	cosines[3]) * rotation;
	
	// YW
	rotation = mat4( 1.0,			0.0,			0.0,	0.0,
					 0.0,			cosines[4],		0.0,	-sines[4],
					 0.0,			0.0,			1.0,	0.0,
					 0.0,			sines[4],		0.0,	cosines[4] ) * rotation;
	
	// ZW
	rotation = mat4( 1.0,	0.0,	0.0,			0.0,
					 0.0,	1.0,	0.0,			0.0,
					 0.0,	0.0,	cosines[5],		-sines[5],
					 0.0,	0.0,	sines[5],		cosines[5] ) * rotation;
	

  //gl_Position = Projection*WorldMatrix*ModelView*vPosition;

  // Perspective projection of hypercube into 3D space
  vec4 temp = rotation*vPosition;
  temp.w = temp.w + 1.0;
  temp.xyz = temp.xyz * temp.w;
  temp.w = 1.0;

  
  // Bring hypercube into eye coordinates
  gl_Position = Projection*ModelView*WorldMatrix*temp;
  color = vNormal;
}
