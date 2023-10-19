#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define m       30
#define n       30
#define Ntime   200
#define dt      0.01
#define dx      0.1
#define D       0.1

void KhoiTao(float *T)
{
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (i >= (m / 2 - 5) && i < (m / 2 + 5) && j >= (n / 2 - 5) && j < (n / 2 + 5))
                *(T + i * n + j) = 80.0;
            else
                *(T + i * n + j) = 25.0;
        }
    }
}

void FD(float *T, float *new_T, int start_row, int end_row)
{
    int i, j;
    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < n; j++) {
            float c = *(T + i * n + j);
            float l = (j == 0) ? c : *(T + i * n + (j - 1));
            float r = (j == n - 1) ? c : *(T + i * n + (j + 1));
            float u = (i == 0) ? c : *(T + (i - 1) * n + j);
            float d = (i == m - 1) ? c : *(T + (i + 1) * n + j);
            float laplacian = (l + r + u + d - 4 * c) / (dx * dx);
            float dT = D * laplacian * dt;
            *(new_T + i * n + j) = c + dT;
        }
    }
}

int main(int argc, char *argv[])
{
    int NP, ID;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &NP);
    MPI_Comm_rank(MPI_COMM_WORLD, &ID);

    int rows_per_process = m / NP;
    int start_row = ID * rows_per_process;
    int end_row = (ID == NP - 1) ? m : (start_row + rows_per_process);

    float *T, *new_T;
    T = (float *)malloc(m * n * sizeof(float));
    new_T = (float *)malloc(m * n * sizeof(float));

    KhoiTao(T);

    int t;
    for (t = 0; t < Ntime; t++) {
        FD(T, new_T, start_row, end_row);
        MPI_Allgather(new_T + start_row * n, rows_per_process * n, MPI_FLOAT, T, rows_per_process * n, MPI_FLOAT, MPI_COMM_WORLD);
    }

    if (ID == 0) {
    FILE *result_file = fopen("result.txt", "w");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%.2f\t", *(T + i * n + j));
                fprintf(result_file, "%.2f\t", *(T + i * n + j));
            }
            printf("\n");
            fprintf(result_file, "\n");
        }
        fclose(result_file);
    }

    free(T);
    free(new_T);

    MPI_Finalize();

    return 0;
}

