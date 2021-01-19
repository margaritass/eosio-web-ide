#include <eosio/eosio.hpp>

using namespace eosio;


  class tictactoe : eosio::contract {
    public:
    // Use contract's constructor
       using contract::contract;
  
       [[eosio::action]] void welcome( name host, name challenger){
         require_auth(get_self()); 
         print("Welcome " host.name ", "  challenger.name);
  };
};