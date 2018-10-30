#ifndef GRIDCELL_H_
#define GRIDCELL_H_
class gridcell {
    private:int x; 
            int y;
            unsigned char state;
            unsigned char* neighborhood;
    public: gridcell(void); 
            ~gridcell();
            void set_state(unsigned char ch);
            unsigned char get_state(); 
            unsigned char* get_neighborhood();
            void set_x(int X);
            void set_y(int Y);
            void set_neighborhood(unsigned char n_in[]); 
            int count_live_neighbors();  
            friend std::ostream& operator << (std::ostream& os, gridcell& cell);

};
#endif