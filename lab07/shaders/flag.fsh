void main()
{
	vec4 pos = gl_TexCoord[0];
	vec4 whiteColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 blueColor = vec4(0.0, 0.0, 1.0, 1.0);
	vec4 redColor = vec4(1.0, 0, 0, 1.0);
	
	if (pos.y < 0.33)
	{
		gl_FragColor = redColor;
	}
	else if (pos.y < 0.66)
	{
		gl_FragColor = blueColor;
	}
	else
	{
		gl_FragColor = whiteColor;
	}
}