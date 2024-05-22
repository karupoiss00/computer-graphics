attribute vec3 endPosition;

uniform float phase;

vec3 mobiusStripFn(vec4 originPoint)
{
	vec3 resultPoint;
	originPoint.x = originPoint.x * 2.0 - 1;
	originPoint.y = originPoint.y * 2.0 * 3.14159;

	resultPoint.x = cos(originPoint.y) * (2 + (originPoint.x / 2) * cos(originPoint.y / 2));
	resultPoint.y = sin(originPoint.y) * (2 + (originPoint.x / 2) * cos(originPoint.y / 2));
	resultPoint.z = (originPoint.x / 2) * sin(originPoint.y / 2);
	
	return resultPoint;
}

vec3 kleinBottleFn(vec4 originPoint)
{
	vec3 resultPoint;
	originPoint.x = originPoint.x * 2.0 * 3.14159;
	originPoint.y = originPoint.y * 2.0 * 3.14159;

	resultPoint.x = (2.0 / 15.0) * (3.0 + cos(originPoint.x)) * cos(originPoint.x) * (1.0 + sin(originPoint.x)) + 2.0 * (1.0 - cos(originPoint.x) / 2.0) * cos(originPoint.y);
	resultPoint.y = -(2.0 / 15.0) * (3.0 + cos(originPoint.x)) * sin(originPoint.x) * (1.0 + sin(originPoint.x)) + 2.0 * (1.0 - cos(originPoint.x) / 2.0) * sin(originPoint.y);
	resultPoint.z = (2.0 / 15.0) * cos(originPoint.x / 2.0) * (1.0 + sin(originPoint.x)) + ((sqrt(2.0) / 2.0) + (1.0 / sqrt(2.0)) * cos(originPoint.y)) * sin(originPoint.x / 2.0);

	return resultPoint;
}

void main()
{
	vec4 mobiusPoint = vec4(mobiusStripFn(gl_Vertex), 1.0);
	vec4 kleinPoint = vec4(kleinBottleFn(gl_Vertex), 1.0);
	vec4 vertex = mix(mobiusPoint, kleinPoint, phase);

	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	gl_FrontColor = gl_Color;
}