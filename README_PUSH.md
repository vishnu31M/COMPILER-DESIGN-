Usage

1. Open PowerShell as the user who has Git credentials configured (or run `gh auth login` first).

2. From PowerShell run:

```powershell
cd "C:\Users\vishn\OneDrive\Desktop\COMPILER DESIGN - C CODES"
.\push_to_github.ps1
```

Optional parameters:

```powershell
.\push_to_github.ps1 -Repo 'https://github.com/owner/repo.git' -Source 'C:\path\to\source' -TargetFolder 'folder-in-repo' -Branch 'main'
```

Notes
- The script uses `git` and `robocopy`. Ensure `git` is on your PATH.
- If push asks for credentials, authenticate with `gh auth login` or configure Git credentials.
