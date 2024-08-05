#shader vertex

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float a_texIndex;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_texIndex;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   v_TexCoord = texCoord;
   v_Color = a_Color;
   v_texIndex = a_texIndex;
}

#shader framebuff

#version 330 core
layout(location = 0) out vec4 FragColor;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_texIndex;
uniform vec4 u_Color;

uniform sampler2D u_Textures[2];

void main()
{
   int index = int(v_texIndex);
   vec4 texCoord = texture(u_Textures[index], v_TexCoord);
   FragColor = texCoord * v_Color;
}