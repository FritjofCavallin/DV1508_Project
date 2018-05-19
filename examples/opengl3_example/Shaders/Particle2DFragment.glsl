#version 400

in vec2 Vertex_UV;
out vec4 FragColor;

uniform sampler2D textures0;
uniform sampler2D textures1;
uniform sampler2D textures2;
uniform sampler2D textures3;

uniform vec4 Color;
uniform in vec4 Tex_Blend;
uniform in uvec4 Tex_Area;
uniform vec4 Area[8];

//uniform sampler2D tex0;

/* Transform uv to local tex zone
*/
vec2 areaTrans(vec2 uv, uint i)
{
  return Area[i].xy + uv * Area[i].zw;
}

void main (void)
{
  vec2 uv = Vertex_UV.xy;
  uv.y *= -1.0;

  /* Texture blending:
  */
  vec4 colOut = Color;
  colOut *= mix(vec4(1.f),texture(textures0, areaTrans(uv, Tex_Area.x)).rgba, Tex_Blend.x);
  colOut *= mix(vec4(1.f),texture(textures1, areaTrans(uv, Tex_Area.y)).rgba, Tex_Blend.y);
  colOut *= mix(vec4(1.f),texture(textures2, areaTrans(uv, Tex_Area.z)).rgba, Tex_Blend.z);
  colOut *= mix(vec4(1.f),texture(textures3, areaTrans(uv, Tex_Area.w)).rgba, Tex_Blend.w);
  FragColor = colOut;
}
