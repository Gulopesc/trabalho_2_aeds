#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

struct Atleta {
    int codigo;
    string nome;
    double pontos, tempo;
};

const int MAX = 10000;
const int PASSO = 10;

int tam = 0;
Atleta listaAtletas[MAX];
int chaveAux[MAX];

int sorteio(int limite) {
    long long r = (long long)rand() * (RAND_MAX + 1LL) + rand();
    return (int)(r % limite);
}

void gerarChaves(int chave[], int n, int padrao) {
    for (int i = 0; i < n; i++) {
        chave[i] = i * PASSO;
    }

    if (padrao == 0) {
        for (int i = n - 1; i > 0; i--) {
            int j = sorteio(i + 1);
            int aux = chave[i];
            chave[i] = chave[j];
            chave[j] = aux;
        }
    } else if (padrao == 1) {
        for (int i = 0, j = n - 1; i < j; i++, j--) {
            int aux = chave[i];
            chave[i] = chave[j];
            chave[j] = aux;
        }
    }
}

bool gerarAtletas(int n, int padrao, unsigned int semente) {
    if (n <= 0 || n > MAX) {
        return false;
    }

    srand(semente);
    gerarChaves(chaveAux, n, padrao);

    for (int i = 0; i < n; i++) {
        listaAtletas[i].codigo = chaveAux[i];
        listaAtletas[i].nome = "Atleta " + to_string(chaveAux[i]);
        listaAtletas[i].pontos = chaveAux[i] / 10.0;
        listaAtletas[i].tempo = 10.0 + (chaveAux[i] % 100) / 10.0;
    }

    tam = n;
    return true;
}

int verificarPontosDecrescente(const Atleta v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i].pontos < v[i + 1].pontos) {
            return i;
        }
    }
    return -1;
}

void exibirVerificacaoPontos(const Atleta v[], int n) {
    int erro = verificarPontosDecrescente(v, n);
    if (erro == -1) {
        cout << "Verificacao (pontos decrescentes): OK\n";
    } else {
        cout << "Verificacao (pontos decrescentes): ERRO no indice " << erro << "\n";
    }
}

bool insere(int codigoA, string nomeA, double pontosA, double tempoA) {
    if (tam >= MAX) {
        return false;
    }
    for (int i = 0; i < tam; i++) {
        if (listaAtletas[i].codigo == codigoA) {
            return false;
        }
    }

    listaAtletas[tam].codigo = codigoA;
    listaAtletas[tam].nome = nomeA;
    listaAtletas[tam].tempo = tempoA;
    listaAtletas[tam].pontos = pontosA;

    tam++;
    return true;
}

void exibirLista(const Atleta v[], int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i].codigo << " | " << v[i].nome
             << " | Pontos: " << v[i].pontos
             << " | Tempo: " << v[i].tempo << '\n';
    }
}

void bubblePontuacao() {
    if (tam == 0) {
        cout << "Cadastro vazio.\n";
        return;
    }

    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    Atleta temp;
    int n = tam;

    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (listaTemp[j].pontos < listaTemp[j + 1].pontos) {
                temp = listaTemp[j];
                listaTemp[j] = listaTemp[j + 1];
                listaTemp[j + 1] = temp;
                trocas++;
                movimentacoes += 3;
                trocou = true;
            }
        }
        if (!trocou) {
            break;
        }
    }

    cout << "Bubble (pontos): " << comparacoes << " comparacoes, "
         << trocas << " trocas, " << movimentacoes << " movimentacoes\n";
    exibirVerificacaoPontos(listaTemp, n);
    if (n <= 20) {
        exibirLista(listaTemp, n);
    }
}

void selectionPontuacao() {
    if (tam == 0) {
        cout << "Cadastro vazio.\n";
        return;
    }

    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    Atleta temp;
    int n = tam;

    for (int i = 0; i < n - 1; i++) {
        int indMinimo = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (listaTemp[j].pontos > listaTemp[indMinimo].pontos) {
                indMinimo = j;
            }
        }
        if (indMinimo != i) {
            temp = listaTemp[indMinimo];
            listaTemp[indMinimo] = listaTemp[i];
            listaTemp[i] = temp;
            trocas++;
            movimentacoes += 3;
        }
    }

    cout << "Selection (pontos): " << comparacoes << " comparacoes, "
         << trocas << " trocas, " << movimentacoes << " movimentacoes\n";
    exibirVerificacaoPontos(listaTemp, n);
    if (n <= 20) {
        exibirLista(listaTemp, n);
    }
}

void insertionPontuacao() {
    if (tam == 0) {
        cout << "Cadastro vazio.\n";
        return;
    }

    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    int n = tam;

    for (int i = 1; i < n; i++) {
        Atleta chave = listaTemp[i];
        movimentacoes++;
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (listaTemp[j].pontos >= chave.pontos) {
                break;
            }
            listaTemp[j + 1] = listaTemp[j];
            movimentacoes++;
            j--;
        }

        listaTemp[j + 1] = chave;
        movimentacoes++;
    }

    cout << "Insertion (pontos): " << comparacoes << " comparacoes, "
         << trocas << " trocas, " << movimentacoes << " movimentacoes\n";
    exibirVerificacaoPontos(listaTemp, n);
    if (n <= 20) {
        exibirLista(listaTemp, n);
    }
}

void selectionAlfabetico() {
    if (tam == 0) {
        cout << "Cadastro vazio.\n";
        return;
    }

    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    Atleta temp;
    int n = tam;

    for (int i = 0; i < n - 1; i++) {
        int indMinimo = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (listaTemp[j].nome < listaTemp[indMinimo].nome) {
                indMinimo = j;
            }
        }
        if (indMinimo != i) {
            temp = listaTemp[indMinimo];
            listaTemp[indMinimo] = listaTemp[i];
            listaTemp[i] = temp;
            trocas++;
            movimentacoes += 3;
        }
    }

    cout << "Selection (nome): " << comparacoes << " comparacoes, "
         << trocas << " trocas, " << movimentacoes << " movimentacoes\n";
    if (n <= 20) {
        exibirLista(listaTemp, n);
    }
}

void insertionTempo() {
    if (tam == 0) {
        cout << "Cadastro vazio.\n";
        return;
    }

    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    int n = tam;

    for (int i = 1; i < n; i++) {
        Atleta chave = listaTemp[i];
        movimentacoes++;
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (listaTemp[j].tempo <= chave.tempo) {
                break;
            }
            listaTemp[j + 1] = listaTemp[j];
            movimentacoes++;
            j--;
        }

        listaTemp[j + 1] = chave;
        movimentacoes++;
    }

    cout << "Insertion (tempo): " << comparacoes << " comparacoes, "
         << trocas << " trocas, " << movimentacoes << " movimentacoes\n";
    if (n <= 20) {
        exibirLista(listaTemp, n);
    }
}

void cadastrarAtleta() {
    int codigo;
    string nome;
    double pontos, tempo;

    cout << "Codigo: ";
    cin >> codigo;
    cout << "Nome: ";
    getline(cin >> ws, nome);
    cout << "Pontos e tempo: ";
    cin >> pontos >> tempo;

    if (!insere(codigo, nome, pontos, tempo)) {
        cout << "Erro: estrutura cheia ou codigo duplicado.\n";
    }
}

void menuGerarDados() {
    int n, padrao;
    unsigned int semente;

    cout << "Quantidade de atletas (1 a " << MAX << "): ";
    cin >> n;
    cout << "Padrao (0-Aleatorio, 1-Ordenado/decrescente, 2-Inverso/crescente): ";
    cin >> padrao;
    cout << "Semente: ";
    cin >> semente;

    if (padrao < 0 || padrao > 2) {
        cout << "Padrao invalido.\n";
        return;
    }

    if (gerarAtletas(n, padrao, semente)) {
        cout << "Gerados " << tam << " atletas com sucesso.\n";
    } else {
        cout << "Erro ao gerar atletas: quantidade invalida ou acima do limite.\n";
    }
}

void selectionPontuacaoRetornavel(int tam, long long &comp, long long &troc, long long &movi) {
    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    Atleta temp;
    int n = tam;

    for (int i = 0; i < n - 1; i++) {
        int indMinimo = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (listaTemp[j].pontos > listaTemp[indMinimo].pontos) {
                indMinimo = j;
            }
        }
        if (indMinimo != i) {
            temp = listaTemp[indMinimo];
            listaTemp[indMinimo] = listaTemp[i];
            listaTemp[i] = temp;
            trocas++;
            movimentacoes += 3;
        }
    }

    comp = comparacoes;
    troc = trocas;
    movi = movimentacoes;
}

void insertionPontuacaoRetornavel(int tam, long long &comp, long long &troc, long long &movi) {
    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    int n = tam;

    for (int i = 1; i < n; i++) {
        Atleta chave = listaTemp[i];
        movimentacoes++;
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (listaTemp[j].pontos >= chave.pontos) {
                break;
            }
            listaTemp[j + 1] = listaTemp[j];
            movimentacoes++;
            j--;
        }

        listaTemp[j + 1] = chave;
        movimentacoes++;
    }

    comp = comparacoes;
    troc = trocas;
    movi = movimentacoes;
}

void bubblePontuacaoRetornavel(int tam, long long &comp, long long &troc, long long &movi) {
    static Atleta listaTemp[MAX];
    for (int i = 0; i < tam; i++) {
        listaTemp[i] = listaAtletas[i];
    }

    long long trocas = 0;
    long long comparacoes = 0;
    long long movimentacoes = 0;
    Atleta temp;
    int n = tam;

    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (listaTemp[j].pontos < listaTemp[j + 1].pontos) {
                temp = listaTemp[j];
                listaTemp[j] = listaTemp[j + 1];
                listaTemp[j + 1] = temp;
                trocas++;
                movimentacoes += 3;
                trocou = true;
            }
        }
        if (!trocou) {
            break;
        }
    }

    comp = comparacoes;
    troc = trocas;
    movi = movimentacoes;
}

void experimentador(int n) {
    long long comp1, troc1, movi1;
    long long comp2, troc2, movi2;

    cout << "Insertion:\n";

    gerarAtletas(n, 0, 1);
    insertionPontuacaoRetornavel(n, comp1, troc1, movi1);
    gerarAtletas(n, 0, 2);
    insertionPontuacaoRetornavel(n, comp2, troc2, movi2);
    cout << "Padrao aleatorio: "
         << (comp1 + comp2) / 2 << " comparacoes, "
         << (troc1 + troc2) / 2 << " trocas, "
         << (movi1 + movi2) / 2 << " movimentacoes.\n";

    gerarAtletas(n, 1, 1);
    insertionPontuacaoRetornavel(n, comp1, troc1, movi1);
    cout << "Padrao ordenado: " << comp1 << " comparacoes, "
         << troc1 << " trocas, " << movi1 << " movimentacoes.\n";

    gerarAtletas(n, 2, 1);
    insertionPontuacaoRetornavel(n, comp1, troc1, movi1);
    cout << "Padrao inverso: " << comp1 << " comparacoes, "
         << troc1 << " trocas, " << movi1 << " movimentacoes.\n";

    cout << "Bubble:\n";

    gerarAtletas(n, 0, 1);
    bubblePontuacaoRetornavel(n, comp1, troc1, movi1);
    gerarAtletas(n, 0, 2);
    bubblePontuacaoRetornavel(n, comp2, troc2, movi2);
    cout << "Padrao aleatorio: "
         << (comp1 + comp2) / 2 << " comparacoes, "
         << (troc1 + troc2) / 2 << " trocas, "
         << (movi1 + movi2) / 2 << " movimentacoes.\n";

    gerarAtletas(n, 1, 1);
    bubblePontuacaoRetornavel(n, comp1, troc1, movi1);
    cout << "Padrao ordenado: " << comp1 << " comparacoes, "
         << troc1 << " trocas, " << movi1 << " movimentacoes.\n";

    gerarAtletas(n, 2, 1);
    bubblePontuacaoRetornavel(n, comp1, troc1, movi1);
    cout << "Padrao inverso: " << comp1 << " comparacoes, "
         << troc1 << " trocas, " << movi1 << " movimentacoes.\n";

    cout << "Selection:\n";

    gerarAtletas(n, 0, 1);
    selectionPontuacaoRetornavel(n, comp1, troc1, movi1);
    gerarAtletas(n, 0, 2);
    selectionPontuacaoRetornavel(n, comp2, troc2, movi2);
    cout << "Padrao aleatorio: "
         << (comp1 + comp2) / 2 << " comparacoes, "
         << (troc1 + troc2) / 2 << " trocas, "
         << (movi1 + movi2) / 2 << " movimentacoes.\n";

    gerarAtletas(n, 1, 1);
    selectionPontuacaoRetornavel(n, comp1, troc1, movi1);
    cout << "Padrao ordenado: " << comp1 << " comparacoes, "
         << troc1 << " trocas, " << movi1 << " movimentacoes.\n";

    gerarAtletas(n, 2, 1);
    selectionPontuacaoRetornavel(n, comp1, troc1, movi1);
    cout << "Padrao inverso: " << comp1 << " comparacoes, "
         << troc1 << " trocas, " << movi1 << " movimentacoes.\n";
}

void experimento() {
    cout << "Protocolo experimental ativado.\n\nn=10:\n";
    experimentador(10);
    cout << "\n\nn=100:\n";
    experimentador(100);
    cout << "\n\nn=1000:\n";
    experimentador(1000);
}

void ordenarCopiaEstabilidade(const Atleta origem[], int n, int metodo, Atleta destino[]) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }

    Atleta temp;
    if (metodo == 1) {
        for (int i = 0; i < n - 1; i++) {
            bool trocou = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (destino[j].pontos < destino[j + 1].pontos) {
                    temp = destino[j];
                    destino[j] = destino[j + 1];
                    destino[j + 1] = temp;
                    trocou = true;
                }
            }
            if (!trocou) {
                break;
            }
        }
    } else if (metodo == 2) {
        for (int i = 0; i < n - 1; i++) {
            int indMaior = i;
            for (int j = i + 1; j < n; j++) {
                if (destino[j].pontos > destino[indMaior].pontos) {
                    indMaior = j;
                }
            }
            if (indMaior != i) {
                temp = destino[indMaior];
                destino[indMaior] = destino[i];
                destino[i] = temp;
            }
        }
    } else if (metodo == 3) {
        for (int i = 1; i < n; i++) {
            Atleta chave = destino[i];
            int j = i - 1;
            while (j >= 0 && destino[j].pontos < chave.pontos) {
                destino[j + 1] = destino[j];
                j--;
            }
            destino[j + 1] = chave;
        }
    }
}

void imprimirOrdemCodigosPorPontos(const char titulo[], const Atleta v[], int n) {
    cout << "--- " << titulo << " ---\n";
    for (int i = 0; i < n; i++) {
        cout << "Cod:" << v[i].codigo
             << " (" << v[i].nome << ")"
             << " -> Pontos: " << v[i].pontos << '\n';
    }
}

void demonstrarEstabilidade() {
    const int n = 9;
    static Atleta base[MAX];
    static Atleta saida[MAX];

    srand(42);
    for (int i = 0; i < n; i++) {
        base[i].codigo = i + 1;
        base[i].nome = "Atleta " + to_string(i + 1);
        base[i].pontos = (rand() % 4) * 10.0;
        base[i].tempo = 10.0 + i;
    }

    imprimirOrdemCodigosPorPontos("Entrada original (com empates de pontos)", base, n);

    ordenarCopiaEstabilidade(base, n, 1, saida);
    imprimirOrdemCodigosPorPontos("BubbleSort (estavel)", saida, n);

    ordenarCopiaEstabilidade(base, n, 2, saida);
    imprimirOrdemCodigosPorPontos("SelectionSort (pode alterar empates)", saida, n);

    ordenarCopiaEstabilidade(base, n, 3, saida);
    imprimirOrdemCodigosPorPontos("InsertionSort (estavel)", saida, n);
}

int main() {
    int escolha = -1;

    while (escolha != 0) {
        cout << "1-Cadastrar \n2-Bubble/pontos \n3-Selection/nome \n4-Insertion/tempo\n";
        cout << "5-Comparar os tres (mesma entrada) \n6-Exibir cadastro \n7-Gerar dados \n8-testar todos com pontuacao\n";
        cout << "9-Modo experimento 10-Testar estabilidade\n0-Sair\n";
        cin >> escolha;

        switch (escolha) {
            case 0:
                break;
            case 1:
                cadastrarAtleta();
                break;
            case 2:
                bubblePontuacao();
                break;
            case 3:
                selectionAlfabetico();
                break;
            case 4:
                insertionTempo();
                break;
            case 5:
                bubblePontuacao();
                selectionAlfabetico();
                insertionTempo();
                break;
            case 6:
                if (tam == 0) {
                    cout << "Cadastro vazio.\n";
                } else {
                    exibirLista(listaAtletas, tam);
                }
                break;
            case 7:
                menuGerarDados();
                break;
            case 8:
                bubblePontuacao();
                selectionPontuacao();
                insertionPontuacao();
                break;
            case 9:
                experimento();
                break;
            case 10:
                demonstrarEstabilidade();
                break;
            default:
                cout << "Opcao invalida.\n";
                break;
        }
    }

    return 0;
}