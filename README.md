# ASG Institutional Flow V3 — Windows

Primeiro protótipo funcional **DEMONSTRATIVO**, sem Docker, sem MT5 e sem feeds reais.

## Pré-requisitos
- Windows 10/11 x64, Visual Studio com MSVC x64 + CMake + Windows SDK
- Node.js 24 LTS / npm
- Rust stable (https://rustup.rs/), selecionar instalação padrão MSVC
- Microsoft Edge WebView2 Runtime (https://developer.microsoft.com/microsoft-edge/webview2/)
- Git (opcional)

## Como gerar o instalador .exe
1. Extraia o ZIP numa pasta simples, por exemplo `C:\ASG_V3`.
2. Instale Rust pelo `rustup-init.exe`, escolha a opção padrão; **feche e reabra o terminal**.
3. Abra **x64 Native Tools Command Prompt for VS 2026**.
4. Execute `cd /d C:\ASG_V3` (ajuste o caminho).
5. Execute `INSTALAR_E_GERAR_EXE.bat`.
6. O instalador NSIS aparecerá em `src-tauri\target\release\bundle\nsis\`.

Primeira compilação pode baixar bibliotecas e levar vários minutos. Requer internet.

## Teste antes de gerar instalador
No mesmo terminal, execute `TESTAR_APLICATIVO.bat`.

## Estrutura
- `engine/` — motor C++20 independente; gera snapshot JSON simulado.
- `src/` — frontend React/TypeScript com painel institucional.
- `src-tauri/` — janela Windows, comando Rust para executar o motor C++, empacotamento NSIS.
- `scripts/` — compilação do motor C++ via CMake/MSVC.

## Aviso de integridade
Não há integração com corretora, B3, CME, Profit ou BlackArrow nesta versão. Preços, pressão, delta, liquidez, bid/ask e gráficos são **sintéticos**. O cálculo de delta não utiliza agressão de negócios. Não usar para operações financeiras.

## Próximas etapas
1. Substituir processo C++ por chamada por snapshot por serviço persistente com WebSocket.
2. Importação RTD/arquivos e adaptadores para fontes de mercado autorizadas, com validação de timestamps e qualidade.
3. Histórico, replay, indicadores estruturais sem repintura e zonas institucionais.
4. Testes, assinatura do instalador e atualização automática (quando houver certificado e infraestrutura).
