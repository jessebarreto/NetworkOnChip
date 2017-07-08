#include "penullshell.h"

#include "nocdebug.h"

ProcessorElementNullShell::ProcessorElementNullShell(sc_module_name name) :
    sc_module(name)
{
    _name = this->basename();
    NoCDebug::printDebug(std::string("> NullShell: " + _name), NoCDebug::Assembly);
}
