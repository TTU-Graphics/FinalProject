#version 150
uniform vec4 AmbientProduct1, DiffuseProduct1, SpecularProduct1;
uniform vec4 AmbientProduct2, DiffuseProduct2, SpecularProduct2;
uniform vec4 AmbientProduct3, DiffuseProduct3, SpecularProduct3;
uniform vec4 AmbientProduct4, DiffuseProduct4, SpecularProduct4;
uniform float AttConstant1, AttLinear1, AttQuad1;
uniform float AttConstant2, AttLinear2, AttQuad2;
uniform float AttConstant3, AttLinear3, AttQuad3;
uniform float AttConstant4, AttLinear4, AttQuad4;
uniform vec4 Emission;
uniform mat4 modelView;
uniform vec4 LightPosition1;
uniform vec4 LightPosition2;
uniform vec4 LightPosition3;
uniform vec4 LightPosition4;
uniform float Shininess;

in vec3 N;
in vec3 L1;
in vec3 L2;
in vec3 L3;
in vec3 L4;
in vec3 E;

in float dist1;
in float dist2;
in float dist3;
in float dist4;

void main() 
{ 
  float att1 = 1.0 / (AttConstant1 + AttLinear1*dist1 +AttQuad1*dist1*dist1);
  float att2 = 1.0 / (AttConstant2 + AttLinear2*dist2 +AttQuad2*dist2*dist2);
  float att3 = 1.0 / (AttConstant3 + AttLinear3*dist3 +AttQuad3*dist3*dist3);
  float att4 = 1.0 / (AttConstant4 + AttLinear4*dist4 +AttQuad4*dist4*dist4);

  vec3 NN = normalize(N);
  vec3 EE = normalize(E);
  vec3 LL1 = normalize(L1);
  vec3 LL2 = normalize(L2);
  vec3 LL3 = normalize(L3);
  vec3 LL4 = normalize(L4);

  vec4 ambient1, diffuse1, specular1;
  vec4 ambient2, diffuse2, specular2;
  vec4 ambient3, diffuse3, specular3;
  vec4 ambient4, diffuse4, specular4;
  vec3 H1 = normalize(LL1+EE);
  vec3 H2 = normalize(LL2+EE);
  vec3 H3 = normalize(LL3+EE);
  vec3 H4 = normalize(LL4+EE);

  float Kd1 = max(dot(LL1,NN),0.0);
  float Kd2 = max(dot(LL2,NN),0.0);
  float Kd3 = max(dot(LL3,NN),0.0);
  float Kd4 = max(dot(LL4,NN),0.0);

  float Ks1 = pow(max(dot(NN,H1),0.0),Shininess);
  float Ks2 = pow(max(dot(NN,H2),0.0),Shininess);
  float Ks3 = pow(max(dot(NN,H3),0.0),Shininess);
  float Ks4 = pow(max(dot(NN,H4),0.0),Shininess);

  ambient1 = AmbientProduct1+Emission;
  diffuse1 = Kd1*(DiffuseProduct1);
  ambient1 = ambient1*att1; diffuse1 = diffuse1*att1;
  ambient2 = AmbientProduct2+Emission;
  diffuse2 = Kd2*(DiffuseProduct2);
  ambient2 = ambient2*att2; diffuse2 = diffuse2*att2;
  ambient3 = AmbientProduct3+Emission;
  diffuse3 = Kd3*(DiffuseProduct3);
  ambient3 = ambient3*att3; diffuse3 = diffuse3*att3;
  ambient4 = AmbientProduct4+Emission;
  diffuse4 = Kd4*(DiffuseProduct4);
  ambient4 = ambient4*att4; diffuse4 = diffuse4*att4;

  if(dot(LL1,NN) < 0.0) specular1 = vec4(0.0,0.0,0.0,1.0);
  else specular1 = Ks1*(SpecularProduct1);
  specular1 = specular1*att1;
  if(dot(LL2,NN) < 0.0) specular2 = vec4(0.0,0.0,0.0,1.0);
  else specular2 = Ks2*(SpecularProduct2);
  specular2 = specular2*att2;
  if(dot(LL3,NN) < 0.0) specular3 = vec4(0.0,0.0,0.0,1.0);
  else specular3 = Ks3*(SpecularProduct3);
  specular3 = specular3*att3;
  if(dot(LL4,NN) < 0.0) specular4 = vec4(0.0,0.0,0.0,1.0);
  else specular4 = Ks1*(SpecularProduct4);
  specular4 = specular4*att4;

  vec4 ambient = ambient1 + ambient2 + ambient3 + ambient4;
  vec4 diffuse = diffuse1 + diffuse2 + diffuse3 + diffuse4;
  vec4 specular = specular1 + specular2 + specular3 + specular4;

  gl_FragColor = vec4((ambient + diffuse + specular).xyz,1.0);
} 
