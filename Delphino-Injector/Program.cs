﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Delphino_Injector
{
    class Program
    {
        public static string dataDir = Environment.ExpandEnvironmentVariables(@"%appdata%\Delphino");

        public static Process game;
        public static IntPtr pHandle;

        static void Main(string[] args)
        {
            Console.WriteLine("Delphino by DisabledMallis");
            Console.WriteLine("Verifying Delphino is properly installed...");
            if (verifyDel())
            {
                Console.WriteLine("Waiting for Minecraft...");
                awaitGame();
                Console.WriteLine("Injecting...");
                injectDel();
                Console.WriteLine("Injected!");
            }
            else
            {
                Console.WriteLine("Delphino isnt properly installed!");
                Console.ReadLine();
            }
        }

        private static bool verifyDel()
        {
            if (!Directory.Exists(dataDir))
            {
                Directory.CreateDirectory(dataDir);
            }
            if (!File.Exists(dataDir + "/Delphino.dll"))
            {
                Console.WriteLine("Missing dll!");
                return false;
            }
            return true;
        }

        public static void awaitGame()
        {
            while (true)
            {
                Thread.Sleep(10);
                Process[] possiblilties = Process.GetProcessesByName("java");
                if (possiblilties.Length < 1)
                {
                    continue;
                }
                Process tempGame = possiblilties[0];
                if (tempGame.MainWindowHandle == null)
                {
                    continue;
                }
                StringBuilder sb = new StringBuilder("Minecraft 1.8.9".Length + 1);
                Win32.GetWindowText(tempGame.MainWindowHandle, sb, "Minecraft 1.8.9".Length + 1);
                if (sb.ToString().CompareTo("Minecraft 1.8.9") != 0)
                {
                    continue;
                }
                game = tempGame;
                pHandle = Win32.OpenProcess(0x1F0FFF, true, game.Id);
                break;
            }
        }

        private static void injectDel()
        {
            InjectDll(dataDir + "/Delphino.dll");
        }

        //Code from https://github.com/erfg12/memory.dll/blob/master/Memory/memory.cs
        public static void InjectDll(string strDllName)
        {
            IntPtr bytesout;

            foreach (ProcessModule pm in game.Modules)
            {
                if (pm.ModuleName.StartsWith("inject", StringComparison.InvariantCultureIgnoreCase))
                    return;
            }

            /*if (!game.Responding)
                return;*/

            int lenWrite = strDllName.Length + 1;
            UIntPtr allocMem = Win32.VirtualAllocEx(pHandle, (UIntPtr)null, (uint)lenWrite, 0x00001000 | 0x00002000, 0x04);

            Win32.WriteProcessMemory(pHandle, allocMem, strDllName, (UIntPtr)lenWrite, out bytesout);
            UIntPtr injector = Win32.GetProcAddress(Win32.GetModuleHandle("kernel32.dll"), "LoadLibraryA");

            if (injector == null)
                return;

            IntPtr hThread = Win32.CreateRemoteThread(pHandle, (IntPtr)null, 0, injector, allocMem, 0, out bytesout);
            if (hThread == null)
                return;

            int Result = Win32.WaitForSingleObject(hThread, 10 * 1000);
            if (Result == 0x00000080L || Result == 0x00000102L)
            {
                if (hThread != null)
                    Win32.CloseHandle(hThread);
                return;
            }
            Win32.VirtualFreeEx(pHandle, allocMem, (UIntPtr)0, 0x8000);

            if (hThread != null)
                Win32.CloseHandle(hThread);

            return;
        }
    }
}
