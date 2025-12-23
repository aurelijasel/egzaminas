cmake CmakeLists.txt
cmake --install .
cmake --build .
copy src\*.txt Debug\*.txt
cd Debug\
failo_rusiavimo_programa.exe
pause