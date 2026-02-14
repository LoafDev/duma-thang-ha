#include <systems/engine.hpp>

namespace niqqa
{
namespace systems
{
bool Engine::init(uint32_t width, uint32_t height, const std::string &title, bool resizable, bool fullscreen) noexcept
{
    if (!m_window.init(width, height, title, resizable, fullscreen))
    {
        return false;
    }


    return true;
}
} // namespace systems
} // namespace niqqa