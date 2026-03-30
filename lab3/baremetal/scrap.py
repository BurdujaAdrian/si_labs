import sys
import os
from pathlib import Path

def main():
    # Parse command line arguments
    if len(sys.argv) < 2:
        print("Usage: python generate_listings.py <directory> [output_file]", file=sys.stderr)
        sys.exit(1)

    root_dir = Path(sys.argv[1])
    if not root_dir.is_dir():
        print(f"Error: {root_dir} is not a valid directory.", file=sys.stderr)
        sys.exit(1)

    out_file = sys.argv[2] if len(sys.argv) > 2 else None

    # Find all .c and .h files recursively
    files = list(root_dir.rglob("*.c")) + list(root_dir.rglob("*.h"))
    files.sort()  # sort alphabetically for consistent output

    if not files:
        print("No .c or .h files found.", file=sys.stderr)
        sys.exit(0)

    # Prepare output lines
    output_lines = []
    for file_path in files:
        # Use relative path for the subsection title
        rel_path = file_path.relative_to(root_dir)
        output_lines.append(f"\\subsection{{{rel_path}}}")
        output_lines.append("\\begin{lstlisting}")

        # Read file content – assume UTF‑8, ignore errors
        try:
            with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read()
        except Exception as e:
            content = f"Error reading file: {e}"

        output_lines.append(content.rstrip())  # remove trailing newline if any
        output_lines.append("\\end{lstlisting}")
        output_lines.append("")  # blank line between files

    # Join all lines with newline
    final_text = "\n".join(output_lines)

    # Write to file or stdout
    if out_file:
        with open(out_file, "w", encoding="utf-8") as f:
            f.write(final_text)
        print(f"Written to {out_file}", file=sys.stderr)
    else:
        print(final_text)

if __name__ == "__main__":
    main()
