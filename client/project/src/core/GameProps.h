#pragma once

namespace Zmallwood {
    class GameProps {
       public:
        auto ClearColor() { return m_clearColor; }
        void SetClearColor(Color value) { m_clearColor = value; }
        auto WorldAreaSize() { return m_worldAreaSize; }
        void SetWorldAreaSize(Size value) { m_worldAreaSize = value; }
        static GameProps *Get();

       private:
        GameProps() = default;

        Color m_clearColor = {0, 0, 20, 255};
        Size m_worldAreaSize = {100, 100};
    };
}