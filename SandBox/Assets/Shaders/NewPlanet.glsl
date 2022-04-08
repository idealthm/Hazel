#type vertex
#version 330

layout (location = 0) vec3 a_Position;


out vec3 Normal;

void main()
{
	Normal = a_Position;
	gl_Position = a_Position;
}

#type fragment
#version 330

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * light;
	vec3 result = ambient * objectColor;
	FragColor = vec4(result, 1.0);
}