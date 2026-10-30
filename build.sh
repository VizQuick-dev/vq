echo "== [ Built libvq.a ] =="

gcc vqmain/main.c -o vq -lvq
echo "== [ Compiled vq ] =="
gcc show/main.c -o vqshow -lvq
echo "== [ Compiled vqshow ] == "
gcc term/main.c -o vqterm -lvq
echo "== [ Compiled vqterm ] == "
gcc test/main.c parse/*.c lib/*/*.c vq.c -o vqtest -g -I. -lz -DENABLE_LOG
echo "== [ Compiled vqtest ] == "
