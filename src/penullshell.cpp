#include "penullshell.h"

#include "nocdebug.h"

ProcessorElementNullShell::ProcessorElementNullShell(sc_module_name name, unsigned position) :
    sc_module(name),
    _position(position)
{
    NoCDebug::printDebug(std::string("> NullShell: N" + std::to_string(position)), NoCDebug::Assembly);
}
