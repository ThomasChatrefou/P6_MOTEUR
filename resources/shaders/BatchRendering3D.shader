#shader vertex
#version 330 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normals;
layout(location = 3) in vec3 position;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position + vertices, 1.0f);
	v_TexCoord = texCoord;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};