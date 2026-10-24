echo "== [ Built libvq.a ] =="

gcc vqmain/main.c -o vq -lvq
echo "== [ Compiled vq ] =="
gcc show/main.c -o vqshow -lvq
echo "== [ Compiled vqshow ] == "
gcc term/main.c -o vqterm -lvq
echo "== [ Compiled vqterm ] == "
