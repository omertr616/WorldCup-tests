#ifndef DATASTRUCTUREWET2_WORLDCUPTESTS_H
#define DATASTRUCTUREWET2_WORLDCUPTESTS_H

#include "worldcup23a2.h"
#include <cassert>


void add_team_test(){
    world_cup_t world_cup = world_cup_t();

    std::string error_massage = "error in add_team test";
    if (world_cup.add_team(1) != StatusType::SUCCESS){
        throw std::runtime_error(error_massage + ": StatusType::SUCCESS");
    }
    if (world_cup.add_team(1) != StatusType::FAILURE){
        throw std::runtime_error(error_massage + ": StatusType::FAILURE");
    }
    if (world_cup.add_team(0) != StatusType::INVALID_INPUT){
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }

    std::cout << "Pass add_team test" << std::endl;
}


void add_player_test(){
    world_cup_t world_cup = world_cup_t();
    world_cup.add_team(1);
    std::string error_massage = "error in add_player test";

    int a[] = {2,1,3,0,4};
    permutation_t p = permutation_t(a);
    if (world_cup.add_player(
            1,1,p,4,6,
            2,false) != StatusType::SUCCESS){
        throw std::runtime_error(error_massage + ": StatusType::SUCCESS");
    }
    if (world_cup.add_player(
            7,1,p,4,6,
            2,false) != StatusType::SUCCESS){
        throw std::runtime_error(error_massage + ": StatusType::SUCCESS");
    }

    if (world_cup.add_player(
            0,1,p,4,6,
            2,false) != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }
    if (world_cup.add_player(
            2,0,p,4,6,
            2,false) != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }
    int ax[] = {2,4,3,0,4};
    permutation_t px = permutation_t(ax);
    if (world_cup.add_player(
            2,1,px,4,6,
            2,false) != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }
    if (world_cup.add_player(
            2,1,p,-1,6,
            2,false) != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }
    if (world_cup.add_player(
            2,1,p,4,6,
            -1,false) != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }

    if (world_cup.add_player(
            1,1,p,4,6,
            1,false) != StatusType::FAILURE) {
        throw std::runtime_error(error_massage + ": StatusType::FAILURE");
    }
    if (world_cup.add_player(
            1,2,p,4,6,
            1,false) != StatusType::FAILURE) {
        throw std::runtime_error(error_massage + ": StatusType::FAILURE");
    }

    std::cout << "Pass add_player test" << std::endl;
}


void remove_team_test() {
    world_cup_t world_cup = world_cup_t();
    world_cup.add_team(1);
    world_cup.add_team(2);
    int a[] = {2,1,3,0,4};
    permutation_t p = permutation_t(a);
    world_cup.add_player(1,1,p,4,
                         6,2,false);
    world_cup.add_player(2,1,p,4,
                         6,2,false);
    world_cup.add_player(3,2,p,4,
                         6,2,false);
    world_cup.add_player(4,2,p,4,
                         6,2,false);



    std::string error_massage = "error in add_player test";
    if (world_cup.remove_team(0) != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + ": StatusType::INVALID_INPUT");
    }

    if (world_cup.remove_team(3) != StatusType::FAILURE) {
        throw std::runtime_error(error_massage + ": StatusType::FAILURE");
    }

    if (world_cup.remove_team(2) != StatusType::SUCCESS) {
        throw std::runtime_error(error_massage + ": StatusType::SUCCESS");
    }
    if (world_cup.remove_team(1) != StatusType::SUCCESS) {
        throw std::runtime_error(error_massage + ": StatusType::SUCCESS");
    }
    if (world_cup.add_team(1) != StatusType::SUCCESS) {
        throw std::runtime_error(error_massage + ": use again team id after it was removed: StatusType::SUCCESS");
    }
    if (world_cup.remove_team(1) != StatusType::SUCCESS) {
        throw std::runtime_error(error_massage + ": StatusType::SUCCESS, empty team");
    }

    std::cout << "Pass remove_team test" << std::endl;
}


void get_ith_pointless_ability_test(){

    const int PLAYERS_NUM = 24;
    const int TEAMS_NUM = 8;

    world_cup_t world_cup;

    int team_ids[] = {1, 15, 61, 212, 5, 47, 17, 11};

    int player_ids[PLAYERS_NUM];
    for(int i = 0; i < PLAYERS_NUM; i++){
        player_ids[i] = i+1;
    }
    int player_ability[PLAYERS_NUM] = {1, 2, 3, 2, 2, 2,
                                       4, 7, 12, 21, 1, 1,
                                       65, 30, 5, 120, -10, -10,
                                       12, 13, 14, 55, 34, 12};

    permutation_t p = permutation_t::neutral();
    for(int i = 0; i < TEAMS_NUM; i++){
        world_cup.add_team(team_ids[i]);
        for(int j = i*3; j < (i+1)*3; j++){
            world_cup.add_player(player_ids[j],team_ids[i],p,4,
                                 player_ability[j],2,false);
        }
    }

    std::string error_massage = "error in get_ith_pointless_ability test";

    if(world_cup.get_ith_pointless_ability(TEAMS_NUM).status() != StatusType::FAILURE){
        throw std::runtime_error(error_massage + ": index too large");
    }
    if(world_cup.get_ith_pointless_ability(-100).status() != StatusType::FAILURE){
        throw std::runtime_error(error_massage + ": index negative");
    }
    if(world_cup.get_ith_pointless_ability(-1).status() != StatusType::FAILURE){
        throw std::runtime_error(error_massage + ": index negative");
    }

    int expected_output[] = {1, 15, 61, 212, 17, 5, 47, 11};
    for (int i = 0; i < TEAMS_NUM; ++i) {
        if(world_cup.get_ith_pointless_ability(i).ans() != expected_output[i]){
            throw std::runtime_error(error_massage + " index = " + std::to_string(i));
        }
    }

    world_cup.add_player(25,1,p,4,
                         1,2,false);
    world_cup.add_player(26,5,p,4,
                         2,2,false);
    world_cup.add_player(27,212,p,4,
                         100,2,false);
    int expected_output2[] = {15, 1, 61, 17, 47, 11, 5, 212};
    for (int i = 0; i < TEAMS_NUM; ++i) {
        if(world_cup.get_ith_pointless_ability(i).ans() != expected_output2[i]){
            throw std::runtime_error(error_massage + " index = " + std::to_string(i));
        }
    }

    world_cup.remove_team(47);
    int expected_output3[] = {15, 1, 61, 17, 11, 5, 212};
    for (int i = 0; i < 7; ++i) {
        if(world_cup.get_ith_pointless_ability(i).ans() != expected_output3[i]){
            throw std::runtime_error(error_massage + " index = " + std::to_string(i));
        }
    }

    world_cup.remove_team(15);
    world_cup.remove_team(5);
    int expected_output4[] = {1, 61, 17, 11, 212};
    for (int i = 0; i < 5; ++i) {
        if(world_cup.get_ith_pointless_ability(i).ans() != expected_output4[i]){
            throw std::runtime_error(error_massage + " index = " + std::to_string(i));
        }
    }

    world_cup.remove_team(1);
    world_cup.remove_team(61);
    world_cup.remove_team(11);
    world_cup.remove_team(212);
    int expected_output5[] = {17};
    for (int i = 0; i < 1; ++i) {
        if(world_cup.get_ith_pointless_ability(i).ans() != expected_output5[i]){
            throw std::runtime_error(error_massage + " index = " + std::to_string(i));
        }
    }

    world_cup.remove_team(17);
    if(world_cup.get_ith_pointless_ability(0).status() != StatusType::FAILURE){
            throw std::runtime_error(error_massage + " index = 0");
    }

    world_cup_t world_cup2;
    const int LEN = 1000;
    for(int i = 1; i < LEN; i++){
        world_cup2.add_team(i);
        world_cup2.add_player(i, i, p, 1, LEN - i, 1, false);
        for(int j = 0; j <= i; j++){
            if (world_cup2.get_ith_pointless_ability(j).ans() != i - j){
                throw std::runtime_error(error_massage + " index = " + std::to_string(i));
            }
        }
    }
    for(int i = LEN - 1; i > 0; i--){
        world_cup2.remove_team(i);
        for(int j = 0; j < i - 1; j++){
            if (world_cup2.get_ith_pointless_ability(j).ans() != i - 1 - j){
                throw std::runtime_error(error_massage + " index = " + std::to_string(i));
            }
        }
    }


    world_cup_t world_cup3;
    if (world_cup2.get_ith_pointless_ability(0).status() != StatusType::FAILURE){
        throw std::runtime_error(error_massage + " StatusType::FAILURE, empty world cup ");
    }

    std::cout << "Pass get_ith_pointless_ability test" << std::endl;
}

void play_match_test(){

    std::string error_massage = "error in play_match test: ";
    world_cup_t world_cup;

    permutation_t p = permutation_t::neutral();
    world_cup.add_team(1);
    world_cup.add_player(11,1,p,4,
                         3,2,true);
    world_cup.add_player(12,1,p,4,
                         3,2,false);
    world_cup.add_player(13,1,p,4,
                         3,2,false);

    world_cup.add_team(2);
    world_cup.add_player(21,2,p,4,
                         3,2,true);
    world_cup.add_player(22,2,p,4,
                         3,2,false);
    world_cup.add_player(23,2,p,4,
                         3,2,false);

    world_cup.add_team(3);
    world_cup.add_player(31,3,p,4,
                         3,2,false);
    world_cup.add_player(32,3,p,4,
                         3,2,false);
    world_cup.add_player(33,3,p,4,
                         3,2,false);

    int a[] = {2,1,3,0,4};
    permutation_t pd = permutation_t(a);
    world_cup.add_team(4);
    world_cup.add_player(41,4,p,4,
                         3,2,true);
    world_cup.add_player(42,4,p,4,
                         3,2,false);
    world_cup.add_player(43,4,pd,4,
                         4,2,false);

    int player_ids[] = {11,12,13,21,22,23,31,32,33,41,42,43};
    for (int i = 0; i < 12; ++i) {
        if(world_cup.num_played_games_for_player(player_ids[i]).ans() != 4)
            throw std::runtime_error(error_massage + "num_played_games_for_player: " + std::to_string(i));
    }

    if(world_cup.num_played_games_for_player(0).status() != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "num_played_games_for_player: StatusType::INVALID_INPUT: 0");

    if(world_cup.num_played_games_for_player(7).status() != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "num_played_games_for_player: StatusType::FAILURE: 7");

    if (world_cup.play_match(1,0).status() != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + "StatusType::INVALID_INPUT: zero team id");
    }

    if (world_cup.play_match(1,1).status() != StatusType::INVALID_INPUT) {
        throw std::runtime_error(error_massage + "StatusType::INVALID_INPUT: identical team id");
    }

    if (world_cup.play_match(1,3).status() != StatusType::FAILURE) {
        throw std::runtime_error(error_massage + "StatusType::FAILURE: a team without gatekeeper");
    }

    if (world_cup.play_match(1,9).status() != StatusType::FAILURE) {
        throw std::runtime_error(error_massage + "StatusType::FAILURE: a team with unknown teamId");
    }

    for (int i = 0; i < 12; ++i) {
        if(world_cup.num_played_games_for_player(player_ids[i]).ans() != 4)
            throw std::runtime_error(error_massage + "num_played_games_for_player: " + std::to_string(i));
    }

    if (world_cup.play_match(1,2).ans() != 0) {
        throw std::runtime_error(error_massage + "0 draw");
    }

    int expected1[] = {5,5,5,5,5,5,4,4,4,4,4,4};
    for (int i = 0; i < 12; ++i) {
        if(world_cup.num_played_games_for_player(player_ids[i]).ans() != expected1[i])
            throw std::runtime_error(error_massage + "num_played_games_for_player: after draw: " + std::to_string(i));
    }

    if (world_cup.play_match(1,4).ans() != 2) {
        throw std::runtime_error(error_massage + "2 spiritual win");
    }
    int expected2[] = {6,6,6,5,5,5,4,4,4,5,5,5};
    for (int i = 0; i < 12; ++i) {
        if(world_cup.num_played_games_for_player(player_ids[i]).ans() != expected2[i])
            throw std::runtime_error(error_massage + "num_played_games_for_player: " + std::to_string(i));
    }

    world_cup.add_player(44,4,p,4,
                         3,2,false);
    if (world_cup.play_match(4,1).ans() != 4) {
        throw std::runtime_error(error_massage + "4 spiritual win");
    }
    int player_ids3[] = {11,12,13,21,22,23,31,32,33,41,42,43,44};
    int expected3[] = {7,7,7,5,5,5,4,4,4,6,6,6,5};
    for (int i = 0; i < 13; ++i) {
        if(world_cup.num_played_games_for_player(player_ids3[i]).ans() != expected3[i])
            throw std::runtime_error(error_massage + "num_played_games_for_player: " + std::to_string(i));
    }

    if (world_cup.play_match(1,4).ans() != 1) {
        throw std::runtime_error(error_massage + "1 ability win");
    }
    int player_ids4[] = {11,12,13,21,22,23,31,32,33,41,42,43,44};
    int expected4[] = {8,8,8,5,5,5,4,4,4,7,7,7,6};
    for (int i = 0; i < 13; ++i) {
        if(world_cup.num_played_games_for_player(player_ids4[i]).ans() != expected4[i])
            throw std::runtime_error(error_massage + "num_played_games_for_player: " + std::to_string(i));
    }

    if (world_cup.play_match(4,1).ans() != 3) {
        throw std::runtime_error(error_massage + "3 ability win");
    }
    int player_ids5[] = {11,12,13,21,22,23,31,32,33,41,42,43,44};
    int expected5[] = {9,9,9,5,5,5,4,4,4,8,8,8,7};
    for (int i = 0; i < 13; ++i) {
        if(world_cup.num_played_games_for_player(player_ids5[i]).ans() != expected5[i])
            throw std::runtime_error(error_massage + "num_played_games_for_player: " + std::to_string(i));
    }

    world_cup.add_player(14,1,p,100,0,0, false);
    if (world_cup.num_played_games_for_player(14).ans() != 100)
        throw std::runtime_error(error_massage + "num_played_games_for_player: 14");


    std::cout << "Pass play_match test" << std::endl;
}

void get_partial_spirit_test() {

    std::string error_massage = "error in get_partial_spirit test: ";
    world_cup_t world_cup;

    world_cup.add_team(1);

    int a1[] = {0,1,2,3,4};
    permutation_t p1 = permutation_t(a1);
    world_cup.add_player(11, 1, p1, 4,
                         3, 2, true);

    int a2[] = {1,2,3,4,0};
    permutation_t p2 = permutation_t(a2);
    world_cup.add_player(12, 1, p2, 4,
                         3, 2, false);

    int a3[] = {2,3,4,0,1};
    permutation_t p3 = permutation_t(a3);
    world_cup.add_player(13, 1, p3, 4,
                         3, 2, false);

    int a4[] = {3,4,0,1,2};
    permutation_t p4 = permutation_t(a4);
    world_cup.add_player(14, 1, p4, 4,
                         3, 2, false);

    if (world_cup.get_partial_spirit(0).status() != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT: 0");

    if (world_cup.get_partial_spirit(666).status() != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: 666");





    if (world_cup.get_partial_spirit(1).ans() == p1)
        throw std::runtime_error(error_massage + "player 1");
    if (world_cup.get_partial_spirit(2).ans() == p1*p2)
        throw std::runtime_error(error_massage + "player 2");
    if (world_cup.get_partial_spirit(3).ans() == p1*p2*p3)
        throw std::runtime_error(error_massage + "player 3");
    if (world_cup.get_partial_spirit(4).ans() == p1*p2*p3*p4)
        throw std::runtime_error(error_massage + "player 4");



    world_cup.remove_team(1);
    if (world_cup.get_partial_spirit(11).status() != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: 1, after remove team");

    std::cout << "Pass get_partial_spirit test" << std::endl;
}

void get_team_points_test() {
    std::string error_massage = "error in get_partial_spirit test: ";
    world_cup_t world_cup;

    if (world_cup.get_team_points(0).status() != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT: 0");

    if (world_cup.get_team_points(1).status() != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: 1");

    int a[] = {0,1,2,3,4};
    permutation_t p = permutation_t(a);

    world_cup.add_team(1);
    world_cup.add_player(1, 1, p, 4,
                         3, 2, true);

    world_cup.add_team(2);
    world_cup.add_player(2, 2, p, 4,
                         3, 2, true);

    world_cup.add_team(3);
    world_cup.add_player(3, 3, p, 4,
                         3, 2, true);



    world_cup.add_team(4);
    int a1[] = {4,3,2,1,0};
    permutation_t p1 = permutation_t(a1);
    world_cup.add_player(4, 4, p1, 4,
                         3, 2, true);

    for (int i = 1; i <= 4; ++i) {
        if (world_cup.get_team_points(i).ans() != 0)
            throw std::runtime_error(error_massage + "initial points");
    }

    world_cup.play_match(1,2);
    if (world_cup.get_team_points(1).ans() != 1)
        throw std::runtime_error(error_massage + "tie: team 1");
    if (world_cup.get_team_points(2).ans() != 1)
        throw std::runtime_error(error_massage + "tie: team 2");

    world_cup.play_match(1,3);
    if (world_cup.get_team_points(1).ans() != 4)
        throw std::runtime_error(error_massage + "team 1: after team 1 defeat team 3");
    if (world_cup.get_team_points(3).ans() != 0)
        throw std::runtime_error(error_massage + "team 3: after team 1 defeat team 3");

    world_cup.play_match(4,2);
    if (world_cup.get_team_points(4).ans() != 0)
        throw std::runtime_error(error_massage + "team 4: after team 2 defeat team 4");
    if (world_cup.get_team_points(2).ans() != 4)
        throw std::runtime_error(error_massage + "team 2: after team 2 defeat team 4");

    world_cup.play_match(4,3);
    if (world_cup.get_team_points(4).ans() != 0)
        throw std::runtime_error(error_massage + "team 4: after team 4 defeat team 3");
    if (world_cup.get_team_points(3).ans() != 3)
        throw std::runtime_error(error_massage + "team 3: after team 4 defeat team 3");


    std::cout << "Pass get_team_points test" << std::endl;
}

void add_player_cards_test(){
    std::string error_massage = "error in add_player_cards test: ";
    world_cup_t world_cup;

    if (world_cup.add_player_cards(0,0) != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT: id = 0");
    if (world_cup.add_player_cards(1,-1) != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT: card = -1");

    if (world_cup.add_player_cards(1,0) != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: id = 1");


    int a[] = {0,1,2,3,4};
    permutation_t p = permutation_t(a);
    world_cup.add_team(1);
    world_cup.add_player(1, 1, p, 4,
                         3, 2, true);
    world_cup.add_player(2, 1, p, 4,
                         3, 2, true);

    world_cup.remove_team(1);

    if (world_cup.add_player_cards(1,0) != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: id = 1 after removing team");
    if (world_cup.add_player_cards(1,0) != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: id = 2 after removing team");


    std::cout << "Pass add_player_cards test" << std::endl;
}


void get_player_cards_test(){
    std::string error_massage = "error in get_player_cards test: ";
    world_cup_t world_cup;

    if (world_cup.get_player_cards(0).status() != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT: 0");

    if (world_cup. get_player_cards(1).status() != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: 1");


    int a[] = {0,1,2,3,4};
    permutation_t p = permutation_t(a);
    world_cup.add_team(1);
    world_cup.add_player(1, 1, p, 4,
                         3, 2, true);
    world_cup.add_player(2, 1, p, 4,
                         3, 2, true);
    world_cup.add_player(3, 1, p, 4,
                         3, 2, true);


    if (world_cup.get_player_cards(1).ans() != 2)
        throw std::runtime_error(error_massage + "cards need to be 2");


    world_cup.add_player_cards(1,1);
    if (world_cup.get_player_cards(1).ans() != 3)
        throw std::runtime_error(error_massage + "cards need to be 3");

    world_cup.add_player_cards(1,1);
    if (world_cup.get_player_cards(1).ans() != 4)
        throw std::runtime_error(error_massage + "cards need to be 4");

    world_cup.add_player_cards(3,1);
    if (world_cup.get_player_cards(3).ans() != 3)
        throw std::runtime_error(error_massage + "cards need to be 4");


    std::cout << "Pass get_player_cards test" << std::endl;
}



void buy_team_test1(){

    std::string error_massage = "error in buy_team test1: ";
    world_cup_t world_cup;

    if (world_cup.buy_team(0,1) != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT");
    if (world_cup.buy_team(1,0) != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT");
    if (world_cup.buy_team(1,1) != StatusType::INVALID_INPUT)
        throw std::runtime_error(error_massage + "INVALID_INPUT");

    if (world_cup.buy_team(1,2) != StatusType::FAILURE)
        throw std::runtime_error(error_massage + "FAILURE: 1, 2");


    world_cup.add_team(1);
    permutation_t p_ident = permutation_t::neutral();
    world_cup.add_player(11, 1, p_ident, 4,
                         3, 2, true);
    int a12[] = {2,1,3,0,4};
    permutation_t p12 = permutation_t(a12);
    world_cup.add_player(12, 1, p12, 4,
                         3, 2, false);
    int a13[] = {3,1,2,0,4};
    permutation_t p13 = permutation_t(a13);
    world_cup.add_player(13, 1, p13, 4,
                         3, 2, false);




    world_cup.add_team(2);

    world_cup.add_player(21, 2, p_ident, 4,
                         3, 2, true);
    int a22[] = {1,3,2,4,0};
    permutation_t p22 = permutation_t(a22);
    world_cup.add_player(22, 2, p22, 4,
                         3, 2, false);
    int a23[] = {2,3,1,4,0};
    permutation_t p23 = permutation_t(a23);
    world_cup.add_player(23, 2, p23, 4,
                         3, 2, false);

    world_cup.add_team(3);
    world_cup.add_player(31, 3, p_ident, 4,
                         3, 2, false);
    int a32[] = {1,3,2,0,4};
    permutation_t p32 = permutation_t(a32);
    world_cup.add_player(32, 3, p32, 4,
                         3, 2, false);
    int a33[] = {1,3,2,0,4};
    permutation_t p33 = permutation_t(a33);
    world_cup.add_player(33, 3, p33, 4,
                         3, 2, false);

    world_cup.add_team(4);
    world_cup.add_player(41, 4, p_ident, 4,
                         3, 2, true);
    permutation_t p42 = permutation_t::read("3,4,2,1,5");
    world_cup.add_player(42, 4, p42, 4,
                         3, 2, false);
    permutation_t p43 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(43,4,p43,4,
                         4,2,false);

    world_cup.add_team(5);
    world_cup.add_player(51, 5, p_ident, 4,
                         3, 2, true);
    permutation_t p52 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(52, 5, p52, 4,
                         3, 2, false);
    permutation_t p53 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(53, 5, p53, 4,
                         3, 2, false);

    world_cup.add_team(6);
    world_cup.add_player(61, 6, p_ident, 4,
                         3, 2, true);
    permutation_t p62 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(62, 6, p62, 4,
                         3, 2, false);
    permutation_t p63 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(63, 6, p63, 4,
                         3, 2, false);

    world_cup.add_team(7);
    world_cup.add_player(71, 7, p_ident, 4,
                         3, 2, true);
    permutation_t p72 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(72, 7, p72, 4,
                         3, 2, false);
    permutation_t p73 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(73, 7, p73, 4,
                         3, 2, false);

    world_cup.add_team(8);
    world_cup.add_player(81, 8, p_ident, 4,
                         3, 2, true);
    permutation_t p82 = permutation_t::read("1,3,5,2,4");
    world_cup.add_player(82, 8, p82, 4,
                         3, 2, false);
    permutation_t p83 = permutation_t::read("4,3,1,2,5");
    world_cup.add_player(83, 8, p83, 4,
                         3, 2, false);

    world_cup.play_match(1,2);
    world_cup.play_match(1,4);
    world_cup.play_match(4,1);
    world_cup.play_match(1,4);
    world_cup.play_match(4,1);
    world_cup.play_match(5,6);
    world_cup.play_match(6,7);
    world_cup.play_match(6,5);
    world_cup.play_match(7,8);

    int TEAMS_NUM = 8;
    int PLAYERS_NUM = 24;
    int player_ids [] = {11,12,13,21,22,23,31,32,33,41,42,43,51,52,53,61,62,63,71,72,73,81,82,83};

    int team_points_before_buy [TEAMS_NUM];
    for(int i = 0; i < TEAMS_NUM; i++){
        team_points_before_buy[i] = world_cup.get_team_points(i + 1).ans();
    }

    int played_games_before_buy [PLAYERS_NUM];
    int player_cards_before_buy [PLAYERS_NUM];
    for(int i = 0; i < PLAYERS_NUM; i++){
        played_games_before_buy[i] = world_cup.num_played_games_for_player(i + 1).ans();
        player_cards_before_buy[i] = world_cup.get_player_cards(i + 1).ans();
    }


    world_cup.buy_team(1,2);
    if (world_cup.get_partial_spirit(11).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 11");
    if (world_cup.get_partial_spirit(12).ans() != p12)
        throw std::runtime_error(error_massage + "player 12");
    if (world_cup.get_partial_spirit(13).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 13");

    if (world_cup.get_partial_spirit(21).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 21");
    if (world_cup.get_partial_spirit(22).ans() != p12 * p13 * p22)
        throw std::runtime_error(error_massage + "player 22");
    if (world_cup.get_partial_spirit(23).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 23");

    world_cup.buy_team(1,3);
    if (world_cup.get_partial_spirit(31).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 31");
    if (world_cup.get_partial_spirit(32).ans() != p12 * p13 * p22 * p23 * p32)
        throw std::runtime_error(error_massage + "player 32");
    if (world_cup.get_partial_spirit(33).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 33");

    world_cup.buy_team(5,6);
    if (world_cup.get_partial_spirit(51).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    world_cup.buy_team(4,5);
    if (world_cup.get_partial_spirit(41).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 41");
    if (world_cup.get_partial_spirit(42).ans() != p42)
        throw std::runtime_error(error_massage + "player 42");
    if (world_cup.get_partial_spirit(43).ans() != p42 * p43)
        throw std::runtime_error(error_massage + "player 43");

    if (world_cup.get_partial_spirit(51).ans() != p42 * p43)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p42 * p43 * p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p42 * p43 * p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    world_cup.buy_team(7,8);
    if (world_cup.get_partial_spirit(71).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 71");
    if (world_cup.get_partial_spirit(72).ans() != p72)
        throw std::runtime_error(error_massage + "player 72");
    if (world_cup.get_partial_spirit(73).ans() != p72 * p73)
        throw std::runtime_error(error_massage + "player 73");

    if (world_cup.get_partial_spirit(81).ans() != p72 * p73)
        throw std::runtime_error(error_massage + "player 81");
    if (world_cup.get_partial_spirit(82).ans() != p72 * p73 * p82)
        throw std::runtime_error(error_massage + "player 82");
    if (world_cup.get_partial_spirit(83).ans() != p72 * p73 * p82 * p83)
        throw std::runtime_error(error_massage + "player 83");

    world_cup.buy_team(4,7);
    if (world_cup.get_partial_spirit(41).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 41");
    if (world_cup.get_partial_spirit(42).ans() != p42)
        throw std::runtime_error(error_massage + "player 42");
    if (world_cup.get_partial_spirit(43).ans() != p42 * p43)
        throw std::runtime_error(error_massage + "player 43");

    if (world_cup.get_partial_spirit(51).ans() != p42 * p43)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p42 * p43 * p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p42 * p43 * p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    if (world_cup.get_partial_spirit(71).ans() != p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 71");
    if (world_cup.get_partial_spirit(72).ans() != p42 * p43 * p52 * p53 * p62 * p63 * p72)
        throw std::runtime_error(error_massage + "player 72");
    if (world_cup.get_partial_spirit(73).ans() != p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 73");

    if (world_cup.get_partial_spirit(81).ans() != p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 81");
    if (world_cup.get_partial_spirit(82).ans() != p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82)
        throw std::runtime_error(error_massage + "player 82");
    if (world_cup.get_partial_spirit(83).ans() != p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82 * p83)
        throw std::runtime_error(error_massage + "player 83");

    world_cup.buy_team(1,4);

    if (world_cup.get_partial_spirit(11).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 11");
    if (world_cup.get_partial_spirit(12).ans() != p12)
        throw std::runtime_error(error_massage + "player 12");
    if (world_cup.get_partial_spirit(13).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 13");

    if (world_cup.get_partial_spirit(21).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 21");
    if (world_cup.get_partial_spirit(22).ans() != p12 * p13 * p22)
        throw std::runtime_error(error_massage + "player 22");
    if (world_cup.get_partial_spirit(23).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 23");

    if (world_cup.get_partial_spirit(31).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 31");
    if (world_cup.get_partial_spirit(32).ans() != p12 * p13 * p22 * p23 * p32)
        throw std::runtime_error(error_massage + "player 32");
    if (world_cup.get_partial_spirit(33).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 33");

    if (world_cup.get_partial_spirit(41).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 41");
    if (world_cup.get_partial_spirit(42).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42)
        throw std::runtime_error(error_massage + "player 42");
    if (world_cup.get_partial_spirit(43).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 43");

    if (world_cup.get_partial_spirit(51).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    if (world_cup.get_partial_spirit(71).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 71");
    if (world_cup.get_partial_spirit(72).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72)
        throw std::runtime_error(error_massage + "player 72");
    if (world_cup.get_partial_spirit(73).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 73");

    if (world_cup.get_partial_spirit(81).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 81");
    if (world_cup.get_partial_spirit(82).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82)
        throw std::runtime_error(error_massage + "player 82");
    if (world_cup.get_partial_spirit(83).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82 * p83)
        throw std::runtime_error(error_massage + "player 83");


    int team1_new_points = 0;
    for(int i = 0; i < TEAMS_NUM; i++){
        team1_new_points += team_points_before_buy[i];
    }
    if (team1_new_points != world_cup.get_team_points(1).ans())
        throw std::runtime_error(error_massage + "team_points_before_buy has changed");



    for(int i = 0; i < PLAYERS_NUM; i++){
        if(played_games_before_buy[i] != world_cup.num_played_games_for_player(i + 1).ans())
            throw std::runtime_error(error_massage + "played_games_before_buy has changed");

        if(player_cards_before_buy[i] != world_cup.get_player_cards(i + 1).ans())
            throw std::runtime_error(error_massage + "player_cards_before_buy has changed");
    }


    std::cout << "Pass buy_team test1" << std::endl;
}



void buy_team_test2(){

    std::string error_massage = "error in buy_team test2: ";
    world_cup_t world_cup;

    world_cup.add_team(1);
    permutation_t p_ident = permutation_t::neutral();
    world_cup.add_player(11, 1, p_ident, 4,
                         3, 2, true);
    int a12[] = {2,1,3,0,4};
    permutation_t p12 = permutation_t(a12);
    world_cup.add_player(12, 1, p12, 4,
                         3, 2, false);
    int a13[] = {3,1,2,0,4};
    permutation_t p13 = permutation_t(a13);
    world_cup.add_player(13, 1, p13, 4,
                         3, 2, false);




    world_cup.add_team(2);

    world_cup.add_player(21, 2, p_ident, 4,
                         3, 2, true);
    int a22[] = {1,3,2,4,0};
    permutation_t p22 = permutation_t(a22);
    world_cup.add_player(22, 2, p22, 4,
                         3, 2, false);
    int a23[] = {2,3,1,4,0};
    permutation_t p23 = permutation_t(a23);
    world_cup.add_player(23, 2, p23, 4,
                         3, 2, false);

    world_cup.add_team(3);
    world_cup.add_player(31, 3, p_ident, 4,
                         3, 2, false);
    int a32[] = {1,3,2,0,4};
    permutation_t p32 = permutation_t(a32);
    world_cup.add_player(32, 3, p32, 4,
                         3, 2, false);
    int a33[] = {1,3,2,0,4};
    permutation_t p33 = permutation_t(a33);
    world_cup.add_player(33, 3, p33, 4,
                         3, 2, false);

    world_cup.add_team(4);
    world_cup.add_player(41, 4, p_ident, 4,
                         3, 2, true);
    permutation_t p42 = permutation_t::read("3,4,2,1,5");
    world_cup.add_player(42, 4, p42, 4,
                         3, 2, false);
    permutation_t p43 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(43,4,p43,4,
                         4,2,false);

    world_cup.add_team(5);
    world_cup.add_player(51, 5, p_ident, 4,
                         3, 2, true);
    permutation_t p52 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(52, 5, p52, 4,
                         3, 2, false);
    permutation_t p53 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(53, 5, p53, 4,
                         3, 2, false);

    world_cup.add_team(6);
    world_cup.add_player(61, 6, p_ident, 4,
                         3, 2, true);
    permutation_t p62 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(62, 6, p62, 4,
                         3, 2, false);
    permutation_t p63 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(63, 6, p63, 4,
                         3, 2, false);

    world_cup.add_team(7);
    world_cup.add_player(71, 7, p_ident, 4,
                         3, 2, true);
    permutation_t p72 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(72, 7, p72, 4,
                         3, 2, false);
    permutation_t p73 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(73, 7, p73, 4,
                         3, 2, false);

    world_cup.add_team(8);
    world_cup.add_player(81, 8, p_ident, 4,
                         3, 2, true);
    permutation_t p82 = permutation_t::read("1,3,5,2,4");
    world_cup.add_player(82, 8, p82, 4,
                         3, 2, false);
    permutation_t p83 = permutation_t::read("4,3,1,2,5");
    world_cup.add_player(83, 8, p83, 4,
                         3, 2, false);


    world_cup.buy_team(1,2);
    world_cup.buy_team(1,3);

    world_cup.buy_team(5,6);
    world_cup.buy_team(4,5);
    world_cup.buy_team(7,8);
    world_cup.buy_team(4,7);

    world_cup.buy_team(1,4);

    if (world_cup.get_partial_spirit(11).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 11");
    if (world_cup.get_partial_spirit(12).ans() != p12)
        throw std::runtime_error(error_massage + "player 12");
    if (world_cup.get_partial_spirit(13).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 13");

    if (world_cup.get_partial_spirit(21).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 21");
    if (world_cup.get_partial_spirit(22).ans() != p12 * p13 * p22)
        throw std::runtime_error(error_massage + "player 22");
    if (world_cup.get_partial_spirit(23).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 23");

    if (world_cup.get_partial_spirit(31).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 31");
    if (world_cup.get_partial_spirit(32).ans() != p12 * p13 * p22 * p23 * p32)
        throw std::runtime_error(error_massage + "player 32");
    if (world_cup.get_partial_spirit(33).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 33");

    if (world_cup.get_partial_spirit(41).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 41");
    if (world_cup.get_partial_spirit(42).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42)
        throw std::runtime_error(error_massage + "player 42");
    if (world_cup.get_partial_spirit(43).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 43");

    if (world_cup.get_partial_spirit(51).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    if (world_cup.get_partial_spirit(71).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 71");
    if (world_cup.get_partial_spirit(72).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72)
        throw std::runtime_error(error_massage + "player 72");
    if (world_cup.get_partial_spirit(73).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 73");

    if (world_cup.get_partial_spirit(81).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 81");
    if (world_cup.get_partial_spirit(82).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82)
        throw std::runtime_error(error_massage + "player 82");
    if (world_cup.get_partial_spirit(83).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82 * p83)
        throw std::runtime_error(error_massage + "player 83");


    std::cout << "Pass buy_team test2" << std::endl;
}


void buy_team_test3(){

    std::string error_massage = "error in buy_team test3: ";
    world_cup_t world_cup;

    world_cup.add_team(1);
    permutation_t p_ident = permutation_t::neutral();
    world_cup.add_player(11, 1, p_ident, 4,
                         3, 2, true);
    int a12[] = {2,1,3,0,4};
    permutation_t p12 = permutation_t(a12);
    world_cup.add_player(12, 1, p12, 4,
                         3, 2, false);
    int a13[] = {3,1,2,0,4};
    permutation_t p13 = permutation_t(a13);
    world_cup.add_player(13, 1, p13, 4,
                         3, 2, false);




    world_cup.add_team(2);

    world_cup.add_player(21, 2, p_ident, 4,
                         3, 2, true);
    int a22[] = {1,3,2,4,0};
    permutation_t p22 = permutation_t(a22);
    world_cup.add_player(22, 2, p22, 4,
                         3, 2, false);
    int a23[] = {2,3,1,4,0};
    permutation_t p23 = permutation_t(a23);
    world_cup.add_player(23, 2, p23, 4,
                         3, 2, false);

    world_cup.add_team(3);
    world_cup.add_player(31, 3, p_ident, 4,
                         3, 2, false);
    int a32[] = {1,3,2,0,4};
    permutation_t p32 = permutation_t(a32);
    world_cup.add_player(32, 3, p32, 4,
                         3, 2, false);
    int a33[] = {1,3,2,0,4};
    permutation_t p33 = permutation_t(a33);
    world_cup.add_player(33, 3, p33, 4,
                         3, 2, false);

    world_cup.add_team(4);
    world_cup.add_player(41, 4, p_ident, 4,
                         3, 2, true);
    permutation_t p42 = permutation_t::read("3,4,2,1,5");
    world_cup.add_player(42, 4, p42, 4,
                         3, 2, false);
    permutation_t p43 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(43,4,p43,4,
                         4,2,false);

    world_cup.add_team(5);
    world_cup.add_player(51, 5, p_ident, 4,
                         3, 2, true);
    permutation_t p52 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(52, 5, p52, 4,
                         3, 2, false);
    permutation_t p53 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(53, 5, p53, 4,
                         3, 2, false);

    world_cup.add_team(6);
    world_cup.add_player(61, 6, p_ident, 4,
                         3, 2, true);
    permutation_t p62 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(62, 6, p62, 4,
                         3, 2, false);
    permutation_t p63 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(63, 6, p63, 4,
                         3, 2, false);

    world_cup.add_team(7);
    world_cup.add_player(71, 7, p_ident, 4,
                         3, 2, true);
    permutation_t p72 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(72, 7, p72, 4,
                         3, 2, false);
    permutation_t p73 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(73, 7, p73, 4,
                         3, 2, false);

    world_cup.add_team(8);
    world_cup.add_player(81, 8, p_ident, 4,
                         3, 2, true);
    permutation_t p82 = permutation_t::read("1,3,5,2,4");
    world_cup.add_player(82, 8, p82, 4,
                         3, 2, false);
    permutation_t p83 = permutation_t::read("4,3,1,2,5");
    world_cup.add_player(83, 8, p83, 4,
                         3, 2, false);


    world_cup.play_match(1,2);
    world_cup.play_match(1,4);
    world_cup.play_match(4,1);
    world_cup.play_match(1,4);
    world_cup.play_match(2,7);
    world_cup.play_match(3,8);
    world_cup.play_match(7,8);
    world_cup.play_match(7,8);
    world_cup.play_match(7,8);
    world_cup.buy_team(7,8);
    world_cup.buy_team(6,7);
    world_cup.buy_team(5,6);
    world_cup.buy_team(4,5);
    world_cup.buy_team(3,4);
    world_cup.buy_team(2,3);
    world_cup.buy_team(1,2);

    if (world_cup.get_partial_spirit(11).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 11");
    if (world_cup.get_partial_spirit(12).ans() != p12)
        throw std::runtime_error(error_massage + "player 12");
    if (world_cup.get_partial_spirit(13).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 13");

    if (world_cup.get_partial_spirit(21).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 21");
    if (world_cup.get_partial_spirit(22).ans() != p12 * p13 * p22)
        throw std::runtime_error(error_massage + "player 22");
    if (world_cup.get_partial_spirit(23).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 23");

    if (world_cup.get_partial_spirit(31).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 31");
    if (world_cup.get_partial_spirit(32).ans() != p12 * p13 * p22 * p23 * p32)
        throw std::runtime_error(error_massage + "player 32");
    if (world_cup.get_partial_spirit(33).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 33");

    if (world_cup.get_partial_spirit(41).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 41");
    if (world_cup.get_partial_spirit(42).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42)
        throw std::runtime_error(error_massage + "player 42");
    if (world_cup.get_partial_spirit(43).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 43");

    if (world_cup.get_partial_spirit(51).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    if (world_cup.get_partial_spirit(71).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 71");
    if (world_cup.get_partial_spirit(72).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72)
        throw std::runtime_error(error_massage + "player 72");
    if (world_cup.get_partial_spirit(73).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 73");

    if (world_cup.get_partial_spirit(81).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 81");
    if (world_cup.get_partial_spirit(82).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82)
        throw std::runtime_error(error_massage + "player 82");
    if (world_cup.get_partial_spirit(83).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82 * p83)
        throw std::runtime_error(error_massage + "player 83");


    std::cout << "Pass buy_team test3" << std::endl;
}



void buy_team_test4(){

    std::string error_massage = "error in buy_team test4: ";
    world_cup_t world_cup;

    world_cup.add_team(1);
    permutation_t p_ident = permutation_t::neutral();
    world_cup.add_player(11, 1, p_ident, 4,
                         3, 2, true);
    int a12[] = {2,1,3,0,4};
    permutation_t p12 = permutation_t(a12);
    world_cup.add_player(12, 1, p12, 4,
                         3, 2, false);
    int a13[] = {3,1,2,0,4};
    permutation_t p13 = permutation_t(a13);
    world_cup.add_player(13, 1, p13, 4,
                         3, 2, false);


    world_cup.add_team(2);

    world_cup.add_player(21, 2, p_ident, 4,
                         3, 2, true);
    int a22[] = {1,3,2,4,0};
    permutation_t p22 = permutation_t(a22);
    world_cup.add_player(22, 2, p22, 4,
                         3, 2, false);
    int a23[] = {2,3,1,4,0};
    permutation_t p23 = permutation_t(a23);
    world_cup.add_player(23, 2, p23, 4,
                         3, 2, false);


    world_cup.add_team(3);
    world_cup.add_player(31, 3, p_ident, 4,
                         3, 2, false);
    int a32[] = {1,3,2,0,4};
    permutation_t p32 = permutation_t(a32);
    world_cup.add_player(32, 3, p32, 4,
                         3, 2, false);
    int a33[] = {1,3,2,0,4};
    permutation_t p33 = permutation_t(a33);
    world_cup.add_player(33, 3, p33, 4,
                         3, 2, false);


    world_cup.add_team(4);
    world_cup.add_player(41, 4, p_ident, 4,
                         3, 2, true);
    permutation_t p42 = permutation_t::read("3,4,2,1,5");
    world_cup.add_player(42, 4, p42, 4,
                         3, 2, false);
    permutation_t p43 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(43,4,p43,4,
                         4,2,false);


    world_cup.add_team(5);
    world_cup.add_player(51, 5, p_ident, 4,
                         3, 2, true);
    permutation_t p52 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(52, 5, p52, 4,
                         3, 2, false);
    permutation_t p53 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(53, 5, p53, 4,
                         3, 2, false);


    world_cup.add_team(6);
    world_cup.add_player(61, 6, p_ident, 4,
                         3, 2, true);
    permutation_t p62 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(62, 6, p62, 4,
                         3, 2, false);
    permutation_t p63 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(63, 6, p63, 4,
                         3, 2, false);


    world_cup.add_team(7);
    world_cup.add_player(71, 7, p_ident, 4,
                         3, 2, true);
    permutation_t p72 = permutation_t::read("5,3,2,1,4");
    world_cup.add_player(72, 7, p72, 4,
                         3, 2, false);
    permutation_t p73 = permutation_t::read("5,3,1,2,4");
    world_cup.add_player(73, 7, p73, 4,
                         3, 2, false);


    world_cup.add_team(8);
    world_cup.add_player(81, 8, p_ident, 4,
                         3, 2, true);
    permutation_t p82 = permutation_t::read("1,3,5,2,4");
    world_cup.add_player(82, 8, p82, 4,
                         3, 2, false);
    permutation_t p83 = permutation_t::read("4,3,1,2,5");
    world_cup.add_player(83, 8, p83, 4,
                         3, 2, false);


    world_cup.play_match(1,2);
    world_cup.play_match(1,4);
    world_cup.play_match(4,1);
    world_cup.play_match(1,4);
    world_cup.play_match(2,7);
    world_cup.play_match(3,8);
    world_cup.play_match(7,8);
    world_cup.play_match(7,8);
    world_cup.play_match(7,8);
    world_cup.play_match(1,2);
    world_cup.play_match(1,4);
    world_cup.play_match(4,1);
    world_cup.play_match(1,4);
    world_cup.play_match(4,1);
    world_cup.play_match(5,6);
    world_cup.play_match(6,7);
    world_cup.play_match(6,5);
    world_cup.play_match(7,8);


    int TEAMS_NUM = 8;
    int PLAYERS_NUM = 24;
    int player_ids [] = {11,12,13,21,22,23,31,32,33,41,42,43,51,52,53,61,62,63,71,72,73,81,82,83};

    int team_points_before_buy [TEAMS_NUM];
    for(int i = 0; i < TEAMS_NUM; i++){
        team_points_before_buy[i] = world_cup.get_team_points(i + 1).ans();
    }

    int played_games_before_buy [PLAYERS_NUM];
    int player_cards_before_buy [PLAYERS_NUM];
    for(int i = 0; i < PLAYERS_NUM; i++){
        played_games_before_buy[i] = world_cup.num_played_games_for_player(i + 1).ans();
        player_cards_before_buy[i] = world_cup.get_player_cards(i + 1).ans();
    }


    world_cup.buy_team(1,2);
    world_cup.buy_team(1,3);
    world_cup.buy_team(5,6);
    world_cup.buy_team(4,5);
    world_cup.buy_team(7,8);
    world_cup.buy_team(4,7);
    world_cup.buy_team(1,4);


    int team1_new_points = 0;
    for(int i = 0; i < TEAMS_NUM; i++){
        team1_new_points += team_points_before_buy[i];
    }
    if (team1_new_points != world_cup.get_team_points(1).ans())
        throw std::runtime_error(error_massage + "team_points_before_buy has changed");


    for(int i = 0; i < PLAYERS_NUM; i++){
        if(played_games_before_buy[i] != world_cup.num_played_games_for_player(i + 1).ans())
            throw std::runtime_error(error_massage + "played_games_before_buy has changed");

        if(player_cards_before_buy[i] != world_cup.get_player_cards(i + 1).ans())
            throw std::runtime_error(error_massage + "player_cards_before_buy has changed");
    }

    if (world_cup.get_partial_spirit(11).ans() != p_ident)
        throw std::runtime_error(error_massage + "player 11");
    if (world_cup.get_partial_spirit(12).ans() != p12)
        throw std::runtime_error(error_massage + "player 12");
    if (world_cup.get_partial_spirit(13).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 13");

    if (world_cup.get_partial_spirit(21).ans() != p12 * p13)
        throw std::runtime_error(error_massage + "player 21");
    if (world_cup.get_partial_spirit(22).ans() != p12 * p13 * p22)
        throw std::runtime_error(error_massage + "player 22");
    if (world_cup.get_partial_spirit(23).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 23");

    if (world_cup.get_partial_spirit(31).ans() != p12 * p13 * p22 * p23)
        throw std::runtime_error(error_massage + "player 31");
    if (world_cup.get_partial_spirit(32).ans() != p12 * p13 * p22 * p23 * p32)
        throw std::runtime_error(error_massage + "player 32");
    if (world_cup.get_partial_spirit(33).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 33");

    if (world_cup.get_partial_spirit(41).ans() != p12 * p13 * p22 * p23 * p32 * p33)
        throw std::runtime_error(error_massage + "player 41");
    if (world_cup.get_partial_spirit(42).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42)
        throw std::runtime_error(error_massage + "player 42");
    if (world_cup.get_partial_spirit(43).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 43");

    if (world_cup.get_partial_spirit(51).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43)
        throw std::runtime_error(error_massage + "player 51");
    if (world_cup.get_partial_spirit(52).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52)
        throw std::runtime_error(error_massage + "player 52");
    if (world_cup.get_partial_spirit(53).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 53");

    if (world_cup.get_partial_spirit(61).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53)
        throw std::runtime_error(error_massage + "player 61");
    if (world_cup.get_partial_spirit(62).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62)
        throw std::runtime_error(error_massage + "player 62");
    if (world_cup.get_partial_spirit(63).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 63");

    if (world_cup.get_partial_spirit(71).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63)
        throw std::runtime_error(error_massage + "player 71");
    if (world_cup.get_partial_spirit(72).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72)
        throw std::runtime_error(error_massage + "player 72");
    if (world_cup.get_partial_spirit(73).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 73");

    if (world_cup.get_partial_spirit(81).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73)
        throw std::runtime_error(error_massage + "player 81");
    if (world_cup.get_partial_spirit(82).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82)
        throw std::runtime_error(error_massage + "player 82");
    if (world_cup.get_partial_spirit(83).ans() != p12 * p13 * p22 * p23 * p32 * p33 * p42 * p43 * p52 * p53 * p62 * p63 * p72 * p73 * p82 * p83)
        throw std::runtime_error(error_massage + "player 83");





    std::cout << "Pass buy_team test4" << std::endl;
}


#endif //DATASTRUCTUREWET2_WORLDCUPTESTS_H
