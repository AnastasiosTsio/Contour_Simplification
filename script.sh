clear
tput setaf 2;cat map.txt;tput setaf 7

read -n 1 -r -p $''
clear
rm ./Image_pbm/*.eps
rm ./Image_pbm/*.contour
make clean
make

read -n 1 -r -p $''
clear
echo "Contenu de Image_pbm avant la creature de nouveaux fichiers"
ls ./Image_pbm

read -n 1 -r -p $''
clear
echo "Execution de test_tache6 avec image_poly" 
./TEST_TACHE6 ./Image_pbm/image2_poly.pbm


read -n 1 -r -p $''
clear
echo "Ouverture du fichier image2_poly.contour"\\n
cat ./Image_pbm/image2_poly.contour

read -n 1 -r -p $''
clear
echo "Execution de test_tache6 avec papillon2" 
./TEST_TACHE6 ./Image_pbm/papillon2.pbm

read -n 1 -r -p $''
clear
echo "Ouverture de papillon2_1.eps"
gv ./Image_pbm/papillon2_1.eps

read -n 1 -r -p $''
clear
echo "Ouverture de papillon2_2.eps"
gv ./Image_pbm/papillon2_2.eps

read -n 1 -r -p $''
clear
echo "Contenu de Image_pbm apres la creature de nouveaux fichiers"
ls ./Image_pbm

read -n 1 -r -p $''
clear
tput setaf 2;cat fini.txt;tput setaf 7

read -n 1 -r -p $''
clear
