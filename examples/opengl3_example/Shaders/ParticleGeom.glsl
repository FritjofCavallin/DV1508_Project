#version 400

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

// GLSL Hacker automatic uniforms:
uniform mat4 projMat;

in Vertex
{
  vec4 color;
  vec2 size;
  float rot;
  vec4 texBlend;
  ivec4 texArea;
} vertex[];


out vec2 Vertex_UV;
flat out vec4 Vertex_Color;
flat out vec4 Tex_Blend;
flat out ivec4 Tex_Area;

vec2 rotate(in float theta, in vec2 v)
{
  float cs = cos(theta);
  float sn = sin(theta);

  vec2 ret;
  ret.x = v.x * cs - v.y * sn;
  ret.y = v.x * sn + v.y * cs;
  return ret;
}

void main (void)
{
  vec4 P = gl_in[0].gl_Position;

  // a: left-bottom
  vec2 va = P.xy + rotate(vertex[0].rot, vec2(-0.5, -0.5)) *vertex[0].size;
  //va.xy = va.xy*0.1 + vec2(-1, -1);
  gl_Position = projMat * vec4(va, P.zw);
  Vertex_UV = vec2(0.0, 0.0);
  Vertex_Color = vertex[0].color;
  Tex_Blend = vertex[0].texBlend;
  Tex_Area = vertex[0].texArea;
  EmitVertex();

  // b: left-top
  vec2 vb = P.xy + rotate(vertex[0].rot, vec2(-0.5, 0.5)) * vertex[0].size;
  gl_Position = projMat * vec4(vb, P.zw);
  Vertex_UV = vec2(0.0, 1.0);
  Vertex_Color = vertex[0].color;
  Tex_Blend = vertex[0].texBlend;
  Tex_Area = vertex[0].texArea;
  EmitVertex();

  // d: right-bottom
  vec2 vd = P.xy + rotate(vertex[0].rot, vec2(0.5, -0.5)) * vertex[0].size;
  gl_Position = projMat * vec4(vd, P.zw);
  Vertex_UV = vec2(1.0, 0.0);
  Vertex_Color = vertex[0].color;
  Tex_Blend = vertex[0].texBlend;
  Tex_Area = vertex[0].texArea;
  EmitVertex();

  // c: right-top
  vec2 vc = P.xy + rotate(vertex[0].rot, vec2(0.5, 0.5)) *vertex[0].size;
  gl_Position = projMat * vec4(vc, P.zw);
  Vertex_UV = vec2(1.0, 1.0);
  Vertex_Color = vertex[0].color;
  Tex_Blend = vertex[0].texBlend;
  Tex_Area = vertex[0].texArea;
  EmitVertex();

  EndPrimitive();
}
