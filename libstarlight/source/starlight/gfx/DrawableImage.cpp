#include <cstdio>
#include <cmath>

#include "starlight/datatypes/Color.h"
#include "starlight/GFXManager.h"

#include "DrawableImage.h"

using starlight::Vector2;
using starlight::VRect;
using starlight::Color;
using starlight::GFXManager;
using starlight::gfx::DrawableImage;

using starlight::gfx::RenderCore;
using starlight::gfx::CRenderTarget;

void DrawableImage::Draw(const Vector2& position, const Vector2& origin, OptRef<VRect> sampleRect, OptRef<Color> color, float rotation, const Vector2& scale, BlendMode mode) {
    if (GFXManager::PrepareForDrawing()) {
        texture->Bind(color ? color.get() : Color(1,1,1,1), mode);
        const VRect& sr = sampleRect ? sampleRect.get() : VRect(Vector2::zero, texture->size);
        VRect rect(position - (texture->size * origin) * scale, sr.size * scale);
        RenderCore::DrawQuad(rect, position, rotation, sr / texture->txSize);
    }
}

void DrawableImage::Draw(const VRect& rect, OptRef<VRect> sampleRect, OptRef<Color> color, BlendMode mode) {
    if (GFXManager::PrepareForDrawing()) {
        texture->Bind(color ? color.get() : Color(1,1,1,1), mode);
        const VRect& sr = sampleRect ? sampleRect.get() : VRect(Vector2::zero, texture->size);
        RenderCore::DrawQuad(rect, sr / texture->txSize);
    }
}

Vector2 DrawableImage::Size() {
    return texture->size;
}
