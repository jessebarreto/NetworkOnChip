#include <systemc.h>

#include <routerchannel.h>
#include <channeltester.h>

int main()
{
    ChannelTester tester1("Tester1", 0, true);
    ChannelTester tester2("Tester2", 1, false);

    RouterChannel channel("Channel1");
    tester1.channel(channel);
    tester2.channel(channel);


    // Start Simulation
    std::cout << "Start NoC Simulation..." << std::endl;
    sc_start(sc_time(2, SC_MS), SC_RUN_TO_TIME);

    return 0;
}

