/*For now only point of this class is to:
    1) compile and link shader program
    2) make the ID of shader aviable aferwards
*/
class Shader
{
public:
    unsigned int ID;

    Shader();
    void compile(const char* vsPath, const char* fsPath);
};