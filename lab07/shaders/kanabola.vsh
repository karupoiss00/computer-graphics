float calculateCanabolaK(float x)
{
    return (1 + sin(x)) * (1 + 0.9 * cos(8 * x)) * (1 + 0.1 * cos(24 * x)) * (0.5 + 0.3 * cos(140 * x));
}

vec4 firstColor = vec4(0.2, 0.6, 0.3, 1.0);
vec4 secondColor = vec4(0, 1.0, 0.25, 1.0);

void main()
{
   vec4 pos = gl_Vertex;
   float canabolaK = calculateCanabolaK(pos.x);
 
   pos.y = canabolaK * sin(pos.x);
   pos.x = canabolaK * cos(pos.x);
 
   gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * pos;
   gl_FrontColor = mix(firstColor, secondColor, mod(pos.y, 0.1) * 10.0);
}