#pragma once

namespace Zmallwood {
    class Tile {
       public:
        void SetGround(const std::string &text);
        auto Ground() { return m_ground; }
        void SetGround(int value) { m_ground = value; }
        auto Color() { return m_color; }
        void SetColor(Zmallwood::Color value) { m_color = value; }

       private:
        int m_ground = 0;
        Zmallwood::Color m_color;
    };
}