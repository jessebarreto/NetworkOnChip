# NetworkOnChip
Development of a Network on Chip Simulation using SystemC.

This is the final project of the course Silicon Systems Modelling at University of Brasília @ 01/2017.

## Objectives

This project has as final objective the development of a NoC with the following characteristics:

### Router Architecture

The NoC Router will have the following characteristics:

 * Routing - Using XY-Algorithm.
 * Switching Scheme - Wormhole Switching.
 * Flow Control - Handshaking Signal based.
 * Arbiter Scheme - FCFS (First Come First Serve).
 * Using VC (Virtual Channel)

The messages will be divide in packets with N-flits with 32-bits depth. The first flit will be used as header
to allocate network resources to be used by the following data flits.

The Header flit will divided as:

\------------------------------------------------------------------------------------------

\| source ID (8 bits) | destiny ID (8 bits) | packet size (8 bits) | flit number (8 bits) |

\------------------------------------------------------------------------------------------

### Network Interface Architecture

The NoC NI will have the following characteristics:

 * Back-End - Responsible for encapsulate/desencapsulate the message in a group of packets to be send by the router.
 * Front-End - Used as wrapper to make sure the different PE can communicate through the NoC.

### Processor Elements

The NoC will be used in MpSoC with elements developed by other groups. The following PE are expected to be connected in
our NoC:

 * Risc-V Processor
 * MIPS Processor
 * Graphic Unit
 * Shared Memory
 * Criptographic Unit

## Group Members

 * Jessé Barreto
 * Javier Sánchez
 * João Carlos Passos
 * Pedro
 * Adalberto Gualeve (Group Supervisor)

## Bibliography

 * SUDEEP PASRICHA & NIKIL DUTT, On-Chip Communication Architectures - System On Chip Interconnect, Morgan-Kauffmann, 2008, Chap. 12
 * Agarwal, Ankur, Cyril Iskander, and Ravi Shankar. "Survey of network on chip (noc) architectures & contributions." Journal of engineering, Computing and Architecture 3.1 (2009): 21-27.
 * Zeferino, Cesar Albenes, Márcio Eduardo Kreutz, and Altamiro Amadeu Susin. "RASoC: A router soft-core for networks-on-chip." Design, Automation and Test in Europe Conference and Exhibition, 2004. Proceedings. Vol. 3. IEEE, 2004.
 * Dimitrakopoulos, Giorgos, Psarras, Anastasios, and Ioannis Seitanidis, Microarchitecture of Network-onChip Routers - A Designer's Perspective, Springer, 2015.
