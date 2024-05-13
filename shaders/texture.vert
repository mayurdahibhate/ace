#version 460 core 

in vec4 aPosition; 
in vec2 aTexCoord;

uniform mat4 uMVPMatrix;

out vec2 oTexCoord; 

void main(void) 
{ 
    gl_Position = uMVPMatrix * aPosition; 
    oTexCoord = aTexCoord; 
}
