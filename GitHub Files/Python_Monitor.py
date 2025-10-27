import subprocess
import re
import time
import psutil
import json
import os

CPP_APP = r""   # Path to your compiled C++ app
OUTPUT_FILE = r""  # Shared file for the popup


def run_cpp_and_get_output():
    """Run the C++ process tree app and return its stdout text."""
    try:
        proc = subprocess.run(
            [CPP_APP],
            input="0\n",
            text=True,
            capture_output=True,
            timeout=10
        )
        return proc.stdout
    except Exception as e:
        return ""


def parse_tree_output(output):
    """Parse tree output into [(indent, name, pid)]."""
    lines = output.splitlines()
    pattern = re.compile(r"^( *)(?:\|-- )?(.+?) \(PID: (\d+)\)")
    result = []
    for line in lines:
        match = pattern.search(line)
        if match:
            indent = len(match.group(1))
            name = match.group(2).strip()
            pid = int(match.group(3))
            result.append((indent, name, pid))
    return result


def get_usage(pid):
    """Return (cpu, mem) for a PID."""
    try:
        p = psutil.Process(pid)
        cpu = p.cpu_percent(interval=0.01)
        mem = p.memory_percent()
        return cpu, mem
    except (psutil.NoSuchProcess, psutil.AccessDenied):
        return None, None


def save_to_json(data):
    """Write process info tree to a JSON file."""
    try:
        with open(OUTPUT_FILE, "w") as f:
            json.dump(data, f, indent=2)
    except Exception as e:
        pass


def main():
    while True:
        output = run_cpp_and_get_output()
        if not output.strip():
            time.sleep(5)
            continue

        tree_data = parse_tree_output(output)
        process_list = []

        for indent, name, pid in tree_data:
            cpu, mem = get_usage(pid)
            process_list.append({
                "indent": indent,
                "name": name,
                "pid": pid,
                "cpu": cpu if cpu is not None else 0.0,
                "mem": mem if mem is not None else 0.0
            })

        save_to_json(process_list)
        time.sleep(5)


if __name__ == "__main__":
    main()

