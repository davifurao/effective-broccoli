#!/bin/bash

#ainda está em fase de testes

pp= python3 --version

if [$pp == "python 3.10.6"]; then 
    echo "está instalado"
else 
    echo "nao passou pelo laço"

fi


#O bash está com erro de sintaxe, mas o objetivo é verificar se o python3, paho e mosquitto estão instalados. E caso contrário, instalá-los


#deverá ser construído da seguinte forma: 
#verificar se o python3 está instalado
#verificar se o pip está instalado
#tornar o subscriber executável(com chmod)
#verificar se o selinux está ativado, para verificar se o sistema consegue executar o paho
#iniciar o subscriber em paho(python), iniciando o arquivo da pasta(caminho)




#OBS: Caso dê algum erro, poderei pedir para o sistema dar um git clone do repositório(claro, verificando se o git está instalado anteriormente, talvez por meio do apt)