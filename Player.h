using namespace std;

class Player{

    int score;
    vector <Tile*> Rack;
    bool turn;

    public:
    void setScore(int s);
    int getScore();
    void pushToRack(vector<Tile*> newLetters);
    vector<Tile*> getRackLetters();   
};

