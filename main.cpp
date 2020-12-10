#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

#pragma region Login
auto autenticacao = SpeechConfig::FromSubscription("<key>", "<region>"); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
#pragma endregion

auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE TEXTO EM FALA DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE FALA EM TEXTO DO RECURSO

// PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMAÇÃO DE UM TEXTO EM FALA
void texto_em_fala(string Texto)
{
    //cout << Texto + "\n";
    requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}
// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto() {
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
    //cout << resultado->Text + "\n";
    return resultado->Text; //CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}
//checks if player can win
bool can_win(int game[3][3], int value) {
    //vertical check
    for (size_t i = 0; i < 3; i++)
    {
        bool win = true;
        for (size_t j = 0; j < 3; j++)
        {
            auto ii = game[i][j];
            if (ii != value && ii != 0)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    //horizontal check
    for (size_t i = 0; i < 3; i++)
    {
        bool win = true;
        for (size_t j = 0; j < 3; j++)
        {
            auto ii = game[j][i];
            if (ii != value && ii != 0)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    //diagonal check
    {
        bool win = true;
        for (size_t i = 0; i < 3; i++)
        {
            auto ii = game[i][i];
            if (ii != value && ii != 0)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    {
        bool win = true;
        for (size_t i = 0; i < 3; i++)
        {
            auto ii = game[i][2 - i];
            if (ii != value && ii != 0)
            {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}
//checks if a player had won
bool win(int game[3][3], int value) {
    //vertical check
    for (size_t i = 0; i < 3; i++)
    {
        bool win = true;
        for (size_t j = 0; j < 3; j++)
        {
            if (game[i][j] != value)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    //horizontal check
    for (size_t i = 0; i < 3; i++)
    {
        bool win = true;
        for (size_t j = 0; j < 3; j++)
        {
            if (game[j][i] != value)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    //diagonal check
    {
        bool win = true;
        for (size_t i = 0; i < 3; i++)
        {
            if (game[i][i] != value)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    {
        bool win = true;
        for (size_t i = 0; i < 3; i++)
        {
            if (game[i][2 - i] != value)
            {
                win = false;
                break;
            }
        }
        if (win)return true;
    }
    return false;
}


// converte variaveis para um formato legivel
const char encoding[] = { (char)254,'X','O' };
const string encoding_semantinc[] = { "","xisinho","bolinha" };
// faz o dezenho da matriz do jogo
void print(int game[3][3]) {
    system("cls");
    cout << "  ";
    //cabeçario
    for (size_t i = 1; i < 4; i++)
        cout << i << " ";
    cout << '\n';
    for (size_t i = 0; i < 3; i++)
    {
        //lateral
        cout << (char)('a' + i) << " ";
        //dados
        for (size_t j = 0; j < 3; j++)
            cout << encoding[game[i][j]] << " ";
        cout << "\n";
    }
}
const string prefix[] = { "Há","A","B","C","Se","Um","Dois","Três","1","2","3","Hum","Ah"  };
const string pvalue[] = { "a","a","b","c","c","1","2","3","1","2","3","1" ,"a"};
const string sulfix[] = { "um","dois","três","1","2","3","há","a","b","c","se","sei","Ah" };
const string svalue[] = { "1","2","3","1","2","3","a","a","b","c","c","c" ,"a"};
string parse(string str)
{
    for (size_t i = 0; i < 13; i++)
        for (size_t j = 0; j < 13; j++)
            if (str == prefix[i] + " " + sulfix[j]+".")return pvalue[i] + svalue[j];
    return "";
}
int main()
{
    #pragma region Login
    autenticacao = SpeechConfig::FromSubscription("<key>", "<region>");         //  AUTENTICAÇÃO DO RECURSO COM A CHAVE E REGIÃO INFORMADOS PELO USUÁRIO 
    #pragma endregion
    autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //pt-BR-Daniel  // CONFIGURAÇÃO DA AUTENTICAÇÃO COM UMA VOZ ESPECÍFICA 
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURAÇÕES 
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES


    while (true)
    {
        try
        {
            //inicializa matriz
            int game[3][3] = {
                {0,0,0},
                {0,0,0},
                {0,0,0},
            };
            string ctx;
            int player = 1;
            int x = 0;
            int y = 0;
            texto_em_fala("Jogo iniciado, vez do jogador " + encoding_semantinc[player]);
            while (true)
            {
                print(game);
                auto str = fala_em_texto();

                if (str == "Limpar.")break;

                ctx = parse(str);

                if (ctx.length() != 2)continue;

                if (ctx[0] > '9')
                {
                    x = ctx[0] - 'a';
                    y = ctx[1] - '1';
                }
                else
                {
                    x = ctx[1] - 'a';
                    y = ctx[0] - '1';
                }
                if (x >= 0 && x < 3 && y >= 0 && y < 3 && game[x][y] == 0)
                {
                    
                    game[x][y] = player;
                    if (win(game, player))
                    {
                        texto_em_fala(encoding_semantinc[player] + " é o vencedor.");
                        break;
                    }
                    if (!can_win(game, 1) && !can_win(game, 2)) {
                        texto_em_fala("Empate.");
                        break;
                    }
                    player = player == 1 ? 2 : 1;
                    texto_em_fala("Vez do jogador "+ encoding_semantinc[player]);
                    
                }
            }

        }
        catch (exception e) { cout << e.what(); }
    }

    return 0;
}