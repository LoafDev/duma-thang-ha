#include "test1.hpp"

namespace niqqa
{
namespace app
{
bool Test1::init(uint32_t width, uint32_t height, const std::string &title, bool resizable, bool fullscreen) noexcept
{
    if (!m_instance.init())
    {
        return false;
    }

    return true;
}

void Test1::run() noexcept
{
}
} // namespace app
} // namespace niqqa