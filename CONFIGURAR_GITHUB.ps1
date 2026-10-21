param(
 [Parameter(Mandatory=$true)][string]$Usuario,
 [Parameter(Mandatory=$true)][string]$Repositorio,
 [Parameter(Mandatory=$true)][string]$ChavePublica
)
$ErrorActionPreference='Stop'
$configPath=Join-Path $PSScriptRoot 'src-tauri\tauri.conf.json'
$config=Get-Content $configPath -Raw -Encoding UTF8 | ConvertFrom-Json
$config.plugins.updater.pubkey=$ChavePublica.Trim()
$config.plugins.updater.endpoints=@("https://github.com/$Usuario/$Repositorio/releases/latest/download/latest.json")
$config | ConvertTo-Json -Depth 40 | Set-Content $configPath -Encoding UTF8
Write-Host 'Atualizador configurado para:' $Usuario/$Repositorio
Write-Host 'Verifique se o repositorio e PUBLICO e se a chave publica corresponde a chave privada do GitHub Secret.'
