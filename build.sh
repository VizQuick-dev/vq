echo "== [ Built libvq.a ] =="

gcc vqmain/main.c parse/*.c lib/*/*.c -o vq -lz
echo "== [ Compiled vq ] =="
gcc show/main.c parse/*.c lib/*/*.c -o vqshow -lz
echo "== [ Compiled vqshow ] == "
gcc term/main.c parse/*.c lib/*/*.c -o vqterm -lz
echo "== [ Compiled vqterm ] == "
