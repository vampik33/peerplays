#pragma once

#include <graphene/peerplays_sidechain/defs.hpp>
#include <graphene/peerplays_sidechain/peerplays_sidechain_plugin.hpp>

#include <vector>

#include <boost/program_options.hpp>

namespace graphene { namespace peerplays_sidechain {

class sidechain_net_handler {
public:
    sidechain_net_handler(peerplays_sidechain_plugin &_plugin, const boost::program_options::variables_map& options);
    virtual ~sidechain_net_handler();

    std::vector<std::string> get_sidechain_addresses();

protected:
    peerplays_sidechain_plugin &plugin;
    graphene::peerplays_sidechain::sidechain_type sidechain;

    virtual std::string create_multisignature_wallet( const std::vector<std::string> public_keys ) = 0;
    virtual std::string transfer( const std::string& from, const std::string& to, const uint64_t amount ) = 0;
    virtual std::string sign_transaction( const std::string& transaction ) = 0;
    virtual std::string send_transaction( const std::string& transaction ) = 0;

    virtual void handle_event( const std::string& event_data ) = 0;

private:

};

} } // graphene::peerplays_sidechain

