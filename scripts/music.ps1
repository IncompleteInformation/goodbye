Keyboard.println("Add-Type -AssemblyName presentationCore");
Keyboard.println("$mp = New-Object system.windows.media.mediaplayer");
Keyboard.println("$mp.open((Join-Path $home 'Desktop\\goodbye\\goodbye.mp3'))");
Keyboard.println("$mp.Play()");
Keyboard.println("Add-Type -AssemblyName System.speech");
Keyboard.println("$s = New-Object System.Speech.Synthesis.SpeechSynthesizer");
Keyboard.println("$s.SelectVoice('Microsoft Zira Desktop')");
