#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;  // Ajout des coordonnées UV

out vec3 fragColor;
out vec2 TexCoord;  // Output vers le fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragColor = color;
    TexCoord = texCoord;  // Passage des coordonnées de texture au fragment shader
    gl_Position = projection * view * model * vec4(position, 1.0);
}