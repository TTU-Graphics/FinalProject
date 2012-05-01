#version 150

in vec4 vPosition;
in vec4 vNormal;

out vec3 N;
out vec3 L1;
out vec3 E;
out vec3 L2;
out vec3 L3;
out vec3 L4;

out float dist1;
out float dist2;
out float dist3;
out float dist4;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition1;
uniform vec4 LightPosition2;
uniform vec4 LightPosition3;
uniform vec4 LightPosition4;

void main() 
{
  gl_Position = Projection * ModelView * vPosition;
  vec3 pos = (ModelView * vPosition).xyz;

  dist1 = length(LightPosition1-vec4(pos,0.0));
  dist2 = length(LightPosition2-vec4(pos,0.0));
  dist3 = length(LightPosition3-vec4(pos,0.0));
  dist4 = length(LightPosition4-vec4(pos,0.0));

  N = normalize(ModelView*vec4(vNormal.xyz,0.0)).xyz;
  L1 = normalize(LightPosition1.xyz - pos);
  L2 = normalize(LightPosition2.xyz - pos);
  L3 = normalize(LightPosition3.xyz - pos);
  L4 = normalize(LightPosition4.xyz - pos);
  if (LightPosition1.w == 0.0) L1 = LightPosition1.xyz;
  if (LightPosition2.w == 0.0) L2 = LightPosition2.xyz;
  if (LightPosition3.w == 0.0) L3 = LightPosition3.xyz;
  if (LightPosition4.w == 0.0) L4 = LightPosition4.xyz;
  E = normalize(-pos);
} 
