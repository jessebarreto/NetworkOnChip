#ifndef PENULL_H
#define PENULL_H

#include <systemc.h>

class ProcessorElementNull : public sc_module
{
    SC_HAS_PROCESS(ProcessorElementNull);

    /*!
     * \brief Position of the element in the NoC.
     */
    unsigned _position;
public:
    ProcessorElementNull(sc_module_name name, unsigned position);
};

#endif // PENULL_H
