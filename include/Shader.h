#ifndef SHADER_H
#define SHADER_H

#include "VulkanAppBase.h"
#include <fstream>
#include <string>
#include <vector>

/**
 * @brief read bytes from file and return a vector of bytes
 * @param filename path to file
 * @return vector of bytes
 */
std::string readFile(const std::string& filename);

class Shader{
private:
  std::string shaderFilepath;
  std::vector<char> shaderByteCode;
  GLuint type = GL_SHADER;  // type of shader module

public:
  Shader() = default;
  ~Shader() = delete;

  /**
   * @brief create a Shader object and optionally compile it to bytecode,
   *    compiled bytecode will be stored in shaderByteCode.
   * @param shaderTy
   * @param shaderSrc
   * @param compileSrc
   */
   Shader(GLuint shaderTy, const char* shaderSrc, bool compileSrc = true)
      : type(shaderTy), shaderFilepath(shaderSrc){
    if (compileSrc) compile();
  }

  /**
   * @brief returns bytecode, if shader source code was not yet compiled, it
   *    will be done so.
   * @return shader bytecode as a vector of bytes
   */
  std::vector<char> getShaderByteCode();

  /**
   * @brief construct and return a Vulkan Shader module from the
   *    preserved shader code.
   * @param device
   * @param pAllocator
   * @return
   */
  VkShaderModule getShaderModule(VkDevice& device, const VkAllocationCallbacks* pAllocator);
private:

  void compile();

};


#endif /* SHADER_H */