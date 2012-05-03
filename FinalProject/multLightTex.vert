attribute vec4 vPosition;
attribute vec4 vNormal;
attribute vec3 vTangent;
attribute vec3 vBitangent;
attribute vec2 vTexture;

// output values that will be interpretated per-fragment
varying vec3 fN;
varying vec3 fT;
varying vec3 fB;
varying vec3 fE;
varying vec3 fL[nLights];

struct LightInfo {
  vec4 Position;
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
  fN = NormalMatrix * vNormal.xyz;
  fT = NormalMatrix * vTangent.xyz;
  fB = NormalMatrix * vBitangent.xyz;
  fE = (ModelView*vPosition).xyz;

  for(int i=0; i<nLights; i++) {
    if( lights[i].Position.w != 0.0 ) {
      fL[i] = (lights[i].Position).xyz - fE;
    } else {
      fL[i] = (lights[i].Position).xyz;
    }
  }

  vTex = vTexture;
  gl_Position = Projection*WorldMatrix*ModelView*vPosition;
}
