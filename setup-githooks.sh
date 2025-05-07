#!/bin/sh
echo "Setting up Git hooks from .githooks/..."

HOOKS_DIR=".githooks"
GIT_HOOKS_DIR="$(git rev-parse --git-path hooks)"

for hook in post-merge post-checkout; do
  src="$HOOKS_DIR/$hook"
  dest="$GIT_HOOKS_DIR/$hook"

  if [ -f "$src" ]; then
    echo "Installing hook: $hook"
    ln -sf "../../$src" "$dest"
    chmod +x "$dest"
  else
    echo "Warning: Hook script $src not found"
  fi
done

echo "Git hooks installed successfully."
