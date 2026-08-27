#!/bin/bash

#1
mkdir -p "ice cream 2023/water flavors/"{"Cinnabon","apple","pineapple"} "ice cream 2023/milk flavors/"{"chocolate","cappuccino"}
tree "ice cream 2023"

#2
cat << EOF > color
Azul
EOF
mkdir colors
mv color colors/
cat << EOF >> colors/color
Rojo
EOF

#3
echo "Jose" > name.txt
mkdir "student registry"
cp name.txt "student registry"/
echo "Terlleria" >> "student registry"/name.txt
