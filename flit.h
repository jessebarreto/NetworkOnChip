#ifndef FLIT_H
#define FLIT_H

#include <systemc.h>

// Common Types
typedef sc_uint<FLIT_SIZE> flit_t;
typedef sc_uint<FLIT_SIZE/2> halfflit_t;
typedef sc_uint<FLIT_SIZE/4> quarterflit_t;

/*!
 * \brief The Flit class is responsible to represent the data inside of a Flit.
 * It has the data used by the NoC's Routers also data used only user Debug.
 */
class Flit
{
    /*!
     * \brief The data used by the NoC.
     */
    flit_t _data;

    /*!
     * \brief A unique identification number to this flit globally.
     */
    uint64_t _systemFlitId;

    /*!
     * \brief The identification number for this flit in the packet.
     */
    uint64_t _packetFlitId;

public:
    /*!
     * \brief The default constructor.
     * \param data The flit data.
     * \param uniqueId The flit globally unique identification number;
     * \param flitNumber The flit number inside of the packet.
     */
    Flit(flit_t data, uint64_t uniqueId, uint64_t flitNumber);

    flit_t
};

#endif // FLIT_H
