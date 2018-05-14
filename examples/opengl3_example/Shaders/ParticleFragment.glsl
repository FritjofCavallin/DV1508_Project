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
  if(Tex_Blend.x + Tex_Blend.z > 0.f)
    colOut *= texture(textures0, uv).rgba * Tex_Blend.x + texture(textures2, uv).rgba * Tex_Blend.z;
  if(Tex_Blend.y + Tex_Blend.w > 0.f)
    colOut *= texture(textures1, uv).rgba * Tex_Blend.y + texture(textures3, uv).rgba * Tex_Blend.w;
  //FragColor = vec4(t, 1.0) * Vertex_Color;
  FragColor = colOut;
}
