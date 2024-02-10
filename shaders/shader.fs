#version 460 core

out vec4 FragColor;
// in vec3 ourColor;
in vec3 ourPosition;

uniform float time;

void main()
{
   vec3 animatedColor = vec3(0.5 + 0.5 * sin(time), 0.5 + 0.5 * sin(time + 2.0), 0.5 + 0.5 * sin(time + 4.0));
   FragColor = vec4(animatedColor, 1.0);
}