#include "../include/agent.h"
#include <algorithm>

Agent::Agent() {
    x = 0;
    y = 0;
    actions = new int[4] {0, 1, 2, 3}; // UP, DOWN, LEFT. RIGHT
    action_count = 4;
}

int Agent::get_action_count() { return action_count; }

int Agent::get_x() { return x; }
int Agent::get_y() { return y; }

void Agent::set_x(int new_x) { x = new_x; }
void Agent::set_y(int new_y) { y = new_y; }

void Agent::take_action(int action) {

    if (action == actions[0]) { // UP
        y = std::min(y + 1, 4);

    } else if (action == actions[1]) { // DOWN
        y = std::max(y - 1, 0);

    } else if (action == actions[2]) { // LEFT
        x = std::max(x - 1, 0);

    } else { // RIGHT
        x = std::min(x + 1, 4);

    }

}

