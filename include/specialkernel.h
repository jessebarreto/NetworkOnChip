#ifndef SPECIALKERNEL_H
#define SPECIALKERNEL_H

#include <systemc.h>

#include "inetworkinterfacefrontend.h"

/*!
 * \brief The SpecialKernel class is a fictitious test implementation of a kernel which connects together two shell
 * modules.
 * This communication happens as a by-pass communication between both shells.
 */
class SpecialKernel : public sc_module
{
    SC_HAS_PROCESS(SpecialKernel);

    /*!
     * \brief Reference of a shell which is considered as master.
     */
    INetworkInterfaceFrontEnd *_frontEndMaster;

    /*!
     * \brief Reference of a shell which is cnsidered as slave.
     */
    INetworkInterfaceFrontEnd *_frontEndSlave;

    /*!
     * \brief Thread of communication between both shells.
     */
    void _threadConnectionMasterSlave();
public:
    /*!
     * \brief Constructor
     * \param name The module name.
     */
    SpecialKernel(sc_module_name name);

    /*!
     * \brief Connects the master shell to the kernel.
     * \param frontEndMaster A reference to the master shell.
     */
    void connectMaster(INetworkInterfaceFrontEnd *frontEndMaster);

    /*!
     * \brief Connects the slave shell to the kernel.
     * \param frontEndSlave A reference to the slave shell.
     */
    void connectSlave(INetworkInterfaceFrontEnd *frontEndSlave);
};

#endif // SPECIALKERNEL_H
