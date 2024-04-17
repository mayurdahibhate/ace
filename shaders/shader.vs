#version 460 core 

in vec4 aPosition; 
in vec4 aColor; 

uniform mat4 uMVPMatrix;

out vec4 oColor; 

void main(void) 
{ 
    gl_Position = uMVPMatrix * aPosition; 
    oColor = aColor; 
}
