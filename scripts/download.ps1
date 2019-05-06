$root_url = 'https://github.com/IncompleteInformation/goodbye/raw/master/'
$root = Join-Path $home 'Desktop\goodbye'
New-Item $root -ItemType "directory" -Force

[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$url = -Join($root_url, 'media\goodbye.mp3')
$outpath = Join-Path $root 'goodbye.mp3'
$webClient = New-Object System.Net.WebClient
$webClient.DownloadFile($url, $outpath)

$url = -Join($root_url, 'media\goodbye.gif')
$outpath = Join-Path $root 'goodbye.gif'
$webClient = New-Object System.Net.WebClient
$webClient.DownloadFile($url, $outpath)

$url = -Join($root_url, 'scripts\video.ps1')
$outpath = Join-Path $root 'video.ps1'
$webClient = New-Object System.Net.WebClient
$webClient.DownloadFile($url, $outpath)

$url = -Join($root_url, 'scripts\cleanup.ps1')
$outpath = Join-Path $root '..\cleanup.ps1'
$webClient = New-Object System.Net.WebClient
$webClient.DownloadFile($url, $outpath)
