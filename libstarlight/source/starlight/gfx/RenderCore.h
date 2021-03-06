#pragma once
#include "starlight/_global.h"

#include <memory>
#include <3ds.h>
#include <citro3d.h>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"
#include "starlight/datatypes/Color.h"

#include "starlight/gfx/Enums.h"

#include "starlight/util/WorkerThread.h"

namespace starlight {
    namespace gfx {
        class RenderCore;
        class CTexture {
        protected:
            CTexture() = default;
            
        public:
            Vector2 size;
            Vector2 txSize;
            
            virtual ~CTexture() = default;
            virtual void Bind(Color color = Color::white, BlendMode mode = BlendMode::Normal) = 0;
        };
        
        class CRenderTarget : public CTexture {
            friend class starlight::gfx::RenderCore;
        protected:
            C3D_RenderTarget* tgt;
            C3D_Tex tex;
            Color clearColor = Color::transparent;
            bool firstClearDone = false;
            
        public:
            C3D_Mtx projection;
            
            CRenderTarget(int width, int height, bool forceExact = false);
            ~CRenderTarget();
            
            void Clear(Color color);
            void BindTarget();
            
            void Bind(Color color = Color::white, BlendMode mode = BlendMode::Normal) override;
        };
        
        class RenderCore {
        public:
            //static util::WorkerThread loadingThread;
            
            static std::unique_ptr<CRenderTarget> targetTopLeft;
            static std::unique_ptr<CRenderTarget> targetTopRight;
            static std::unique_ptr<CRenderTarget> targetBottom;
            
            RenderCore() = delete; // static
            
            static void Open();
            static void Close();
            
            static void SyncFrame();
            static void BeginFrame();
            static void EndFrame();
            
            static void BindTexture(C3D_Tex* tex, const Color& color, BlendMode mode = BlendMode::Normal);
            static void BindColor(const Color& color, BlendMode mode = BlendMode::Normal);
            static void DrawQuad(const VRect& rect, const VRect& src, bool noSnap = false);
            static void DrawQuad(const VRect& rect, const Vector2& anchor, float angle, const VRect& src);
            
            static CTexture* LoadTexture(void* src, int width, int height);
        };
    }
}
