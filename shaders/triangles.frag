	#version 460 core
	
	in vec4 oColor;
	
    out vec4 FragColor;
	
    void main(void)
	{
	    // FragColor = oColor;
		FragColor = vec4(1.0f, 0.2f, 0.3f, 1.0f);
	}