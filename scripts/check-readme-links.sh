#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
readme="$repo_root/README.md"
failures=()

while IFS= read -r target; do
  [[ -z "$target" ]] && continue
  [[ "$target" == \#* ]] && continue
  [[ "$target" == http://* || "$target" == https://* || "$target" == mailto:* || "$target" == *://* ]] && continue

  path_only="${target%%#*}"
  [[ -z "$path_only" ]] && continue

  if [[ ! -e "$repo_root/$path_only" ]]; then
    failures+=("$target")
  fi
done < <(grep -oE '!?\[[^]]+\]\([^)]+\)' "$readme" | sed -E 's/^!?\[[^]]+\]\(([^)]+)\)$/\1/')

if (( ${#failures[@]} > 0 )); then
  echo "Broken README local links:"
  printf ' - %s\n' "${failures[@]}"
  exit 1
fi

echo "README local links OK."
