using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LogicCodeIDE
{
    internal static class Program
    {
        public delegate void LogCallback(IntPtr value);
        public delegate void ClearCallback();

        [DllImport("Logic.dll",CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void runCode([MarshalAs(UnmanagedType.LPStr)] string code);
        [DllImport("Logic.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Setup_DebugLog(IntPtr callback);
        [DllImport("Logic.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Setup_DebugClear(IntPtr callback);
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        /// 
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
