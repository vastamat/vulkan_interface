#pragma once

namespace vui
{
    class Graphics
    {
    public:
        Graphics();
        ~Graphics();

        Graphics(const Graphics &other) = delete;
        Graphics(Graphics &&other) noexcept = delete;

        Graphics &operator=(const Graphics &other) = delete;
        Graphics &operator=(Graphics &&other) noexcept = delete;

    private:
    };
} // namespace vui
