#!env python3

'''
This script reads student names and email addresses from `students.csv` and
creates accounts for them on Gerrit development server running locally. It adds
them to a group named `Students`.
'''

import csv
import subprocess
import shlex

GERRIT_HOST = "localhost"
GERRIT_PORT = 29418
ADMIN_USER = "admin"
GROUP = "Students"

with open("students.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        fullname = row["full_name"]
        email = row["email"]
        cmd = [
            "ssh",
            "-p", str(GERRIT_PORT),
            f"{ADMIN_USER}@{GERRIT_HOST}",
            "gerrit", "create-account",
            "--full-name", shlex.quote(fullname),
            "--email", email,
            "--group", GROUP,
            email
        ]
        print( f"{cmd}" )
        subprocess.run(cmd, check=True)


