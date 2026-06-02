$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$readme = Join-Path $repoRoot "README.md"
$content = Get-Content -LiteralPath $readme -Raw
$pattern = '!\[[^\]]*\]\(([^)]+)\)|\[[^\]]+\]\(([^)]+)\)'
$failures = @()

foreach ($match in [regex]::Matches($content, $pattern)) {
  $target = if ($match.Groups[1].Success) { $match.Groups[1].Value } else { $match.Groups[2].Value }
  $target = $target.Trim()

  if ($target -eq "" -or
      $target.StartsWith("#") -or
      $target.StartsWith("http://") -or
      $target.StartsWith("https://") -or
      $target.StartsWith("mailto:") -or
      $target.Contains("://")) {
    continue
  }

  $pathOnly = ($target -split "#", 2)[0]
  if ($pathOnly -eq "") {
    continue
  }

  $resolved = Join-Path $repoRoot $pathOnly
  if (-not (Test-Path -LiteralPath $resolved)) {
    $failures += $target
  }
}

if ($failures.Count -gt 0) {
  Write-Host "Broken README local links:"
  $failures | ForEach-Object { Write-Host " - $_" }
  exit 1
}

Write-Host "README local links OK."
