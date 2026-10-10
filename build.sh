echo "== [ Built libvq.a ] =="

gcc vqmain/main.c parse/*.c lib/*/*.c -o vq
echo "== [ Compiled vq ] =="
gcc show/main.c parse/*.c lib/*/*.c -o vqshow -g
echo "== [ Compiled vqshow ] == "
gcc term/main.c parse/*.c lib/*/*.c -o vqterm
echo "== [ Compiled vqterm ] == "
