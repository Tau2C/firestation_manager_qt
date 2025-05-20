#!/bin/sh
echo "Initializing submodules"
git submodule update --init --recursive

chmod +x lib/*/setup-githooks.sh
./lib/*/setup-githooks.sh

echo "Setting up Git hooks from .githooks/..."

HOOKS_DIR=".githooks"
GIT_HOOKS_DIR="$(git rev-parse --git-path hooks)"

for hook in post-merge post-checkout pre-commit; do
  src="$HOOKS_DIR/$hook"
  dest="$GIT_HOOKS_DIR/$hook"

  if [ -f "$src" ]; then
    echo "Installing hook: $hook"
	rm -f "$dest"
    cp "$src" "$dest"
    chmod +x "$dest"
  else
    echo "Warning: Hook script $src not found"
  fi
done

echo "Git hooks installed successfully."
