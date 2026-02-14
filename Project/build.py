import platform
import zipfile
import tarfile
import shutil
import os

#---------------------
# DATA
#---------------------
os_name                 = platform.system()
os_win                  = "Windows"
os_mac                  = "Darwin"

thirdparty_win_name     = "Thirdparty.zip"
thirdparty_mac_name     = "Thirdparty.tar"
data_zip_name           = "Data.zip"
tool_zip_name           = "Tool.zip"
gamedir_path            = "../GameDir/"

shaderc_name_win        = "Shaderc.exe"
shaderc_name_mac        = "shadercRelease"

debug_win_path          = "x64/Debug"
release_win_path        = "x64/Release"

d3d_dir                 = "../GameDir/Data/Shaders/D3D"
spirv_dir               = "../GameDir/Data/Shaders/SPIRV"

win_file_copy = [
    "Thirdparty/x64/Debug/assimp-vc143-mtd.dll",
    "Thirdparty/x64/Debug/renderdoc.dll",
    "Thirdparty/x64/Debug/SDL3.dll",
    "Thirdparty/x64/Release/assimp-vc143-mt.dll",
    "Thirdparty/x64/Release/SDL3.dll"
]

win_file_dest = [
    "x64/Debug/assimp-vc143-mtd.dll",
    "x64/Debug/renderdoc.dll",
    "x64/Debug/SDL3.dll",
    "x64/Release/assimp-vc143-mt.dll",
    "x64/Release/SDL3.dll"
]       

#---------------------
# CODE
#---------------------
os.makedirs(gamedir_path, exist_ok=True)

if os_name == os_win:
    with zipfile.ZipFile(thirdparty_win_name, 'r') as zip_ref:
        zip_ref.extractall()
    
    os.makedirs(debug_win_path, exist_ok=True)
    os.makedirs(release_win_path, exist_ok=True)
            
    for src, dst in zip(win_file_copy, win_file_dest):
        shutil.copy2(src, dst)

    os.makedirs(d3d_dir, exist_ok=True)
    
    with zipfile.ZipFile(tool_zip_name, 'r') as zip_ref:
        zip_ref.extract(shaderc_name_win, path=gamedir_path)
elif os_name == os_mac:
    with tarfile.open(thirdparty_mac_name, "r:*") as tar:
        tar.extractall()
    
    with zipfile.ZipFile(tool_zip_name, 'r') as zip_ref:
        zip_ref.extract(shaderc_name_mac, path=gamedir_path)

os.makedirs(spirv_dir, exist_ok=True)

with zipfile.ZipFile(data_zip_name, "r") as zipRef:
        zipRef.extractall(gamedir_path)
