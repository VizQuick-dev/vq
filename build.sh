echo "== [ Built libvq.a ] =="

gcc vqmain/main.c parse/*.c lib/*/*.c -o vq -lz -I.
echo "== [ Compiled vq ] =="
gcc show/main.c parse/*.c lib/*/*.c -o vqshow -lz -I.
echo "== [ Compiled vqshow ] == "
gcc term/main.c parse/*.c lib/*/*.c -o vqterm -lz -I.
echo "== [ Compiled vqterm ] == "
