#! /bin/sh
ls
ls -li file3.txt
ln -s file3.txt file4.txt
ls
cat file3.txt
cat file4.txt
sudo gedit file4.txt
cat file3.txt
cat file4.txt
rm file3.txt
ls
sudo gedit file4.txt
cat file4.txt
ls