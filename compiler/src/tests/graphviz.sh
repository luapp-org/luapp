cd src

[ $1 = "-parser" ]; bin/luappc -s parser -o dot/$2.dot
[ $1 = "-type" ]; bin/luappc -s parser -o dot/$2.dot
dot -Tpng dot/$2.dot > dot/$2.png
