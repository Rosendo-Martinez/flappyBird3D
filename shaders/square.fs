#version 330 core
in vec3 Normal;
out vec4 FragColor;

uniform vec4 color;

void main()
{
    if (Normal == vec3(0.0,0.0,1.0)) // front face
    {
        FragColor = vec4(color.xyz * 0.75, color.w);
    }
    else if (Normal == vec3(1.0, 0.0, 0.0)) // right face
    {
        FragColor = vec4(color.xyz * 0.5, color.w);
    }
    else if (Normal == vec3(0.0, -1.0, 0.0)) // bottom face
    {
        FragColor = vec4(color.xyz * 0.25, color.w);
    }
    else
    {
        FragColor = vec4(color.xyz, color.w);
    }
};