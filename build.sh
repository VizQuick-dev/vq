gcc vqmain/main.c parse/*.c lib/pbm/*.c -o vq
echo "== [ Compiled vq ] =="
gcc show/main.c parse/*.c lib/pbm/*.c -o vqshow
echo "== [ Compiled vqshow ] == "
read
