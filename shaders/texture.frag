#version 460 core

in vec2 oTexCoord;

uniform sampler2D uTextureSampler;

out vec4 FragColor;

void main(void)
{
    FragColor = texture(uTextureSampler, oTexCoord);
}
