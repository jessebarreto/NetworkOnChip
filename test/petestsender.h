#ifndef PETESTSENDER_H
#define PETESTSENDER_H

#include <systemc.h>

#include "noccommon.h"

/*!
 * \brief The PETestSender class is a test module of an IP-Core to send a message char-by-char using the NoC.
 */
class PETestSender : public sc_module
{
    SC_HAS_PROCESS(PETestSender);

    /*!
     * \brief The test message.
     */
    std::string _message;

    /*!
     * \brief This module main thread.
     */
    void _threadRun();

public:
    // IO
    sc_fifo_out<char> fifoOutput;

    /*!
     * \brief Constructor
     * \param name Module name.
     */
    PETestSender(sc_module_name name);

    /*!
     * \brief Getter to retrieve the test message.
     * \return  the test message.
     */
    const std::__cxx11::string &getMessage();

    /*!
     * \brief Getter to retrieve the module name.
     * \return  the module name.
     */
    const std::__cxx11::string getName();
};

#endif // PETESTSENDER_H
