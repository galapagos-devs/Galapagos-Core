
from ctypes import windll

lib = windll.LoadLibrary(r'C:\Users\asus\source\repos\Galapagos\x64\Debug\Galapagos.dll')
lib.hello_world()