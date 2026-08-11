param(
    [string]$Repo = 'https://github.com/vishnu31M/COMPILER-DESIGN.git',
    [string]$Source = 'C:\Users\vishn\OneDrive\Desktop\COMPILER DESIGN - C CODES',
    [string]$TargetFolder = 'COMPILER-DESIGN-C-CODES',
    [string]$Branch = 'main'
)

$ErrorActionPreference = 'Stop'

$tempDir = Join-Path $env:TEMP ("push_repo_" + [guid]::NewGuid().ToString())
Write-Output "Cloning $Repo to $tempDir..."
git clone $Repo $tempDir
if ($LASTEXITCODE -ne 0) { Write-Error "git clone failed"; exit 1 }

$dest = Join-Path $tempDir $TargetFolder
Write-Output "Copying from '$Source' to '$dest' (mirroring)..."
New-Item -ItemType Directory -Path $dest -Force | Out-Null

# Use robocopy for robust copying on Windows
robocopy $Source $dest /MIR /NFL /NDL /NJH /NJS | Out-Null

Set-Location $tempDir

# Configure user if not set (optional)
$gitName = git config user.name
if (-not $gitName) { git config user.name "AutoPushScript" }
$gitEmail = git config user.email
if (-not $gitEmail) { git config user.email "autopush@example.com" }

git add -A

# Try to commit; if no changes, continue
$commitMsg = "Add/Update $TargetFolder"
if (git diff --cached --quiet) {
    Write-Output "No changes to commit."
} else {
    git commit -m $commitMsg
    if ($LASTEXITCODE -ne 0) { Write-Error "git commit failed"; exit 1 }
}

Write-Output "Pushing to origin/$Branch..."
git push origin $Branch
if ($LASTEXITCODE -ne 0) { Write-Error "git push failed"; exit 1 }

Write-Output "Done. Repository updated."