S.O.S
=====

Protocolo v1.1
=====

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
