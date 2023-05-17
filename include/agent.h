
class Agent {

    private:
        int x;
        int y;
        const int* actions;
        int action_count;

    public:

        Agent();

        int get_action_count();
        
        int get_x();
        int get_y();

        void set_x(int new_x);
        void set_y(int new_y);

        void take_action(int action);

};