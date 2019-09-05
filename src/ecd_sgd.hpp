

class ECD_SGD {
public:
    ECD_SGD();
    void run();
    void run_batch();

private:
    int world_size;
    int world_rank;
}
