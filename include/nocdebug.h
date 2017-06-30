#ifndef NOCDEBUG_H
#define NOCDEBUG_H

#include <string>
#include <iostream>

// Defines the Debug Level to be printed.
#define NOC_COMMON_DEBUG (NoCDebug::Assembly | NoCDebug::Channel | NoCDebug::Router | NoCDebug::NI | NoCDebug::PE)

/*!
 * Namespace with everything related to Debug.
 */
namespace NoCDebug
{
    /*!
     * \brief The DebugLevel enumerates the multiple types of sources from debug.
     */
    enum DebugLevel {       // 0x10: most restricted, 0x01: least restricted
        PE  = 0x10,         // mostra detalhes de processamento dos IP-cores (Processor Elements)
        NI = 0x08,          // mostra detalhes de processamento das interfaces de redes (NI)
        Router = 0x04,      // mostra detalhes de processamento dos modulos roteadores
        Channel = 0x02,     // mostra detalhes de transmissao entre roteadores (canais)
        Assembly = 0x01     // mostra detalhes da criação da NoC
    };

    /*!
     * \brief Converts a DebugLevel type to its string value.
     * \param type The DebugLevel type, i.e, PE, NI, Router, Channel or Assembly.
     * \return The string value of the DebugLevel type or an empty string when a not registered DebugLevel type is used.
     */
    inline static const std::string debugTypeToString(DebugLevel type)
    {
        switch (type) {
        case DebugLevel::PE:
            return "PE";
        case DebugLevel::NI:
            return "NI";
        case DebugLevel::Router:
            return "Router";
        case DebugLevel::Channel:
            return "Channel";
        case DebugLevel::Assembly:
            return "Assembly";
        default:
            return "";
        }
    }

    /*!
     * \brief This function is responsible to print debug messages to execution console/log.
     * \param message The message to be printed.
     * \param type The type of the source of the message.
     * \param isError A flag that indicates a critical error on the system.
     *        Deal with this error as you like with assert, exceptiption handling or even exit.
     */
    static void printDebug(const std::string &message, DebugLevel type, bool isError = false)
    {
        if (NOC_COMMON_DEBUG & type) {
            std::cout << "[DEBUG-Type: " << debugTypeToString(type) << "]";
            if (isError) {
                std::cout << "[ERROR]";
            }
            std::cout << " - " << message << std::endl;
        }
    }
}


#endif // NOCDEBUG_H
