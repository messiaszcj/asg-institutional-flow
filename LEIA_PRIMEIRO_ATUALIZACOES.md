# ASG V3.2 — Atualização integrada

Esta versão **adiciona o plugin oficial Tauri Updater e interface de atualização**. O updater **não funciona até ser configurado** com o seu repositório GitHub e sua chave pública de assinatura. NÃO compile o projeto com placeholders.

## Passos iniciais (apenas uma vez)

1. Crie um repositório **público** no GitHub (por exemplo `asg-institutional-flow`). Repositórios privados exigem outro serviço de distribuição/autenticação.
2. Instale o CLI Tauri, se necessário: `npm.cmd install`.
3. No terminal na raiz do projeto, execute `npm.cmd exec tauri signer generate -- -w "$env:USERPROFILE\asg-updater.key"` no PowerShell **ou** `npm.cmd exec tauri signer generate -- -w "%USERPROFILE%\asg-updater.key"` no CMD. Guarde o arquivo `.key` e a senha fora do repositório. A chave pública fica no arquivo `.key.pub`.
4. Execute no PowerShell na pasta do projeto:
   `powershell -ExecutionPolicy Bypass -File .\CONFIGURAR_GITHUB.ps1 -Usuario SEU_USUARIO -Repositorio SEU_REPO -ChavePublica (Get-Content "$env:USERPROFILE\asg-updater.key.pub" -Raw)`
5. Em GitHub > Settings > Secrets and variables > Actions, crie `TAURI_SIGNING_PRIVATE_KEY` (conteúdo da chave privada) e `TAURI_SIGNING_PRIVATE_KEY_PASSWORD` (senha usada ao gerar). **Nunca compartilhe a chave privada nem a senha no chat.**
6. Publique o projeto no repositório (sem chaves privadas; inclua `.gitignore`). Faça commit do `tauri.conf.json` configurado.
7. Para a primeira versão com updater, execute `INSTALAR_E_GERAR_EXE.bat` **com variáveis de assinatura configuradas**, ou preferencialmente publique a tag `v0.3.2` e baixe o instalador gerado pelo GitHub Actions. Instale **uma vez** esta versão com updater.
8. Para próximas versões, aumente o número em `package.json`, `src-tauri/Cargo.toml` e `src-tauri/tauri.conf.json`, faça commit e crie uma nova tag (ex.: `v0.3.3`). O workflow gera release, NSIS e `latest.json`. O aplicativo poderá detectar e instalar essa atualização.

### Atenção
- A assinatura do Tauri Updater não é a mesma assinatura Authenticode do Windows. SmartScreen pode exibir alertas em apps não assinados com certificado Windows.
- O instalador e o `latest.json` devem estar acessíveis pelo aplicativo; valide os arquivos publicados antes de distribuir.
- A atualização precisa de rede, permissão de escrita e versão instalada com updater.
- Não execute `npm audit fix --force` sem testar a compatibilidade.
- Em desenvolvimento, o updater pode falhar fora do build instalado; teste usando a versão empacotada.
