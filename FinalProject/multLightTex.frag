uniform sampler2D Texture;
uniform sampler2D NormalMap;
varying vec2 vTex;

// per-fragment interpolated values from the vertex shader
varying  vec3 fN;
varying  vec3 fT;
varying  vec3 fB;
varying  vec3 fL[nLights];
varying  vec3 fE;

uniform float Shininess;


struct LightInfo {
  vec4 Position;
  //product of material and light properties
  vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
};
uniform LightInfo lights[nLights];

void main() 
{ 
  // Normalize the input lighting vectors
  vec3 N = normalize(fN);
  vec3 T = normalize(fT);
  vec3 B = normalize(fB);
  vec3 E = -normalize(fE);
  //vec3 L = normalize(fL);
  vec3 L[nLights];
  
  // Setup transform to tangentspace
  mat3 TBN = mat3(T,B,N);
  E = TBN * E;
  N = normalize(texture2D( NormalMap, vTex ).rgb*2.0 - 1.0);

  vec4 ambient = vec4(0,0,0,0),
    diffuse = vec4(0,0,0,0),
    specular = vec4(0,0,0,0);
  float Kd, Ks;
  for(int i=0; i<nLights; i++) {
    ambient += lights[i].AmbientProduct;

    // Bring L into tangent space
    L[i] = TBN*normalize(fL[i]);

    vec3 H = normalize(L[i] + E);

    Kd = max(dot(L[i], N), 0.0);
    diffuse += Kd*lights[i].DiffuseProduct;

    Ks = pow(max(dot(N, H), 0.0), Shininess);
    if(dot(L[i], N) >= 0.0) {
      specular += Ks*lights[i].SpecularProduct;
    }
  }

  gl_FragColor = ambient + diffuse + specular;
  gl_FragColor.a = 1.0;
  gl_FragColor *= texture2D(Texture, vTex);
} 

