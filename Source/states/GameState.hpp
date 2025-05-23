class GameState {
public:
    virtual ~GameState() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual GameState* GetNextState() = 0;
    virtual bool ShouldExit() const { return false; }
};