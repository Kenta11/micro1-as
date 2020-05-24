#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

namespace micro1 {

enum class InstGroup {
    GROUP1,
    GROUP2,
    GROUP3,
    GROUP4,
    GROUP5,
    GROUP6,
    GROUP7,
    GROUP8,
    GROUP9,
    INVALID
};

class Instruction {
public:
    Instruction() { m_value = 0; }
    Instruction(uint16_t value) : m_value(value) {}
private:
    uint16_t m_value;
public:
    uint16_t& value() { return m_value; }
    uint8_t op() const { return static_cast< uint8_t >((m_value >> 12)); }
    uint8_t ra() const { return static_cast< uint8_t >((m_value >> 10) & 3); }
    uint8_t rb() const { return static_cast< uint8_t >((m_value >> 8) & 3); }
    uint8_t nd() const { return static_cast< uint8_t >(m_value & 0xF); }
    void setND(uint8_t nd) { m_value = (m_value & 0xFF00) | static_cast< uint16_t >(nd); }
};

InstGroup getNumberOfGroup(std::string op);
std::tuple<uint8_t, uint8_t, uint8_t> getEncoding(std::string op);

}

#endif // INSTRUCTION_H