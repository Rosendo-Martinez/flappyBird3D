#ifndef SHADER
#define SHADER

class Shader
{
public:
    unsigned int ID;

    Shader();
    void compile(const char* vsPath, const char* fsPath);
    void use();
};

#endif