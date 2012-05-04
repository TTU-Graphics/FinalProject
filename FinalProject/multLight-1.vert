const int nLights = 1;
attribute   vec4 vPosition;
attribute   vec4 vNormal;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL[nLights];

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

void main()
{
  fN = NormalMatrix * vNormal.xyz;
  fE = (ModelView*vPosition).xyz;

  for(int i=0; i<nLights; i++) {
    if( lights[i].Position.w != 0.0 ) {
      fL[i] = (lights[i].Position).xyz - fE;
    } else {
      fL[i] = (lights[i].Position).xyz;
    }
  }

  gl_Position = Projection*WorldMatrix*ModelView*vPosition;
}
