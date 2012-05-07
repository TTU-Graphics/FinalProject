const int nLights = 3;
attribute vec4 vPosition;
//attribute vec4 vNormal;
attribute vec2 vTexture;

// output values that will be interpretated per-fragment
//varying vec3 fN;
varying vec3 fE;
varying vec3 fL[nLights];

struct LightInfo {
  vec4 Position, Direction;
  float Angle;
  //product of material and light properties
  vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
};
uniform LightInfo lights[nLights];

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat3 NormalMatrix;
uniform mat4 WorldMatrix;

varying vec2 vTex;

void main()
{
//  fN = normalize(NormalMatrix * vNormal.xyz);
  fE = (ModelView*vPosition).xyz;

  for(int i=0; i<nLights; i++) {
    if( lights[i].Position.w != 0.0 ) {
      fL[i] = (lights[i].Position).xyz - fE;
    } else {
      fL[i] = (lights[i].Position).xyz;
    }
    fL[i] = normalize(fL[i]);
  }
  
  fE = normalize(fE);

  vTex = vTexture;
  gl_Position = Projection*WorldMatrix*ModelView*vPosition;
}
