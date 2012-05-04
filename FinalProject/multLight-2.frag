const int nLights = 2;
// per-fragment interpolated values from the vertex shader
varying  vec3 fN;
varying  vec3 fL[nLights];
varying  vec3 fE;

//uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
//uniform mat4 ModelView;
//uniform vec4 LightPosition;
uniform float Shininess;

struct LightInfo {
  vec4 Position, Direction;
  float Angle;
  //product of material and light properties
  vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
};
uniform LightInfo lights[nLights];

void main() 
{
  // Normalize the input lighting vectors
  vec3 N = normalize(fN);
  vec3 E = -normalize(fE);
  //vec3 L = normalize(fL);
  vec3 L[nLights];

  vec4 ambient = vec4(0,0,0,0),
    diffuse = vec4(0,0,0,0),
    specular = vec4(0,0,0,0);
  float Kd, Ks;
  for(int i=0; i<nLights; i++) {
    ambient += lights[i].AmbientProduct;

    L[i] = normalize(fL[i]);

    vec3 H = normalize(L[i] + E);

	if( dot(E-L[i],normalize(lights[i].Direction.xyz)) > cos(lights[i].Angle) )
	{
		Kd = max(dot(L[i], N), 0.0);
		diffuse += Kd*lights[i].DiffuseProduct;

		Ks = pow(max(dot(N, H), 0.0), Shininess);
		if(dot(L[i], N) >= 0.0) {
		  specular += Ks*lights[i].SpecularProduct;
		}
	}
  }

  gl_FragColor = ambient + diffuse + specular;
  gl_FragColor.a = 1.0;
} 

