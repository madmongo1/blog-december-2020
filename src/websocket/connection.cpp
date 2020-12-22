//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection.hpp"

namespace websocket
{
net::awaitable< connection >
connect(std::string url, websocket::connect_options options)
{
    boost::ignore_unused(url, options);
    co_return connection();
}
}   // namespace websocket