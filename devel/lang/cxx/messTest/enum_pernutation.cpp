/* show all possible pernutation matrixs of NxN matrix */

#include<cstdio>
#include<vector>
#include<list>
using std::vector;
using std::list;

list<vector<int>> result_matrix;

void show_matrix_spc(const vector<int> & v, int max) {
    for(const auto & elem: v) {
        for(int i = 0; i < max; i++) {
            if(i == elem)
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
    printf("\n");
}

void enum_NxN_pernutation(
        vector<int> & vec,
        const int row,
        const int size) {
    if(row == size) { // end
        result_matrix.push_back(vec);
        return;
    }
    for(int val = 0; val < size; val++) {
        int isOK = true;
        /* traverse all value */
        for(int idx = 0; idx < row; idx++) {
            if(val == vec[idx]) {
                isOK = false;
            }
        }

        if(isOK == false)
            continue;
        else {
            vec[row] = val;
            enum_NxN_pernutation(vec, row + 1, size);
        }
    }
}

int main( int argc, char **argv ) {
    int matrix_size = 4;
    result_matrix.clear();
    vector<int> vec(matrix_size, 0);
    enum_NxN_pernutation(vec, 0, matrix_size);
    int result_index = 0;
    for(const vector<int> & elem : result_matrix) {
        printf("%d: >>\n", result_index++);
        show_matrix_spc(elem, matrix_size);
    }
    return 0;
}
