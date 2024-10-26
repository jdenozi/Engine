#version 330 core

out vec4 FragColor;

uniform float time;

void main()
{
    float r = 0.5 + 0.5 * sin(time);
    float g = 0.5 + 0.5 * sin(time + 2.094);
    float b = 0.5 + 0.5 * sin(time + 4.189);

    FragColor = vec4(r, g, b, 1.0);
}