#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

// out vec3 Normal;
out vec4 ourColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec4 color;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    if (aNormal == vec3(0.0,0.0,1.0)) // front face
    {
        ourColor = vec4(color.xyz * 0.75, color.w);
    }
    else if (aNormal == vec3(1.0, 0.0, 0.0)) // right face
    {
        ourColor = vec4(color.xyz * 0.5, color.w);
    }
    else if (aNormal == vec3(0.0, -1.0, 0.0)) // bottom face
    {
        ourColor = vec4(color.xyz * 0.25, color.w);
    }
    else
    {
        ourColor = vec4(color.xyz, color.w);
    }
};