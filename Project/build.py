import platform
import zipfile
import shutil
import os

os_name = platform.system()
thp_zip_name = "Thirdparty.zip"
data_zip_name = "Data.zip"
tool_zip_name = "Tool.zip"
gamedir_path = "../GameDir/"

with zipfile.ZipFile(thp_zip_name, "r") as zipRef:
    zipRef.extractall()

os.makedirs(gamedir_path, exist_ok=True)

if os_name == "Windows":
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

    with zipfile.ZipFile(data_zip_name, "r") as zipRef:
        zipRef.extractall(gamedir_path)

    with zipfile.ZipFile(tool_zip_name, 'r') as zip_ref:
        zip_ref.extract("Shaderc.exe", path=gamedir_path)

    os.makedirs("../GameDir/Data/Shaders/D3D", exist_ok=True)
    os.makedirs("../GameDir/Data/Shaders/SPIRV", exist_ok=True)
elif os_name == "Darwin":
    os.makedirs(gamedir_path+"Contents/", exist_ok=True)
    os.makedirs(gamedir_path+"Contents/MacOS/", exist_ok=True)
    os.makedirs(gamedir_path+"Contents/Resources/", exist_ok=True)
    
    with zipfile.ZipFile(data_zip_name, "r") as zipRef:
        zipRef.extractall(gamedir_path+"Contents/Resources/")
    
    with zipfile.ZipFile(tool_zip_name, 'r') as zip_ref:
        zip_ref.extract("Shaderc", path=gamedir_path)
