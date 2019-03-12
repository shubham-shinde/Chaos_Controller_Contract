#include "controller.hpp"

void controller::createuser(name username) {
    //to ensure that action has been authorized by user
    require_auth(username);
    //Create a user in user table;
    if(_users.find(username.value) == _users.end()) {
        _users.emplace(username, [&](auto& new_user) {
            new_user.username = username;
        });
    }
}

void controller::freezeuser(name username) {
    // Ensure that user is present in the table 
    auto user_iterator = _users.find(username.value);
    //Delete if user is present.
    if(user_iterator != _users.end()) {
        _users.erase(user_iterator);
    }
}

void controller::unfreezeuser(name username, vector<uint8_t> owned_packs, vector<uint8_t> owned_cards) {
    //to ensure that action has been authorized by user
    require_auth(username);
    //check user is present in table
    if(_users.find(username.value) == _users.end()) {
        //Recreate user
        _users.emplace(username, [&](auto& prev_user) {
            prev_user.username = username;
            prev_user.owned_packs = owned_packs;
            prev_user.owned_cards = owned_cards;
        });
    }
    // return;
}

// void cards::buy_packs(name pack_id, name owner, name buyer) {

// }

// void cards::sell_pack(name pack_id, name owner) {

// }

// void cards::rand(uint64_t range) {

// }

// void add_available_pack() {
//     _pack_user_logs.modify(pack_user_logs_iterator, [&](auto& log) {
//         log.packs_available = log.packs_available+1;
//     });
// }

EOSIO_DISPATCH(controller, (createuser)(freezeuser)(unfreezeuser))