attribute   vec4 vPosition;
attribute   vec4 vNormal;

// output values that will be interpretated per-fragment
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;

varying float dist;

uniform mat4 modelView;
uniform vec4 LightPosition;
uniform mat4 projection;

uniform mat4 WorldPosition, WorldRotation, NormalMatrix;

void main()
{
  //fN = (modelView*vec4(vNormal.x,vNormal.y,vNormal.z,1.0)).xyz;
  fN = (NormalMatrix*vNormal).xyz;
  //fE = (modelView*vPosition).xyz;
  //fE = vPosition.xyz;
  fE = normalize(-(modelView*vPosition).xyz);

  /*if( LightPosition.w != 0.0 ) {
    fL = (modelView * LightPosition).xyz - fE;
  } else {
    fL = (modelView * LightPosition).xyz;
  }*/
  fL = LightPosition.xyz;

  dist = length(fL - fE);

  gl_Position = projection*modelView*vPosition;
}
