#include "../include/env.h"
#include <iostream>
#include <ctime>

Env::Env() {

    initialize_q_table();
    initialize_reward_table();
    initialize_world();

}

void Env::initialize_q_table() {

    for (int s = 0; s < world_size; s++) {
        for (int a = 0; a < agent.get_action_count(); a++) {

            q_table[s][a] = 0.0F;

        }
    }

}

void Env::initialize_reward_table() {

    reward_table[0] = -1;
    reward_table[1] =  3; 
    reward_table[2] = -5;
    reward_table[3] = 10; 

}

void Env::initialize_world() {

    for (int i = 0; i < world_size; i++) {
        world[i] = base_world[i];
    }

}

void Env::reset() {

    steps = 50;
    initialize_world();
    done = false;
    agent.set_x(rand() % 5);
    agent.set_y(rand() % 5);

}

void Env::step(int action) {

    steps--;
    agent.take_action(action);

}

int Env::evaluate_state(int state) {

    return reward_table[base_world[state]];

}

void Env::train_agent() {
    
    srand(time(NULL));

    const int TOTAL_EPISODES = 1000000;

    const float alpha = 0.1F;
    const float gamma = 0.9F;

    const int agent_action_count = agent.get_action_count();
    int action;

    for (int i = 0; i < TOTAL_EPISODES; i++) {

        reset();
        action = rand() % agent.get_action_count();

        while (!done) {

            int current_x = agent.get_x();
            int current_y = agent.get_y();
            int current_state = current_y * 5 + current_x;

            step(action);

            int new_x = agent.get_x();
            int new_y = agent.get_y();
            int new_state = new_y * 5 + new_x;

            int reward = evaluate_state(current_state);

            // Bellman Equation
            // Q(s,a) <= Q(s,a) + a * (R(s,a) + y * maxQ(s',a) - Q(s,a))

            float max_q_val = q_table[new_state][0];
            int next_action = 0;

            for (int a = 1; a < agent_action_count; a++) {
                int q_val = q_table[new_state][a];
                if (max_q_val < q_val) {
                    max_q_val = q_val;
                    next_action = a;
                }
            }

            q_table[current_state][action] += // Q(s,a) <= Q(s,a) +
                                             alpha * // a
                                            (
                                             reward + // R(s,a)
                                             gamma * max_q_val // y * maxQ(s',a)
                                             - q_table[current_state][action] // Q(s,a)
                                            );

            if (world[current_state] == 1) { world[current_state] = 0; }

            action = next_action;

            if (steps <= 0 || world[current_state] == 3) {
                done = true;
            }

        }

    }

}

void Env::print_q_table() {

    int agent_action_count = agent.get_action_count();

    std::cout << "Q-Table: " << std::endl;
    for (int s = 0; s < world_size; s++) {
        std::cout << "State " << s << ": ";
        for (int a = 0; a < agent_action_count; a++) {
            std::cout << a << "= " << q_table[s][a] << "  ";

        }
        std::cout << std::endl;
    }

}

void Env::print_best_action() {

    int best[25];
    float max_q;
    float q;

    int action_count = agent.get_action_count();

    for (int s = 0; s < world_size; s++) {

        max_q = q_table[s][0];
        best[s] = 0;

        for (int a = 1; a < action_count; a++) {

            q = q_table[s][a];
            if (q >= max_q) {
                max_q = q;
                best[s] = a;
            }

        }
        
    }

    int count = 0;
    for (int x : best) {

        if (base_world[count] == 2) {
            std::cout << " #";
            count++;
            continue;
        }

        if (base_world[count] == 3) {
            std::cout << " G";
            count++;
            continue;
        }

        if (x == 0) { std::cout << " v"; }
        if (x == 1) { std::cout << " ^"; }
        if (x == 2) { std::cout << " <"; }
        if (x == 3) { std::cout << " >"; }

        count++;

        if (count % 5 == 0) std::cout << std::endl;

    }

}
