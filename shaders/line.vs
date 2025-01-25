#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

// line
uniform vec3 start;
uniform vec3 end;

void main()
{
    if (aPos.x == 0.0)  
    {
        gl_Position = projection * view * vec4(start,1.0);
    }
    else // aPos.x = 1.0
    {
        gl_Position = projection * view * vec4(end,1.0);
    }
};