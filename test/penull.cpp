#include "penull.h"

#include "nocdebug.h"

ProcessorElementNull::ProcessorElementNull(sc_module_name name)
{
    _name = this->basename();
    NoCDebug::printDebug(std::string("> Null: " + _name), NoCDebug::Assembly);
}
