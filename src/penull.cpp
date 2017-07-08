#include "penull.h"

#include "nocdebug.h"

ProcessorElementNull::ProcessorElementNull(sc_module_name name, unsigned position) :
    _position(position)
{
    NoCDebug::printDebug(std::string("> Null: N" + std::to_string(_position)), NoCDebug::Assembly);
}
