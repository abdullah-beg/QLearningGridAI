#include <map>
#include "../src/agent.cpp"

class Env {

    private:
        const int world_size = 25;
        int world[25];
        const int base_world[25] = {
            0, 0, 0, 0, 0,
            0, 2, 2, 1, 0,
            0, 0, 0, 0, 0,
            0, 1, 2, 2, 0,
            0, 0, 0, 0, 3
        };

        int steps = 25;
        std::map<int, std::map<int, float>> q_table;
        std::map<int, int> reward_table;
        bool done;

        Agent agent;

    public:

        Env();

        void initialize_q_table();
        void initialize_reward_table();
        void initialize_world();

        void reset();
        void step(int action);

        int evaluate_state(int state);

        void train_agent();

        void print_q_table();
        void print_best_action();

};