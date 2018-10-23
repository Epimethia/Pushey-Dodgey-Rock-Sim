
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float fOpacity; // alpha value for fade out

void main()
{ 
	// distance from center of image, used to adjust blur
	//vec2 uv = fragCoord.xy / iResolution.xy;
	float d = length(TexCoords - vec2(0.5,0.5));	

	// final color
    vec3 col;
    col.r = texture(screenTexture, vec2(TexCoords.x,TexCoords.y)).r;
    col.g = texture(screenTexture, TexCoords).g;
    col.b = texture(screenTexture, vec2(TexCoords.x,TexCoords.y)).b;
	
	// scanline
	//float scanline = sin(TexCoords.y*800.0)*0.04;
	//col -= scanline;
	
	// vignette
	col *= 1.0 - d * 0.5;

    FragColor = vec4(col, fOpacity); //texture(screenTexture, TexCoords);
}
