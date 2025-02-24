#include<eosiolib/eosio.hpp>
#include<eosiolib/asset.hpp>
// #include<eosiolib/db.h>
#include<vector>
// #include<unordered_map>

using namespace std;
using namespace eosio;

class [[eosio::contract]] controller : public eosio::contract {
    private:
        // struct stats
        // {
        //     name stat;
        // };
        
        struct [[eosio::table]] users
        {
            name username;
            vector<uint8_t> owned_packs;
            vector<uint8_t> owned_cards;
            // stats;
            auto primary_key() const { return username.value; };
        };
        

        enum pack_status: int8_t {
            OPEN = 1,
            CLOSED = 0
        };

        struct [[eosio::table]] pack_user_logs {
            // name user;
            // name user;
            uint8_t packs_available;
            uint8_t packs_opened;
            auto primary_key() const { return packs_available; };
        };

        struct [[eosio::table]] packs_collections
        {
            name pack_collection_name;
            uint8_t count;
            uint8_t sold;
            uint8_t available;
            auto primary_key() const { return pack_collection_name.value; };
        };

        struct [[eosio::table]] packs
        {
            name pack_name;
            int8_t status=CLOSED;
            name owner;
            vector<int8_t> populated_cards;
            name collection_name;
            auto primary_key() const { return pack_name.value; };
        };

        typedef eosio::multi_index<name("collection"), packs_collections> packs_collections_table;
        typedef eosio::multi_index<name("packs"), packs> packs_table;
        typedef eosio::multi_index<name("users"), users> user_table;
        typedef eosio::multi_index<name("logs"), pack_user_logs> pack_user_logs_table;

        user_table _users;
        packs_collections_table _packs_collections;
        packs_table _packs;
        pack_user_logs_table _pack_user_logs;
        
        // _pack_user_logs::iterator pack_user_logs_iterator;

        // void add_available_pack();

        // void add_opened_pack();

        // void remove_pack_from_collection(name pack);

        // void add_pack_to_collection(name collection, name pack);

        // void update_user_pack(name user, name pack);

        // void update_user_cards(name user, uint8_t card_id);

        // void update_pack_owner(name pack, name owner);

        // void update_pack_status(name pack, string status);


    public:
        controller(name receiver, name code, datastream<const char*> ds)
            : contract(receiver, code, ds)
            , _users(receiver, receiver.value)
            , _packs(receiver, receiver.value)
            , _packs_collections(receiver, receiver.value)
            , _pack_user_logs(receiver, receiver.value)
            {
                //create a log in logs table
                _pack_user_logs.emplace(_self, [&](auto& logs) {
                    // logs.user = _self;
                    logs.packs_available = 0;
                    logs.packs_opened = 0;
                });
            };

        [[eosio::action]] 
        void createuser(name username);

        [[eosio::action]]
        void freezeuser(name username);
        
        [[eosio::action]]
        void unfreezeuser(name username, vector<uint8_t> owned_packs, vector<uint8_t> owned_cards);
        
        // [[eosio::action]]
        // void create_pack(); //later

        // [[eosio::action]]
        // void remove_pack(); //later

        // [[eosio::action]]
        // void buy_packs(name pack_id, name owner, name buyer);

        // [[eosio::action]]
        // void sell_pack(name pack_id, name owner);

        // [[eosio::action]]
        // void open_packs(name pack_id);

        // [[eosio::action]]
        // void rand(uint64_t range);
};