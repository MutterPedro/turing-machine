# Maquina de Turing

Trabalho prático da disciplina GCC108 - Teoria da Computação

**Professor:** Ricardo Terra

**Componentes:** 

- André Simões Aranda 10A
- Gabriel da Silva Paiva 10A
- Pedro de Almeida Mutter 10A

Para compilar use:
```sh
gcc trabalhoTeoria.c -o MTU
```

Para executar use:
```sh
./MTU <desc_mt>.txt <palavra para ser testada> <arquivo de saida>.txt
```

Onde a descrição da maquina deve seguir o padrão:
```
(
	{q0,q1,q2,q3,q4,q5,q6}, -> CONJUNTO DE ESTADOS
	{a,b}, -> ALFABETO DA MAQUINA
	{a,b,B,X}, -> ALFABETO DA FITA
	{
		(q0,B)->(q1,B,D), -> TRANSIÇÕES DA FORMA (origem,lido na fita)->(destino,oque sera colocado na fita,sentido em que ira andar)
		(q1,X)->(q1,X,D),
		(q1,a)->(q2,X,D),
		(q1,B)->(q5,B,E),
		(q2,a)->(q2,a,D),
		(q2,X)->(q2,X,D),
		(q2,b)->(q3,X,D),
		(q3,B)->(q4,B,E),
		(q3,b)->(q3,b,D),
		(q4,X)->(q4,X,E),
		(q4,a)->(q4,a,E),
		(q4,b)->(q4,b,E),
		(q4,B)->(q1,B,D),
		(q5,X)->(q5,X,E),
		(q5,B)->(q6,B,N)
	},
	q0, -> estado inicial
	{q6} -> conjunto de estados finais
)
```
**Obs: as identações,"{}" e "()" são essênciais para o não dar erro de segmentação.**
