#include "Shader.h"

/**
 * @brief read bytes from file and return a vector of bytes
 * @param filename path to file
 * @return vector of bytes
 */
static std::vector<char> readFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file " + filename);
  }

  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);
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
void Shader::compile() {
}
