# modules needed for running the script on MareNostrum 4 (CTE-AMD)
# module load anaconda
# source activate gem5


export CC=clang
export CXX=clang++

rm -r build

mkdir build
cd build
cmake ..
make -j64




