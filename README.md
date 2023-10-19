# Heat-Diffusion-2D-MPI
Parallel programming for heat diffusion equation and save result to result.txt
# Install MPI on ubuntu 
`sudo apt install mpich`
# Compile DF2D_MPI_2.c file
`mpicc DF2D_MPI_2.c -o DF2D_MPI_2`
# Run the file with 4 process
`mpirun  -np 4 ./DF2D_MPI_2`
# ![result](https://github.com/imnotwannafire/Heat-Diffusion-2D-MPI/assets/28736776/89c5bbaa-266e-43a3-b1de-43a0d59097fa)
Result
# Run python file to visualize result
`python3 visualize_result.py`
