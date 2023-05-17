#include "env.cpp"

int main() {

    Env env;
    env.print_q_table();
    env.train_agent();
    env.print_q_table();
    env.print_best_action();

    return 0;
}