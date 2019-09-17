#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include "data_manager.hpp"
#include "dcd_psgd.hpp"
#include "ecd_psgd.hpp"

/* mpirun -n threads main file_name [iterations] [learning_rate] [verbose] */
/* mpirun -n 4 main real-sim 1000 0.01 True */
int main(int argc, char *argv[]) {
    int iterations = 1000;
    double learning_rate = 0.1;
    std::ifstream fp;

    /* Setup parameters. */
    if (argc < 2) {
        std::cout << "Usage: mpirun -n threads main file_name iterations"
            " learning_rate [verbose]" << std::endl;
        return 0;
    }
    if (argc > 2) {
        std::istringstream iterations_stream(argv[2]);
        iterations_stream >> iterations;
    }
    if (argc > 3) {
        std::istringstream learning_rate_stream(argv[3]);
        learning_rate_stream >> learning_rate;
    }

    /* Initialize the model. */
    fp.open(argv[1]);
    DataManager dm(fp);
    fp.close();
    ECD_PSGD model(&dm, learning_rate);

    /* Train the model. */
    if (argc > 4) {
        model.train(iterations, true);
    } else {
        model.train(iterations, false);
    }

    return 0;
}
