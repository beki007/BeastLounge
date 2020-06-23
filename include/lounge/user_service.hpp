//
// Copyright (c) 2020 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/BeastLounge
//

#ifndef LOUNGE_USER_SERVICE_HPP
#define LOUNGE_USER_SERVICE_HPP

#include <lounge/server.hpp>
#include <lounge/user.hpp>
#include <lounge/user_data.hpp>
#include <memory>

namespace lounge {

class user_service
    : public service
{
public:
    /** Create a new user.

        @param c The connection object.

        @param h The handler to process events.
    */
    template<class Handler>
    boost::shared_ptr<user>
    create_user(
        boost::weak_ptr<void> c,
        Handler&& h);

    /** Create a new user data key using the type T.
    */
    //template<class T>
    
    static
    user_service&
    install(
        server& srv);

protected:
    using handler = user::handler;
    //using any_data = user_data_base::any_data;

    virtual
    boost::shared_ptr<user>
    create_user_impl(
        boost::weak_ptr<void> c,
        std::unique_ptr<handler>) = 0;
};

} // lounge

#include <lounge/impl/user_service.hpp>

#endif