
#include <GL/glew.h>
#include "Shader.h"

/**
 * @brief read bytes from file and return a vector of bytes
 * @param filename path to file
 * @return vector of bytes
 */
std::string readFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file " + filename);
  }

  size_t fileSize = (size_t)file.tellg();
  std::string buffer(fileSize, '_');
  file.seekg(0);
  file.read(buffer.data(), fileSize);
  file.close();
  return buffer;
}

VkShaderModule Shader::getShaderModule(VkDevice &device, const VkAllocationCallbacks *pAllocator) {
  // compile source code if it was not compiled yet
  if (shaderByteCode.empty()) compile();

  // setup createInfo struct object
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = shaderByteCode.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderByteCode.data());

  // finally, create the module and return it with a runtime error check
  VkShaderModule mod;
  if (vkCreateShaderModule(device, &createInfo, pAllocator, &mod) != VK_SUCCESS)
    throw std::runtime_error("Failed to create shader module!");
  return mod;
}
std::vector<char> Shader::getShaderByteCode() {
  if (shaderByteCode.empty())
    compile();
  return shaderByteCode;
}

/**
 * @brief compile GLSL file specified by shaderFilepath into SPIR-V bytecode which is stored in
 *  shaderByteCode as a vector of bytes
 */
void Shader::compile() {
  GLuint shader = glCreateShader(type);
  if (shader == 0)
    throw std::runtime_error("Failed to create shader!");
  auto shaderCode = readFile(shaderFilepath);
  const GLchar* codeArray[] = {shaderCode.c_str()};
  glShaderSource(shader, 1, codeArray, nullptr);
  glCompileShader(shader);

  GLint result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result );
  if( GL_FALSE == result ) {
    std::cerr << "Shader compilation failed!" << std::endl;

    // Get and print the info log
    GLint logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
    if( logLen > 0 ) {
      std::string log(logLen, ' ');
      GLsizei written;
      glGetShaderInfoLog(shader, logLen, &written, &log[0]);
      std::cerr << "Shader log: " << std::endl << log;
    }
  }
}



