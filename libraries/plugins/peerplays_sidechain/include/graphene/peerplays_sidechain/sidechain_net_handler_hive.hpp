#pragma once

#include <graphene/peerplays_sidechain/sidechain_net_handler.hpp>

#include <string>

#include <fc/network/http/connection.hpp>
#include <fc/signals.hpp>

#include <graphene/peerplays_sidechain/common/rpc_client.hpp>
#include <graphene/peerplays_sidechain/hive/types.hpp>

namespace graphene { namespace peerplays_sidechain {

class hive_node_rpc_client : public rpc_client {
public:
   hive_node_rpc_client(std::string _ip, uint32_t _port, std::string _user, std::string _password);

   std::string account_history_api_get_transaction(std::string transaction_id);
   std::string block_api_get_block(uint32_t block_number);
   std::string condenser_api_get_config();
   std::string database_api_get_dynamic_global_properties();
   std::string database_api_get_version();
   std::string network_broadcast_api_broadcast_transaction(std::string htrx);

   std::string get_chain_id();
   std::string get_head_block_id();
   std::string get_head_block_time();
   std::string get_is_test_net();
   std::string get_last_irreversible_block_num();
};

class hive_wallet_rpc_client : public rpc_client {
public:
   hive_wallet_rpc_client(std::string _ip, uint32_t _port, std::string _user, std::string _password);

   std::string get_account(std::string account);

   std::string get_account_memo_key(std::string account);
};

class sidechain_net_handler_hive : public sidechain_net_handler {
public:
   sidechain_net_handler_hive(peerplays_sidechain_plugin &_plugin, const boost::program_options::variables_map &options);
   virtual ~sidechain_net_handler_hive();

   bool process_proposal(const proposal_object &po);
   void process_primary_wallet();
   void process_sidechain_addresses();
   bool process_deposit(const son_wallet_deposit_object &swdo);
   bool process_withdrawal(const son_wallet_withdraw_object &swwo);
   std::string process_sidechain_transaction(const sidechain_transaction_object &sto);
   std::string send_sidechain_transaction(const sidechain_transaction_object &sto);
   bool settle_sidechain_transaction(const sidechain_transaction_object &sto, asset &settle_amount);

private:
   std::string node_ip;
   uint32_t node_rpc_port;
   std::string node_rpc_user;
   std::string node_rpc_password;
   hive_node_rpc_client *node_rpc_client;

   std::string wallet_ip;
   uint32_t wallet_rpc_port;
   std::string wallet_rpc_user;
   std::string wallet_rpc_password;
   hive_wallet_rpc_client *wallet_rpc_client;

   hive::chain_id_type chain_id;
   hive::network network_type;

   std::string create_primary_wallet_transaction(const son_wallet_object &prev_swo, std::string new_sw_address);
   std::string create_deposit_transaction(const son_wallet_deposit_object &swdo);
   std::string create_withdrawal_transaction(const son_wallet_withdraw_object &swwo);

   uint64_t last_block_received;
   fc::future<void> _listener_task;
   fc::signal<void(const std::string &)> event_received;
   void schedule_hive_listener();
   void hive_listener_loop();
   void handle_event(const std::string &event_data);
};

}} // namespace graphene::peerplays_sidechain
