//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef DECEMBER_2020_VARIANT_WEBSOCKET_HPP
#define DECEMBER_2020_VARIANT_WEBSOCKET_HPP

#include "config.hpp"
#include "websocket/connect_options.hpp"

namespace websocket
{
enum transport_type
{
    transport_tcp,
    transport_tls
};

using tcp_layer = beast::tcp_stream;
using tls_layer = beast::ssl_stream< tcp_layer >;

struct variant_websocket
{
    variant_websocket() = default;

    net::awaitable< void >
    connect(std::string const &url, connect_options const &opts);

  private:
    void
    emplace_tcp(net::any_io_executor                   exec,
                beast::websocket::stream_base::timeout to);

    void
    emplace_tls(net::any_io_executor                   exec,
                ssl::context &                         sslctx,
                beast::websocket::stream_base::timeout to);

    tcp_layer &
    get_tcp();

    tls_layer &
    get_tls();

    tls_layer *
    query_tls();

    void
    set_headers(beast::http::fields const &headers);

    [[nodiscard]] net::awaitable< void >
    client_handshake(beast::websocket::response_type &response,
                     std::string const &              host,
                     std::string const &              target);

    template < class F >
    auto
    visit(F &&f) -> decltype(auto);

    template < class F >
    auto
    visit(F &&f) const -> decltype(auto);

  private:
    using ws_layer     = beast::websocket::stream< tcp_layer >;
    using wss_layer    = beast::websocket::stream< tls_layer >;
    using variant_type = variant< monostate, ws_layer, wss_layer >;
    variant_type var_;
};

template < class F >
auto
variant_websocket::visit(F &&f) -> decltype(auto)
{
    if (auto &var = var_; holds_alternative< ws_layer >(var))
        return f(get< ws_layer >(var));
    else if (holds_alternative< wss_layer >(var))
        return f(get< wss_layer >(var));

    assert(!"invalid websocket visit");
    throw std::logic_error("invalid websocket visit");
}

template < class F >
auto
variant_websocket::visit(F &&f) const -> decltype(auto)
{
    if (auto &var = var_; holds_alternative< ws_layer >(var))
        return f(get< ws_layer >(var));
    else if (holds_alternative< wss_layer >(var))
        return f(get< wss_layer >(var));

    assert(!"invalid websocket visit");
    throw std::logic_error("invalid websocket visit");
}

}   // namespace websocket

#endif   // DECEMBER_2020_VARIANT_WEBSOCKET_HPP
