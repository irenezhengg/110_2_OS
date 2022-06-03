#! /bin/sh
ln file1.txt file2.txt
cat file1.txt
cat file2.txt
sudo gedit file2.txt
cat file1.txt
cat file2.txt
rm file1.txt
ls
strace rm file2.txt