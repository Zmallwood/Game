#pragma once

namespace Funtasia {
    class IScene {
       public:
        IScene();
        virtual void OnEnter() {}
        virtual void Update() = 0;
        void Render();
        auto GUI() { return m_gui; }

       protected:
        virtual void Render3D() = 0;

       private:
        std::shared_ptr<tgui::Gui> m_gui;
    };
}