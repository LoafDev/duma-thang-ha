#include <systems/renderers/renderer.hpp>

namespace niqqa 
{
namespace systems
{
bool BaseRenderer::init(VkDevice device) noexcept
{
    m_device = device;

    return true;
}
} // namespace systems
} // namespace niqqa