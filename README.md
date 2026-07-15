
# Teclado Laser Multi-Instrumental
- Projeto Integrado de Computação II - INF16193/ELE16194
- Artur Noack de Souza, Eduarda Tonini Ferri, Heitor Pinheiro Sousa e Luiz Gabriel Figueiredo Carvalho

O projeto consiste em um teclado multi-instrumental cujo acionamento das teclas ocorre ao interromper um feixe *laser*. De modo geral, o sistema de acionamento pode ser resumido em um conjunto de 24 circuitos emissor comum, que são chaveados de acordo com a resistência de cada LDR (inicialmente saturados pela luz dos *lasers*). Os sinais de saída são recebidos pelo Arduino Mega, que se comunica com o Arduino Uno e o VS1053 para gerar uma saída de áudio via porta P2. Parâmetros diversos como volume e instrumento podem ser visualizados e manipulados por meio de uma interface *web* gerenciada por um ESP32. Adicionalmente, um *encoder* rotativo também pode alterar esses parâmetros.

## Descrição do código

## Descrição do material

### Lista de materiais:
- **Micro Controladores:**
	 - Arduino Mega 2560
	 - Arduino Uno
	 - ESP32
	 - Shield Arduino VS1053
 - **Componentes Eletrônicos:**
	 - 24 Módulos Diodo Laser 5V
	 - 24 Resistores X, Y
	 - 24 Transistores BC547
	 - 24 LDR 5mm
	 - 1 Encoder Rotativo
 - **Impressões 3D:**
	 - Suportes para carcaça, *encoder* e *lasers*
	 - Proteção para LDRs
- **Outros Materiais:**
	- 4 Placas Fenolite Cobreada
	- 1 Placa Fenolite Perfurada
	- Fios e Jumpers Diversos
	- Carcaça de Madeira

## Modelos 3D (e MDF)
O primeiro modelo feito foi a caixa do piano, que, como seria feita em MDF, foi desenhada no *software* de CAD 2D QCAD. Após confecção desse modelo, ele foi enviado para uma loja de artigos em MDF que produziu grande parte da caixa corretamente, mas houveram algumas adaptações feitas pela loja para facilitar a produção da caixa. Isso fez com que algumas medidas do teclado ao final não sejam condizentes com o modelo do QCAD, mas ainda servem de referência.

O primeiro modelo 3D pensado foram as caixinhas dos LDRs: pequenas caixas pretas vazadas apenas para baixo e para frente, feitas para cobrirem cada LDR virado em direção aos *lasers*, prevenindo interferências de iluminação externa e ao mesmo tempo protegendo o ambiente ao redor do piano de poluição visual dos feixes que atravessassem o LDR. Ao total, foram utilizadas 24 caixinhas.

Conforme o desenvolvimento do projeto, foi percebido que o meio do piano, que é relativamente longo, ficaria curvo e frágil sem sustentação por baixo, ainda mais conforme as teclas fossem pressionadas. Para isso, foram impressos alguns suportes 3D, sendo colados à tampa e possuindo espaços vazados para a passagem de cabos e fios. Na mesma lógica, foi impresso um suporte para o *encoder*, uma vez que ele não poderia ser pressionado sem afundar na caixa caso ele não tivesse uma base firme.

Por fim, a última impressão feita foram os anéis de fixação dos *lasers* na parede posterior do teclado. Eles serviram para maior facilidade para colar os lasers, permitindo uma melhor calibragem do que seria possível caso eles fossem colados diretamente no buraco da parede.

Todos esses modelos constam na pasta "models" do repositório. A maioria dos arquivos estão em FCStd, que é o formato padrão do software FreeCAD utilizado para modelagem 3D das peças.
## Projetos de Placas
