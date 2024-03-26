#pragma once

namespace Zmallwood {
    class Tile {
       public:
        void SetGround(const std::string &text);
        auto Ground() { return m_ground; }
        void SetGround(int value) { m_ground = value; }

       private:
        int m_ground = 0;
    };
}