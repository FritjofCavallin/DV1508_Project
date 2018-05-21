#version 400
in vec3 Position;
in vec2 UV;

uniform float Rotation;
uniform vec2 Size;
uniform vec2 SizeMax;

out vec2 Vertex_UV;


vec2 rotate(in float theta, in vec2 v)
{
  float cs = cos(theta);
  float sn = sin(theta);

  vec2 ret;
  ret.x = v.x * cs - v.y * sn;
  ret.y = v.x * sn + v.y * cs;
  return ret;
}

void main()
{
  vec2 p = (Position.xy) * (Size/SizeMax);
  gl_Position = vec4(rotate(Rotation, p), Position.z, 1.f);
  Vertex_UV = UV;
}
