#!env python3

'''
This script reads projects - project1....projectn within gerrit as empty
repositories.
'''

import subprocess

GERRIT_HOST = "localhost"
GERRIT_PORT = 29418
ADMIN_USER = "admin"
NUM_PROJECTS=14

for i in range(1, NUM_PROJECTS+1):
    cmd = [
        "ssh",
        "-p", str(GERRIT_PORT),
        f"{ADMIN_USER}@{GERRIT_HOST}",
        "gerrit", "create-project",
        f"project{i}"
    ]
    print( f"{cmd}" )
    subprocess.run(cmd, check=True)
