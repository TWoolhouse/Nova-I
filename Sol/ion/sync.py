import sys
import json
import functools
from pathlib import Path

# TESTING
sys.argv.extend([
    "C:/dev/Nova/Solar",
])

@functools.wraps(print)
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

if len(sys.argv) < 2:
    eprint("Invalid number of arguments!")
    quit(1)

flare = Path(sys.argv[1]).resolve()
ion = Path(__file__).parent.resolve()

d_cache = flare / "ion"
f_cache = d_cache / "cache.json"

def read_cache() -> dict:
    if not d_cache.exists():
        d_cache.mkdir(parents=True)
    if f_cache.exists():
        with open(f_cache, "rb") as file:
            return json.load(file)
    return {}
def write_cache(obj: dict):
    with open(f_cache, "wb") as file:
        json.dump(cache, file)

cache = read_cache()

write_cache(cache)
