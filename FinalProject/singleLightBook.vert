attribute   vec4 vPosition;
attribute   vec4 vNormal;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;

uniform mat4 modelView;
uniform vec4 LightPosition;
uniform mat4 projection;
uniform mat3 NormalMatrix;
uniform mat4 WorldView;

void main()
{
  fN = NormalMatrix * vNormal.xyz;
  fE = (modelView*vPosition).xyz;
  fL = (LightPosition).xyz;

  if( LightPosition.w != 0.0 ) {
    fL = (LightPosition).xyz - fE;
  }

  gl_Position = projection*modelView*vPosition;
}
