uniform sampler2D Texture;
varying vec2 vTex;

void main() {
  vec4 color = texture2D(Texture, vTex);
  gl_FragColor = color;
}
