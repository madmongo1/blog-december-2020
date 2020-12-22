//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DECEMBER_2020_EVENT_HPP
#define DECEMBER_2020_EVENT_HPP

#include "config.hpp"
#include "websocket/message.hpp"

namespace websocket
{
struct event
{
    bool
    is_error() const;
    bool
    is_message() const;
    error_code const &
    error() const;
    struct message &
    message();
    struct message const &
    message() const;
};

}   // namespace websocket

#endif   // DECEMBER_2020_EVENT_HPP
