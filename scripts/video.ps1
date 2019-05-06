$url = 'https://s3.gifyu.com/images/goodbye2.gif'
$outpath = Join-Path $home 'Desktop\goodbye.gif'
$w = New-Object System.Net.WebClient
$w.DownloadFile($url, $outpath)
[void][reflection.assembly]::LoadWithPartialName('System.Windows.Forms')
$form = (get-item (Join-Path $home '\Desktop\goodbye.gif'))
$image = [System.Drawing.Image]::Fromfile($form);
$form = new-object Windows.Forms.Form
$form.Width = $image.Size.Width;
$form.Height =  $image.Size.Height;
$pictureBox = new-object Windows.Forms.PictureBox
$pictureBox.Width =  $form.Width;
$pictureBox.Height =  $form.Height;
$pictureBox.Image = $image;
$form.controls.add($pictureBox)
$form.Add_Shown({$form.Activate()})
$form.ShowDialog()
