import zipfile
import shutil
import os

with zipfile.ZipFile("Thirdparty.zip", "r") as zipRef:
    zipRef.extractall()
 
os.makedirs("x64/Debug", exist_ok=True)
os.makedirs("x64/Release", exist_ok=True)

shutil.copy2("Thirdparty/x64/Debug/assimp-vc143-mtd.dll",
                "x64/Debug/assimp-vc143-mtd.dll")
shutil.copy2("Thirdparty/x64/Debug/renderdoc.dll",
                "x64/Debug/renderdoc.dll")
shutil.copy2("Thirdparty/x64/Debug/SDL3.dll",
                "x64/Debug/SDL3.dll")
                
shutil.copy2("Thirdparty/x64/Release/assimp-vc143-mt.dll",
                "x64/Release/assimp-vc143-mt.dll")
shutil.copy2("Thirdparty/x64/Release/SDL3.dll",
                "x64/Release/SDL3.dll")

os.makedirs("../GameDir/Data/Shaders/D3D", exist_ok=True)
os.makedirs("../GameDir/Data/Shaders/SPIRV", exist_ok=True)
