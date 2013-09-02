Aplicação Distribúida para Cadastro de Espécies de Animais.
=====

Protocolo v1.1
=====

Compilação:

	- Para que seja possível a compilação da aplicação, é necessário que haja
	a biblioteca libboost versão 1.49 ou acima. Caso não tenha a biblioteca, insira 
	na linha de comando: ~$ make install-boost

Execução do Servidor:
	
	- As possíveis portas para os servidores são, 8870, 8871 e 8872
	- Ao executar o sevidor deve-se passar por argumento o número da porta.

Cadastro de espécie x: 
  - cadastrar?id=x&nomeCientifico=nome&nomePopular=nome2&breveDesc=É feito pra burro
  - Possíveis respostas:

Já existe:
    - status?v=0

Com sucesso:
    - status?v=1

Buscar espécie x:
  - buscar?id=x
  - Possíveis respostas:

Já cadastrado:
    - status?v=0

Com sucesso:
    - resultado?v=1&nomeCientifico=nome&nomePopular=nome2&breveDesc=É feito pra burro

Remover espécie x:
  - remover?id=x
