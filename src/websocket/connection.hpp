//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef DECEMBER_2020_CONNECTION_HPP
#define DECEMBER_2020_CONNECTION_HPP

#include "websocket/connect_options.hpp"
#include "websocket/event.hpp"

namespace websocket
{
struct connection
{
    void send(std::string_view msg, bool is_text = true);
    net::awaitable<event> consume();
    beast::websocket::close_reason const& reason() const;
};

net::awaitable< connection >
connect(std::string url, connect_options options = {});
}   // namespace websocket

#endif   // DECEMBER_2020_CONNECTION_HPP
