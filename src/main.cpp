/*! \file main.cpp
 * \brief Entry app file.
 *
 * \authors Dmitrii Leliuhin
 * \date July 2020
 *
 * Details.
 *
 */

//=======================================================================================

#include "subscribe.h"
#include "config.h"
#include "core.h"
#include "publish.h"
#ifdef GUI
#include "view.h"
#endif

#include "args_parser/arguments.h"

#include "vapplication.h"
#include "vthread.h"

#include <iostream>

//=======================================================================================
/*! \fn int main( int argc, char **argv )
 * \brief Entry point.
 *
 * Execution of the program starts here.
 *
 * \param[in] argc Number of arguments.
 * \param[in] argv List of arguments.
 *
 * \return App exit status.
 */
int main( int argc, char **argv )
{
    // Parse config && create PID

    service::arguments sargs( argc, argv,
                            "cservice_template",
                            Config::by_default() );
    Config config;
    {
        config.capture( sargs.settings() );
        config.logs.setup();
    }

    //-----------------------------------------------------------------------------------

    // Link signals -> slots

    Subscribe subscriber( config );
    Publish publisher( config );
    Core core( config );

    subscriber.received.link( &core, &Core::run );

    core.processed.link( &publisher, &Publish::send );

    //-----------------------------------------------------------------------------------

    // GUI in separate thread

#ifdef GUI
    vthread thread;
    thread.invoke( [&]
    {
        View viewer( sargs.app_name() );
        core.plot_data.link( &viewer, &View::plot );
        viewer.run();
    } );
#endif

    //-----------------------------------------------------------------------------------

    vapplication::poll();

    return EXIT_SUCCESS;
}
//=======================================================================================
