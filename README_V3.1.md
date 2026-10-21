# ASG V3.1 - Windows

## Correção da janela CMD piscando
No src-tauri/src/lib.rs o processo filho C++ agora usa `CREATE_NO_WINDOW` (0x08000000). Antes, o snapshot a cada 1,4 segundo iniciava um processo de console visível.

## Recursos
- Candles OHLC simulados derivados de 5 amostras cada (não equivalem a M1/M5/M15 reais)
- Zoom e navegação dos candles
- VWAP demonstrativa calculada com volumes sintéticos
- Pivôs de topo/fundo confirmados com 2 candles à esquerda e à direita
- Mesmas abas da V3.0 e motor C++

## Instalação/atualização
1. Faça backup de `C:\ASG_V3` ou extraia em `C:\ASG_V31`.
2. Abra `x64 Native Tools Command Prompt for VS 2026`.
3. `cd /d C:\ASG_V31`
4. `INSTALAR_E_GERAR_EXE.bat`
5. Instale o novo executável NSIS na pasta `src-tauri\target\release\bundle\nsis`. Feche a versão antiga antes de atualizar.

**Importante:** esta V3.1 não tem dados reais de B3/CME, nem BOS/CHoCH operacional validado, nem book/agressão real. Não usar para operar.
