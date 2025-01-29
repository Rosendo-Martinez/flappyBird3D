#version 330 core
in vec3 Normal;
out vec4 FragColor;

uniform vec3 color;

void main()
{
    if (Normal == vec3(0.0,0.0,1.0)) // front face
    {
        FragColor = vec4(color * 0.75, 1.0f);
    }
    else if (Normal == vec3(1.0, 0.0, 0.0)) // right face
    {
        FragColor = vec4(color * 0.5, 1.0f);
    }
    else if (Normal == vec3(0.0, -1.0, 0.0)) // bottom face
    {
        FragColor = vec4(color * 0.25, 1.0f);
    }
    else
    {
        FragColor = vec4(color, 1.0f);
    }
};