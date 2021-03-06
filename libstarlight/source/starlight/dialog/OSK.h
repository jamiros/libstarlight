#pragma once
#include "starlight/_global.h"

#include <string>
#include <functional>
#include <memory>

#include "starlight/ui/Form.h"
#include "starlight/ui/Button.h"
#include "starlight/ui/ScrollField.h"
#include "starlight/ui/DrawLayerProxy.h"

#include "starlight/dialog/osk/InputHandler.h"

namespace starlight {
    namespace dialog {
        class OSK : public ui::Form, public ui::FormCreator<OSK> {
        private:
            std::shared_ptr<ui::UIContainer> setContainer;
            std::shared_ptr<ui::ScrollField> previewSc;
            std::shared_ptr<ui::DrawLayerProxy> preview;
            
            std::shared_ptr<ui::Button> shiftKey;
            
            //Vector2 cursorPos;
            bool shiftLock = false;
        
        public:
            std::unique_ptr<osk::InputHandler> handler;
            
            OSK(osk::InputHandler* handler);
            //~OSK() override { };
            
            void Update(bool focused) override;
            
            void OnKey();
            
            void RefreshPreview();
            void DrawPreview(ui::DrawLayerProxy& layer);
            void OnPreviewTap(ui::DrawLayerProxy& layer);
        };
    }
}
