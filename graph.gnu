set terminal png size 800,600 
set output 'out.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (sec)'
set title 'Matrix multiplication speed on Wlofgang Cluster'
plot "data.txt" using 1:2 title 'w/P' with linespoint, "data.txt" using 1:3 title 'SIMD' with linespoint, "data.txt" using 1:4 title 'OpenMP' with linespoint, "data.txt" using 1:5 title 'MPI' with linespoint
