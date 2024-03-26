#pragma once

namespace Funtasia {
    class GameProps {
       public:
        auto ClearColor() { return m_clearColor; }
        void SetClearColor(Color value) { m_clearColor = value; }
        static GameProps *Get();

       private:
        GameProps() = default;

        Color m_clearColor = {0, 0, 20, 255};
    };
}