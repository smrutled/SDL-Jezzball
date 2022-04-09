git clone https://github.com/Microsoft/vcpkg.git
call .\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install sdl2:x86-windows-static sdl2-ttf:x86-windows-static sdl2-image:x86-windows-static