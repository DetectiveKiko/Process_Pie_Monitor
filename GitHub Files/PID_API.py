from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
import json
import os

DATA_FILE = r"" # Path to .json monitor files

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

def read_json_data():
    if os.path.exists(DATA_FILE):
        try:
            with open(DATA_FILE, "r") as f:
                return json.load(f)
        except json.JSONDecodeError:
            return []
    return []

@app.get("/processes")
def get_processes():
    return read_json_data()


