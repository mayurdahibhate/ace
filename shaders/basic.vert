#version 460 core 

in vec4 aPosition; 

uniform mat4 uMVPMatrix;

out vec4 oColor; 

void main(void) 
{ 
    gl_Position = uMVPMatrix * aPosition; 
}
