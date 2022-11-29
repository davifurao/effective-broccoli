#!/bin/bash

#ainda está em fase de testes

pp= python3 --version

if [$pp == "python 3.10.6"]; then 
    echo "está instalado"
else 
    echo "nao passou pelo laço"

fi


#O bash está com erro de sintaxe, mas o objetivo é verificar se o python3, paho e mosquitto estão instalados. E caso contrário, instalá-los