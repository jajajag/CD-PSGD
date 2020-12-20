import numpy as np
import sys

# python split.py file_name test_proportion(0.1) seed
if __name__ == '__main__':
    file_name = sys.argv[1]
    with open(file_name, 'r') as fp:
        data = fp.readlines()
    test_prop = float(sys.argv[2]) if len(sys.argv) > 2 else 0.1
    seed = int(sys.argv[3]) if len(sys.argv) > 3 else 233

    # Shuffle the indices
    n = len(data)
    indices = [i for i in range(n)]
    np.random.seed(seed)
    np.random.shuffle(indices)
    fence = int(test_prop * n) + 1

    # Split and save the data
    train_data = [data[i] for i in indices[fence:]]
    test_data = [data[i] for i in indices[:fence]]
    with open(file_name + '_train', 'w') as fp:
        fp.writelines(train_data)
    with open(file_name + '_test', 'w') as fp:
        fp.writelines(test_data)
