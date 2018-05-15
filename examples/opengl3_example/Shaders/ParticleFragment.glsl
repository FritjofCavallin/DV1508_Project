#version 400

uniform sampler2D textures0;
uniform sampler2D textures1;
uniform sampler2D textures2;
uniform sampler2D textures3;

//uniform sampler2D tex0;
in vec2 Vertex_UV;
in vec4 Vertex_Color;
in vec4 Tex_Blend;
out vec4 FragColor;

void main (void)
{
  vec2 uv = Vertex_UV.xy;
  uv.y *= -1.0;

  /* Texture blending:
  */
  vec4 colOut = Vertex_Color;
  colOut *= mix(vec4(1.f),texture(textures0, uv).rgba, Tex_Blend.x);
  colOut += 0.001f*mix(vec4(1.f),texture(textures1, uv).rgba, 0.001f * Tex_Blend.y);
  colOut += 0.001f*mix(vec4(1.f),texture(textures2, uv).rgba, 0.001f *  Tex_Blend.z);
  colOut += 0.001f*mix(vec4(1.f),texture(textures3, uv).rgba, 0.001f * Tex_Blend.w);

  FragColor = colOut;
}
