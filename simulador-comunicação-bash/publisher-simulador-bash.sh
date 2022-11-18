#!/bin/bash

#atualização do serviço toda vez que o inicia, por segurança
function atualizacao(){
sudo apt-get update
sudo apt-get upgrade
sudo apt install mosquitto
}


atualizacao

printf "Digite o tópico: "
printf ""
read topico


#inicia o serviço
sudo service mosquitto start

function mosquitto_pub(){

#laço que vai computar 400 vezes o código
    for i in $(seq 1 400);
        do
                sudo mosquitto_pub -h test.mosquitto.org -p 1883  -t topico -m "mensagem-topico1-teste" #a mensagem vai ser a mesma
        done
}
#chamada da função
mosquitto_pub


