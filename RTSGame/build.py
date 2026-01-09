import zipfile
import os

with zipfile.ZipFile("Thirdparty.zip", "r") as zipRef:
    zipRef.extractall()
