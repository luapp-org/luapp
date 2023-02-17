cd src

../../bin/luappc -s parser -o dot/$1.dot
dot -Tpng dot/$1.dot > dot/$1.png
