class Shader
{
public:
    unsigned int ID;

    Shader();
    void compile(const char* vsPath, const char* fsPath);
};