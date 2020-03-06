//
// Copyright (c) 2018-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/BeastLounge
//

#include "logger.hpp"
#include "server.hpp"
#include <boost/config.hpp>
#include <boost/beast/src.hpp>
#include <iostream>

#ifdef BOOST_MSVC
# ifndef WIN32_LEAN_AND_MEAN // VC_EXTRALEAN
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
# else
#  include <windows.h>
# endif
#endif

//------------------------------------------------------------------------------

extern
std::unique_ptr<logger>
make_logger();

/** Create a server.

    The configuration file is loaded,
    and all child objects are created.
*/
extern
std::unique_ptr<server>
make_server(
    char const* config_path,
    std::unique_ptr<logger> log);

//------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
#if BOOST_MSVC
    {
        int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
        flags |= _CRTDBG_LEAK_CHECK_DF;
        _CrtSetDbgFlag(flags);
    }
#endif

    // Create the logger as early as possible
    // so we can report more things to the log.
    auto log = make_logger();
    if(! log)
        return EXIT_FAILURE;

    // Check command line arguments.
    if(argc != 2)
    {
        log->cerr() <<
            "Usage: lounge-server <config-path>\n";
        return EXIT_FAILURE;
    }
    auto const config_path = argv[1];

    // Create the server
    beast::error_code ec;
    auto srv = make_server(
        config_path,
        std::move(log));
    if(! srv)
        return EXIT_FAILURE;

    srv->run();

    return EXIT_SUCCESS;
}
