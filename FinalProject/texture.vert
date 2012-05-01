attribute vec4 vPosition;
attribute vec2 vTexture;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 WorldMatrix;

varying vec2 vTex;

void main() {
  vTex = vTexture;
  gl_Position = Projection*WorldMatrix*ModelView*vPosition;
}
