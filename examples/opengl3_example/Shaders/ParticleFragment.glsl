#version 400

uniform sampler2D textures0;
uniform sampler2D textures1;
uniform sampler2D textures2;
uniform sampler2D textures3;

uniform vec4 area[8];

//uniform sampler2D tex0;
in vec2 Vertex_UV;
flat in vec4 Vertex_Color;
flat in vec4 Tex_Blend;
flat in uvec4 Tex_Area;
out vec4 FragColor;

/* Transform uv to local tex zone
*/
vec2 areaTrans(vec2 uv, uint i)
{
  return area[i].xy + uv * area[i].zw;
}

void main (void)
{
  vec2 uv = Vertex_UV.xy;


  uv.y *= -1.0;

  /* Texture blending:
  */
  vec4 colOut = Vertex_Color;
  colOut *= mix(vec4(1.f),texture(textures0, areaTrans(uv, Tex_Area.x)).rgba, Tex_Blend.x);
  colOut *= mix(vec4(1.f),texture(textures1, areaTrans(uv, Tex_Area.y)).rgba, Tex_Blend.y);
  colOut *= mix(vec4(1.f),texture(textures2, areaTrans(uv, Tex_Area.z)).rgba, Tex_Blend.z);
  colOut *= mix(vec4(1.f),texture(textures3, areaTrans(uv, Tex_Area.w)).rgba, Tex_Blend.w);
  FragColor = colOut;
}
