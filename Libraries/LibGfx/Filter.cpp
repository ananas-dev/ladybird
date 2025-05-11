//
// Created by lucien on 5/10/25.
//

#include <LibGfx/Filter.h>
#include <LibGfx/FilterSkia.h>

namespace Gfx {

static FilterImplSkia impl_factory;

Filter::Filter(NonnullOwnPtr<FilterImpl> impl)
    : m_impl(move(impl))
{
}

void Filter::compose(Filter const& other)
{
    m_impl->compose(*other.m_impl);
}

Filter Filter::blend(Filter const& first, Filter const& second, CompositingAndBlendingOperator mode)
{
    return Filter(impl_factory.create_blend(*first.m_impl, *second.m_impl, mode));
}

Filter Filter::flood(Gfx::Color color, float opacity)
{
    return Filter(impl_factory.create_flood(color, opacity));
}

Filter Filter::drop_shadow(float offset_x, float offset_y, float radius, Gfx::Color color, Optional<Filter const&> input)
{
    Optional<FilterImpl const&> input_impl;

    if (input.has_value()) {
        input_impl = static_cast<FilterImpl const&>(*input.value().m_impl);
    }

    return Filter(impl_factory.create_drop_shadow(offset_x, offset_y, radius, color, input_impl));
}

Filter Filter::blur(float radius, Optional<Filter const&> input)
{
    Optional<FilterImpl const&> input_impl;

    if (input.has_value()) {
        input_impl = static_cast<FilterImpl const&>(*input.value().m_impl);
    }

    return Filter(impl_factory.create_blur(radius, input_impl));
}

Filter Filter::color(ColorFilterType type, float amount, Optional<Filter const&> input)
{
    Optional<FilterImpl const&> input_impl;

    if (input.has_value()) {
        input_impl = static_cast<FilterImpl const&>(*input.value().m_impl);
    }

    return Filter(impl_factory.create_color(type, amount, input_impl));
}

Filter Filter::color_matrix(float matrix[20], Optional<Filter const&> input)
{
    Optional<FilterImpl const&> input_impl;

    if (input.has_value()) {
        input_impl = static_cast<FilterImpl const&>(*input.value().m_impl);
    }

    return Filter(impl_factory.create_color_matrix(matrix, input_impl));
}

Filter Filter::saturate(float value, Optional<Filter const&> input)
{
    Optional<FilterImpl const&> input_impl;

    if (input.has_value()) {
        input_impl = static_cast<FilterImpl const&>(*input.value().m_impl);
    }

    return Filter(impl_factory.create_saturate(value, input_impl));
}

Filter Filter::hue_rotate(float angle_degrees, Optional<Filter const&> input)
{
    Optional<FilterImpl const&> input_impl;

    if (input.has_value()) {
        input_impl = static_cast<FilterImpl const&>(*input.value().m_impl);
    }

    return Filter(impl_factory.create_hue_rotate(angle_degrees, input_impl));
}

}
