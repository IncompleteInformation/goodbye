Get-Process | Where-Object {$_.Name -eq 'powershell'} | Where-Object {$_.Id -ne $pid} | Stop-Process -Id {$_.Id} -Force
Start-Sleep -s .5
$root = Join-Path $home 'Desktop\goodbye'
Remove-Item $root -Recurse -Force
