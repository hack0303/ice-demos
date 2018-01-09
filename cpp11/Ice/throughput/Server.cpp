// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <ThroughputI.h>

using namespace std;

class ThroughputServer : public Ice::Application
{
public:

    virtual int run(int, char*[]) override;
};

int
main(int argc, char* argv[])
{
#ifdef ICE_STATIC_LIBS
    Ice::registerIceSSL();
    Ice::registerIceWS();
#endif

    ThroughputServer app;
    return app.main(argc, argv, "config.server");
}

int
ThroughputServer::run(int argc, char*[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return 1;
    }

    auto adapter = communicator()->createObjectAdapter("Throughput");
    auto servant = make_shared<ThroughputI>();
    adapter->add(servant, Ice::stringToIdentity("throughput"));
    adapter->activate();
    communicator()->waitForShutdown();
    return 0;
}
