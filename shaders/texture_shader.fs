#version 460 core

out vec4 FragColor;
in vec3 ourPosition;
in vec2 texCoord;

uniform sampler2D texture1;

void main()
{
   FragColor = texture(texture1, texCoord);
}