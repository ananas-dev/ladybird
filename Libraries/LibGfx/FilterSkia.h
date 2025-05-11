/*
 * Copyright (c) 2024, Lucien Fiorini <lucienfiorini@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGfx/Filter.h>
#include <effects/SkImageFilters.h>

namespace Gfx {

class FilterImplSkia final : public FilterImpl {
public:
    FilterImplSkia() = default;
    explicit FilterImplSkia(sk_sp<SkImageFilter> filter);

    static NonnullOwnPtr<FilterImplSkia> create(sk_sp<SkImageFilter> filter);

    void compose(FilterImpl const& other) override;

    NonnullOwnPtr<FilterImpl> create_blur(float radius, Optional<FilterImpl const&> input) override;
    NonnullOwnPtr<FilterImpl> create_drop_shadow(float offset_x, float offset_y, float radius, Gfx::Color color, Optional<FilterImpl const&> input) override;
    NonnullOwnPtr<FilterImpl> create_color(ColorFilterType type, float amount, Optional<FilterImpl const&> input) override;
    NonnullOwnPtr<FilterImpl> create_flood(Gfx::Color color, float opacity) override;
    NonnullOwnPtr<FilterImpl> create_blend(FilterImpl const& first, FilterImpl const& second, CompositingAndBlendingOperator mode) override;
    NonnullOwnPtr<FilterImpl> create_color_matrix(float matrix[20], Optional<FilterImpl const&> input) override;
    NonnullOwnPtr<FilterImpl> create_saturate(float value, Optional<FilterImpl const&> input) override;
    NonnullOwnPtr<FilterImpl> create_hue_rotate(float angle_degrees, Optional<FilterImpl const&> input) override;

    NonnullOwnPtr<FilterImpl> clone() const override;

    sk_sp<SkImageFilter> const& sk_filter() const { return m_filter; }

private:
    sk_sp<SkImageFilter> m_filter;
};

}
