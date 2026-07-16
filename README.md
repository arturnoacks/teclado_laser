
# Teclado Laser Multi-Instrumental
- Projeto Integrado de Computação II - INF16193/ELE16194
- Artur Noack de Souza, Eduarda Tonini Ferri, Heitor Pinheiro Sousa e Luiz Gabriel Figueiredo Carvalho

O projeto consiste em um teclado multi-instrumental cujo acionamento das teclas ocorre ao interromper um feixe *laser*. De modo geral, o sistema de acionamento pode ser resumido em um conjunto de 24 circuitos emissor comum, que são chaveados de acordo com a resistência de cada LDR (inicialmente saturados pela luz dos *lasers*). Os sinais de saída são recebidos pelo Arduino Mega, que se comunica com o Arduino Uno e o VS1053 para gerar uma saída de áudio via porta P2. Parâmetros diversos como volume e instrumento podem ser visualizados e manipulados por meio de uma interface *web* gerenciada por um ESP32. Adicionalmente, um *encoder* rotativo também pode alterar esses parâmetros.

## Descrição do código

O projeto é dividido em duas partes principais:

* **Hardware**: executado nos microcontroladores (Arduino Mega, Arduino Uno e ESP32), responsável pela leitura das teclas, geração do áudio MIDI e comunicação com a interface web.
* **Software**: aplicação responsável pela interface do usuário, permitindo controlar parâmetros do teclado e visualizar, em tempo real, as teclas pressionadas.

### Hardware

#### Arduino Mega

O Arduino Mega é o controlador principal do sistema.

Suas responsabilidades são:

* realizar a leitura das 24 teclas do teclado laser;
* detectar eventos de Note ON e Note OFF;
* converter cada sensor na respectiva nota MIDI;
* aplicar o deslocamento de oitava selecionado;
* enviar comandos MIDI para o Arduino Uno;
* controlar o encoder rotativo para alteração de volume, instrumento e oitava;
* comunicar-se com a ESP32 através da interface Serial2 utilizando mensagens JSON.

#### Arduino Uno + MIDI Shield

O Arduino Uno é responsável exclusivamente pela geração do áudio.

* inicializa o VS1053 em modo Real-Time MIDI;
* recebe os comandos MIDI enviados pelo Arduino Mega através da comunicação serial;
* encaminha esses comandos ao VS1053 via interface SPI;
* reproduz o áudio correspondente ao instrumento e nota selecionados.

#### ESP32

A ESP32 realiza a comunicação entre o hardware e a interface web. Ela conecta-se à rede Wi-Fi, hospeda um servidor WebSocket e faz a troca de mensagens entre o Arduino Mega e a aplicação web. Assim, alterações realizadas na interface são enviadas ao hardware, enquanto os eventos gerados pelo teclado e pelo encoder são transmitidos em tempo real para a interface.

#### Como executar

Carregue cada código na placa correspondente. Antes de fazer upload na ESP32, configure as credenciais da rede Wi-Fi:

```
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";
```

Após a inicialização, a ESP32 exibirá no monitor serial o seu endereço IP.

### Software

#### Interface web

A interface web permite controlar os principais parâmetros do teclado, como volume, instrumento e oitava, além de exibir, em tempo real, as teclas pressionadas durante a execução. A comunicação com o hardware é realizada por meio de uma conexão WebSocket estabelecida com a ESP32, garantindo a sincronização entre a interface e o instrumento físico.

#### Como executar

Configure o endereço IP da ESP32 utilizado pela conexão WebSocket em app/components/page.tsx:

```
const ESP_IP = "IP_DA_ESP"; 
```

No diretório da aplicação, instale as dependências:

```
npm install
```

Execute o servidor de desenvolvimento:

```
npm run dev
```

Abra http://localhost:3000 no seu navegador para acessar a interface.

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

O processo de criação das placas foi feita a partir da criação de apenas uma nota, que foi replicada 24 vezes para a completude do piano. Cada uma das notas foi feita à partir de um circuito Emissor Comum, como o da imagem abaixo, de forma que o emissor do transistor fosse conectado direto ao terra, R1 = 4.7k Ohms, Rc = 10k Ohms e R2 fosse um LDR, que possui entre 50 e 100 Ohms quando saturado, ou seja, com o laser apontado. 

<img src="/images/emissor_comum.png" alt="Exemplo de circuito Emissor Comum." width="300" height="200">

Figura 1: Exemplo de circuito Emissor Comum.


Dessa forma, quando o laser é impedido por um obstáculo, o transistor entra em corte e a saída cai. Quando o obstáculo é retirado, o LDR satura e o transistor volta a passar corrente, e a saída volta a 5V. Essa lógica é invertida em software.

Depois disso, foi utilizado o software KiCad, onde foram feitos 2 projetos, o primeiro sendo a junção de 5 notas e o segundo de 7 notas. 

<img src="/images/projeto_circuito.jpg" alt="Projeto do circuito de 5 notas no KiCad" width="300" height="200">

Figura 2: Projeto do circuito de 5 notas no KiCad.

Isso foi feito por questão de espaço físico na máquina CnC, que foi utilizada para gravura do circuito na placa. Cada placa foi pintada com uma tinta preta que reage à luz ultra-violeta, de forma que a CnC pudesse disparar um laser forte e secar a tinta no formato do circuito desejado. Depois da gravura, a tinta que não havia sido seca foi retirada com álcool 70%, a placa foi cortada sob medida e por fim imersa em percloreto de ferro, para que o cobre fosse dissolvido.

<img src="/images/circuitoPIC.jpeg" alt="Placa de circuito impresso de 5 notas" width="300" height="200">

Figura 3: Placa de circuito impresso de 5 notas.

Depois da produção da placa, ela foi limpa e raspada com o lado verde de uma esponja molhada com álcool, e furada manualmente. Então, foram soldados todos os componentes como no projeto desenvolvido. 

<img src="/images/circuito-5-trilha.jpeg" alt="Circuito de 5 notas soldado" width="300" height="200">

Figura 4: Placa de circuito impresso de 5 notas pronta.

As trilhas de 5V e GND foram soldadas com seus equivalentes em cada placa por meio de fios de cobre envernizados, e todos os fios de sinais das notas foram soldados em um barramento comum, que pudesse ser facilmente utilizado para se conectar por jumpers no Arduino Mega utilizado.

<img src="/images/piano_pronto.jpeg" alt="Piano montado com todas as placas soldadas." width="300" height="200">

Figura 5: Piano montado com todas as placas soldadas.