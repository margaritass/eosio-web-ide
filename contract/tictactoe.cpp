#include <eosio/eosio.hpp>

using namespace eosio;

  class [[eosio::contract("tictactoe")]] tictactoe : public eosio::contract {
 
    public:
    
        tictactoe( name receiver, name code,  datastream<const char*> ds): 
         contract( receiver, code, ds){}
       

        [[eosio::action]] void welcome( name host, name challenger){
         require_auth(get_self()); 
         print( "Welcome ",  host , ", ", challenger ); };

         [[eosio::action]] void create( name host, name challenger){
         require_auth(get_self());
         game_index game(get_self(), get_self().value);
         check(host != challenger, "Host And Challenger Should Be Different ");
         auto itr = game.find((host.value + challenger.value));
         check(itr == game.end(), "Game Already In Progress");
         game.emplace(get_self(),[&](auto&  new_row){
           new_row.host = host;
           new_row.challenger = challenger;
          }); 
         };
         [[eosio::action]] void close( name host, name challenger){
         require_auth(get_self());
         game_index game(get_self(), get_self().value); 
         check(host != challenger, "Host And Challenger Should Be Different ");
         auto itr = game.find((host.value + challenger.value));
         eosio::check(itr != game.end(), "Game Not Found");
         game.erase(itr);
          };  

    private:
       struct [[eosio::table]] game_record{    
       name host;
       name challenger;
       uint64_t primary_key() const {return ( host.value + challenger.value) ;};
       uint64_t by_challenger() const {return (challenger.value) ;};
       EOSLIB_SERIALIZE(game_record, (host)(challenger))
       };
       typedef eosio::multi_index<
         name("game"),                                  //- Table Name
         game_record,                                  //- Table Structure
         eosio::indexed_by<
          name("challenger"),
          eosio::const_mem_fun<
            game_record,
            uint64_t,       
            &game_record::by_secondary>>                             
         >game_index ;                                  //- Type Name
  
 };