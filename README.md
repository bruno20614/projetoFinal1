README:

Código de Execução:
./main <Tamanho da Janela> <Quantização>

Para obter as Imagens Filtradas, é necessário haver DUAS pastas:
1. "Input" para coletagem das Imagens. (Necessário as Imagens estarem em .pgm).
2. "Output" para recebimento das Imagens.

Após Execução, o Programa gerará os arquivos .csv:
Leitura da Nomeclatura:
-> img_[Tamanho da Janela] [Quantização].csv
Exemplo:
	./main 3 8
Arquivo Gerado:
	img_38.csv

Relatório utilizando o WEKA:

-> Precisão: Quando Quantização 8, a Precisão Média é Maior quanto Menor for a Janela, porém, na Quantização 16 a Precisão Média é Disruptiva.
-> Recall: Quando Quantização 8, o Recall Médio é Maior quanto Menor for a Janela, porém, na Quantização 16 o Recall é Disruptivo.

DADOS:

--------------------------------------------------------------------------------------

Janela 3x3 - Quant 8:           Janela 5x5 - Quant 8:		Janela 7x7 - Quant 8:
